// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * CoralNPU Boot ROM Runner
 *
 * A realistic program runner that uses Boot ROM for program loading,
 * exactly like real hardware would work:
 *
 *   1. Program binary is loaded to Flash (0x20000000)
 *   2. CPU starts from Boot ROM (0x00040000)
 *   3. Boot ROM copies from Flash to ITCM (0x00000000)
 *   4. Boot ROM jumps to ITCM to execute the program
 *
 * This is the authentic boot process, not direct memory injection.
 *
 * Usage:
 *   bazel run //hw_sim:coralnpu_bootrom_runner -- <program_name> [timeout_ms]
 *
 * Example:
 *   bazel run //hw_sim:coralnpu_bootrom_runner -- fibonacci
 *   bazel run //hw_sim:coralnpu_bootrom_runner -- quicksort 5000
 */

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "hw_sim/coralnpu_simulator.h"
#include "tests/verilator_sim/elf.h"

// Memory Map (Default Configuration)
constexpr uint32_t ITCM_BASE = 0x00000000;
constexpr uint32_t ITCM_SIZE = 8 * 1024;        // 8KB
constexpr uint32_t DTCM_BASE = 0x00010000;
constexpr uint32_t DTCM_SIZE = 32 * 1024;       // 32KB
constexpr uint32_t BOOTROM_BASE = 0x00040000;
constexpr uint32_t BOOTROM_SIZE = 8 * 1024;     // 8KB
constexpr uint32_t FLASH_BASE = 0x20000000;
constexpr uint32_t FLASH_SIZE = 1 * 1024 * 1024; // 1MB

// Boot ROM binary path (relative to bazel runfiles)
const char* BOOTROM_BIN = "sw/bootrom/boot_default.bin";

// Available programs (relative paths for bazel runfiles)
const std::map<std::string, std::string> kPrograms = {
    {"fibonacci", "examples/coralnpu_v2_fibonacci.elf"},
    {"quicksort", "examples/coralnpu_v2_quicksort.elf"},
    {"hello", "examples/coralnpu_v2_hello_world_add_floats.elf"},
    {"add_floats", "examples/coralnpu_v2_hello_world_add_floats.elf"},
};

void print_usage(const char* prog) {
    std::cout << "Usage: " << prog << " <program_name> [timeout_ms]" << std::endl;
    std::cout << std::endl;
    std::cout << "This runner uses Boot ROM for authentic program loading:" << std::endl;
    std::cout << "  1. Program loaded to Flash (0x20000000)" << std::endl;
    std::cout << "  2. CPU starts from Boot ROM (0x00040000)" << std::endl;
    std::cout << "  3. Boot ROM copies Flash -> ITCM" << std::endl;
    std::cout << "  4. Boot ROM jumps to ITCM (0x00000000)" << std::endl;
    std::cout << std::endl;
    std::cout << "Available programs:" << std::endl;
    for (const auto& [name, path] : kPrograms) {
        std::cout << "  " << name << " -> " << path << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  program_name  Name of the program to run (or full path to .elf)" << std::endl;
    std::cout << "  timeout_ms    Timeout in milliseconds (default: 10000)" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "========================================" << std::endl;
    std::cout << "  CoralNPU Boot ROM Runner" << std::endl;
    std::cout << "  RV32IMF_Zve32x RISC-V Core" << std::endl;
    std::cout << "  (Authentic Boot Process)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    // Resolve program name to path
    std::string program_arg = argv[1];
    std::string elf_file;

    auto it = kPrograms.find(program_arg);
    if (it != kPrograms.end()) {
        elf_file = it->second;
        std::cout << "[INFO] Running program: " << program_arg << std::endl;
    } else {
        elf_file = program_arg;
        std::cout << "[INFO] Running ELF file: " << elf_file << std::endl;
    }

    int timeout_ms = 10000;  // Default 10 seconds

    if (argc >= 3) {
        timeout_ms = std::atoi(argv[2]);
    }

    // Create simulator
    std::cout << "[SIM] Creating CoralNPU simulator..." << std::endl;
    CoralNPUSimulator* simulator = CoralNPUSimulator::Create();
    if (!simulator) {
        std::cerr << "[ERROR] Failed to create simulator" << std::endl;
        return 1;
    }
    std::cout << "[SIM] Simulator created successfully" << std::endl;

    // Load Boot ROM binary (Verilator doesn't handle $readmemh in bind properly)
    std::cout << "[BOOT] Loading Boot ROM from " << BOOTROM_BIN << std::endl;
    std::ifstream bootrom_file(BOOTROM_BIN, std::ios::binary | std::ios::ate);
    if (!bootrom_file) {
        std::cerr << "[ERROR] Failed to open Boot ROM: " << BOOTROM_BIN << std::endl;
        std::cerr << "        Make sure the file is in bazel data dependencies." << std::endl;
        delete simulator;
        return 1;
    }
    std::streamsize bootrom_size = bootrom_file.tellg();
    bootrom_file.seekg(0, std::ios::beg);
    std::vector<uint8_t> bootrom_data(bootrom_size);
    if (!bootrom_file.read(reinterpret_cast<char*>(bootrom_data.data()), bootrom_size)) {
        std::cerr << "[ERROR] Failed to read Boot ROM" << std::endl;
        delete simulator;
        return 1;
    }
    std::cout << "[BOOT] Boot ROM loaded: " << bootrom_size << " bytes" << std::endl;
    
    // Write Boot ROM to Boot ROM memory region
    simulator->WriteTCM(BOOTROM_BASE, bootrom_data.size(), 
                        reinterpret_cast<const char*>(bootrom_data.data()));
    std::cout << "[BOOT] Boot ROM written to 0x" << std::hex << BOOTROM_BASE << std::dec << std::endl;

    // Open ELF file
    int fd = open(elf_file.c_str(), O_RDONLY);
    if (fd < 0) {
        std::cerr << "[ERROR] Failed to open ELF file: " << elf_file << std::endl;
        return 1;
    }

    struct stat sb;
    if (fstat(fd, &sb) != 0) {
        std::cerr << "[ERROR] Failed to stat file" << std::endl;
        close(fd);
        return 1;
    }

    auto file_size = sb.st_size;
    auto file_data = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (file_data == MAP_FAILED) {
        std::cerr << "[ERROR] Failed to mmap file" << std::endl;
        close(fd);
        return 1;
    }

    // Extract program binary from ELF (to be placed in Flash)
    std::cout << "[ELF] Loading " << elf_file << " (" << file_size << " bytes)" << std::endl;

    // Create Flash memory buffer
    std::vector<uint8_t> flash_memory(FLASH_SIZE, 0);

    // Load ELF sections into Flash buffer (simulating program stored in Flash)
    // Also track where .data section is for preloading
    size_t data_section_flash_offset = 0;
    size_t data_section_size = 0;
    uint32_t data_section_dtcm_addr = 0;
    
    CopyFn copy_fn = [&flash_memory, &data_section_flash_offset, &data_section_size, &data_section_dtcm_addr](void* dest, const void* src, size_t count) {
        uint32_t addr = static_cast<uint32_t>(reinterpret_cast<uint64_t>(dest));
        
        // Map addresses: ELF addresses (0x00000000, 0x00010000) -> Flash offset
        // The program is linked to run at 0x00000000 (ITCM), but we store it in Flash
        // Boot ROM will copy it back to ITCM
        if (addr < ITCM_SIZE) {
            // Code section -> goes to Flash offset 0
            std::memcpy(flash_memory.data() + addr, src, count);
            std::cout << "  [FLASH] Code @ 0x" << std::hex << addr
                      << " (" << std::dec << count << " bytes)" << std::endl;
        } else if (addr >= DTCM_BASE && addr < DTCM_BASE + DTCM_SIZE) {
            // Data section -> goes to Flash offset (after ITCM area)
            uint32_t flash_offset = ITCM_SIZE + (addr - DTCM_BASE);
            if (flash_offset + count <= FLASH_SIZE) {
                std::memcpy(flash_memory.data() + flash_offset, src, count);
                std::cout << "  [FLASH] Data @ 0x" << std::hex << addr
                          << " -> Flash offset 0x" << flash_offset
                          << " (" << std::dec << count << " bytes)" << std::endl;
                // Track this for later preloading
                data_section_flash_offset = flash_offset;
                data_section_size = count;
                data_section_dtcm_addr = addr;
            }
        } else {
            std::cout << "  [WARN] Ignoring section @ 0x" << std::hex << addr << std::endl;
        }
        return dest;
    };

    uint32_t entry_point = LoadElf(reinterpret_cast<uint8_t*>(file_data), copy_fn);

    munmap(file_data, file_size);
    close(fd);

    std::cout << "[ELF] ELF Entry point: 0x" << std::hex << entry_point << std::dec << std::endl;
    
    // IMPORTANT: Preload .data section to DTCM via AXI slave
    // The Boot ROM only copies code from Flash to ITCM, not data to DTCM
    // So we need to initialize DTCM before starting the CPU
    if (data_section_size > 0) {
        std::cout << "[DATA] Preloading .data section to DTCM..." << std::endl;
        std::cout << "       Flash offset 0x" << std::hex << data_section_flash_offset
                  << " -> DTCM 0x" << data_section_dtcm_addr
                  << " (" << std::dec << data_section_size << " bytes)" << std::endl;
        simulator->WriteTCM(data_section_dtcm_addr, data_section_size,
                            reinterpret_cast<const char*>(flash_memory.data() + data_section_flash_offset));
    }
    std::cout << std::endl;

    // Register Flash simulation callback (CPU reads from Flash via AXI)
    std::cout << "[SIM] Registering Flash memory callback at 0x"
              << std::hex << FLASH_BASE << std::dec << std::endl;

    static int total_flash_reads = 0;
    simulator->RegisterReadCallback([&flash_memory](const AxiAddr& addr) {
        AxiRData response;
        uint32_t address = addr.addr_bits_addr;

        // Debug: Show ALL AXI master read requests with details
        static int read_count = 0;
        if (read_count < 10) {
            std::cout << "  [AXI MASTER READ #" << read_count << "] addr=0x" << std::hex << address
                      << " len=" << (int)addr.addr_bits_len
                      << " size=" << (int)addr.addr_bits_size
                      << std::dec << std::endl;
        }
        read_count++;
        total_flash_reads++;

        response.read_data_bits_id = addr.addr_bits_id;
        response.read_data_bits_resp = 2; // SLVERR by default
        response.read_data_bits_last = 1;
        memset(&response.read_data_bits_data[0], 0, 16);

        if (address >= FLASH_BASE && address < (FLASH_BASE + FLASH_SIZE)) {
            uint32_t offset = address - FLASH_BASE;
            uint8_t* rdata = reinterpret_cast<uint8_t*>(&(response.read_data_bits_data[0]));

            // Handle the data placement based on size and address alignment
            // For size=2 (4-byte), place data at the correct lane
            uint32_t lane_offset = address & 0xF; // Position within 16-byte lane
            
            // Copy data starting from the appropriate position
            for (int i = 0; i < 16 && (offset + i - lane_offset) < flash_memory.size() && (offset + i - lane_offset) >= 0; i++) {
                if (i >= lane_offset) {
                    rdata[i] = flash_memory[offset + i - lane_offset];
                }
            }
            
            // Actually, for AXI, the entire 16-byte aligned region should be returned
            // Let me reconsider: the address should be aligned to 16-byte boundary for 128-bit bus
            uint32_t aligned_offset = offset & ~0xF; // Align to 16-byte boundary
            for (int i = 0; i < 16 && (aligned_offset + i) < flash_memory.size(); i++) {
                rdata[i] = flash_memory[aligned_offset + i];
            }
            
            response.read_data_bits_resp = 0; // OKAY

            // Debug: Show first few Flash reads (Boot ROM reading Flash)
            static int flash_read_count = 0;
            if (flash_read_count < 5) {
                std::cout << "    [FLASH READ] offset=0x" << std::hex << offset
                          << " aligned_offset=0x" << aligned_offset
                          << " data[0-3]=" << std::setw(8) << std::setfill('0')
                          << *reinterpret_cast<uint32_t*>(rdata)
                          << std::dec << std::setfill(' ') << std::endl;
                flash_read_count++;
            } else if (flash_read_count == 5) {
                std::cout << "    [FLASH READ] (further reads suppressed...)" << std::endl;
                flash_read_count++;
            }
        } else {
            std::cout << "    [AXI READ] SLVERR - address not in Flash range" << std::endl;
        }

        return response;
    });

    // Register write callback for mailbox (external mailbox at 0x20000000 conflicts with Flash)
    // Actually, mailbox is at CSR region (0x30000), so no conflict
    // But we need to capture writes to see results
    std::array<uint32_t, 4> external_mailbox = {0, 0, 0, 0};
    static int write_count = 0;
    simulator->RegisterWriteCallback([&external_mailbox](const AxiAddr& addr, const AxiWData& data) {
        uint32_t address = addr.addr_bits_addr;
        
        // Calculate the byte offset within the 16-byte data bus
        uint32_t lane_offset = address & 0xF;
        const uint8_t* write_bytes = reinterpret_cast<const uint8_t*>(&data.write_data_bits_data[0]);
        uint32_t value = *reinterpret_cast<const uint32_t*>(write_bytes + lane_offset);
        
        // Debug: show first few writes
        if (write_count < 10) {
            std::cout << "  [AXI MASTER WRITE #" << write_count << "] addr=0x" << std::hex << address
                      << " lane_offset=" << std::dec << lane_offset
                      << " data=0x" << std::hex << value << std::dec << std::endl;
            write_count++;
        }

        // Capture writes to external memory region (where mailbox might write results)
        if (address >= FLASH_BASE && address < FLASH_BASE + 0x100) {
            uint32_t offset = (address - FLASH_BASE) / 4;
            if (offset < 4) {
                external_mailbox[offset] = value;
                std::cout << "  [EXT WRITE] mailbox[" << offset << "] = 0x"
                          << std::hex << external_mailbox[offset] << std::dec << std::endl;
            }
        }

        AxiWResp resp;
        resp.write_resp_bits_id = addr.addr_bits_id;
        resp.write_resp_bits_resp = 0; // OKAY
        return resp;
    });

    // Start execution from Boot ROM
    // The Boot ROM is at 0x00040000, and it will:
    //   1. Copy from Flash (0x20000000) to ITCM (0x00000000)
    //   2. Jump to ITCM (0x00000000) to execute the program
    std::cout << std::endl;
    
    // Debug: Read back Boot ROM to verify it's loaded
    std::cout << "[DEBUG] Reading Boot ROM memory at 0x" << std::hex << BOOTROM_BASE << "..." << std::dec << std::endl;
    char bootrom_verify[48];
    simulator->ReadTCM(BOOTROM_BASE, 48, bootrom_verify);
    std::cout << "  Boot ROM first 12 words:" << std::endl;
    for (int i = 0; i < 12; i++) {
        uint32_t word = *reinterpret_cast<uint32_t*>(bootrom_verify + i * 4);
        std::cout << "    [0x" << std::hex << std::setw(5) << std::setfill('0') << (BOOTROM_BASE + i * 4)
                  << "] = 0x" << std::setw(8) << word << std::dec << std::setfill(' ') << std::endl;
    }
    std::cout << std::endl;

    std::cout << "[BOOT] Starting CPU from Boot ROM at 0x"
              << std::hex << BOOTROM_BASE << std::dec << std::endl;
    std::cout << "[BOOT] Boot ROM will:" << std::endl;
    std::cout << "       1. Copy Flash (0x20000000) -> ITCM (0x00000000)" << std::endl;
    std::cout << "       2. Jump to ITCM base (0x00000000)" << std::endl;
    std::cout << std::endl;
    
    // Debug: Check what CSR values we're writing
    std::cout << "[DEBUG] Setting PC start to 0x" << std::hex << BOOTROM_BASE << std::dec << std::endl;
    std::cout << "[DEBUG] Calling simulator->Run(0x" << std::hex << BOOTROM_BASE << std::dec << ")..." << std::endl;

    simulator->Run(BOOTROM_BASE);  // Start from Boot ROM!
    
    std::cout << "[DEBUG] Run() returned, CPU should be executing now..." << std::endl;

    // Wait for termination
    std::cout << "[CPU] Waiting for termination (timeout: " << timeout_ms << "ms)..." << std::endl;
    bool terminated = simulator->WaitForTermination(timeout_ms);

    std::cout << std::endl;
    if (terminated) {
        std::cout << "[CPU] ✓ Program terminated successfully" << std::endl;
    } else {
        std::cout << "[CPU] ✗ Timeout - program did not terminate" << std::endl;
    }

    // Read and display mailbox contents
    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  Mailbox Contents (Results)" << std::endl;
    std::cout << "========================================" << std::endl;

    CoralNPUMailbox m = simulator->ReadMailbox();

    // Display mailbox entries
    for (int i = 0; i < 4; ++i) {
        std::cout << "  mailbox[" << std::setw(2) << i << "] = 0x"
                  << std::hex << std::setw(8) << std::setfill('0') << m.message[i]
                  << " (" << std::dec << std::setfill(' ') << static_cast<int32_t>(m.message[i]) << ")"
                  << std::endl;
    }

    // Check for Fibonacci program
    if (m.message[0] == 55 && m.message[1] == 6765) {
        std::cout << std::endl;
        std::cout << "  🎉 Fibonacci results verified!" << std::endl;
        std::cout << "     fib(10) = " << m.message[0] << " ✓" << std::endl;
        std::cout << "     fib(20) = " << m.message[1] << " ✓" << std::endl;
    }
    
    // Show total Flash reads
    std::cout << std::endl;
    std::cout << "  Total Flash reads: " << total_flash_reads << std::endl;
    
    // Also display external mailbox (captures via AXI Master writes)
    std::cout << std::endl;
    std::cout << "  External Mailbox (via AXI writes):" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "  ext_mailbox[" << std::setw(2) << i << "] = 0x"
                  << std::hex << std::setw(8) << std::setfill('0') << external_mailbox[i]
                  << " (" << std::dec << std::setfill(' ') << static_cast<int32_t>(external_mailbox[i]) << ")"
                  << std::endl;
    }
    
    // Check external mailbox for Fibonacci results
    if (external_mailbox[0] == 55 && external_mailbox[1] == 6765) {
        std::cout << std::endl;
        std::cout << "  🎉 External Fibonacci results verified!" << std::endl;
        std::cout << "     fib(10) = " << external_mailbox[0] << " ✓" << std::endl;
        std::cout << "     fib(20) = " << external_mailbox[1] << " ✓" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  Boot ROM Simulation Complete" << std::endl;
    std::cout << "========================================" << std::endl;

    delete simulator;
    return terminated ? 0 : 1;
}
