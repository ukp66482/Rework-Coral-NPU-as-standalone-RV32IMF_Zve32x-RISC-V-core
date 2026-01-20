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
 * CoralNPU Boot ROM Fibonacci Test
 *
 * This test verifies the complete Boot ROM boot flow with Fibonacci:
 *   1. Program binary is loaded to Flash (0x20000000)
 *   2. CPU starts from Boot ROM (0x00040000)
 *   3. Boot ROM copies from Flash to ITCM (0x00000000)
 *   4. Boot ROM jumps to ITCM to execute the program
 *   5. Fibonacci writes results to mailbox
 *   6. Test verifies mailbox results
 *
 * This is the AUTHENTIC boot process using Boot ROM.
 *
 * Usage:
 *   bazel test //hw_sim:fibonacci_bootrom_test --test_output=all
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
constexpr uint32_t FLASH_BASE = 0x20000000;
constexpr uint32_t FLASH_SIZE = 1 * 1024 * 1024;  // 1MB

// Boot ROM binary path
const char* BOOTROM_BIN = "sw/bootrom/boot_default.bin";

// Expected Fibonacci results
constexpr uint32_t EXPECTED_FIB_10 = 55;
constexpr uint32_t EXPECTED_FIB_20 = 6765;
constexpr uint32_t EXPECTED_MAGIC = 0xF1B0ACC1;
constexpr uint32_t EXPECTED_FIB_15 = 610;

// Flash memory buffer (simulated external Flash)
static std::vector<uint8_t> flash_memory(FLASH_SIZE, 0);
static uint32_t flash_read_count = 0;
static std::array<uint32_t, 4> external_mailbox = {0, 0, 0, 0};
static int write_count = 0;

int main(int argc, char** argv) {
  std::cout << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "  CoralNPU Boot ROM Fibonacci Test" << std::endl;
  std::cout << "  (Authentic Boot Process)" << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << std::endl;

  // Create simulator
  std::cout << "[SIM] Creating CoralNPU simulator..." << std::endl;
  CoralNPUSimulator* simulator = CoralNPUSimulator::Create();
  if (!simulator) {
    std::cerr << "[ERROR] Failed to create simulator" << std::endl;
    return 1;
  }
  std::cout << "[SIM] Simulator created successfully" << std::endl;

  // Load Boot ROM binary
  std::cout << "[BOOT] Loading Boot ROM from " << BOOTROM_BIN << std::endl;
  std::ifstream bootrom_file(BOOTROM_BIN, std::ios::binary | std::ios::ate);
  if (!bootrom_file) {
    std::cerr << "[ERROR] Failed to open Boot ROM: " << BOOTROM_BIN << std::endl;
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

  // Write Boot ROM to memory
  simulator->WriteTCM(BOOTROM_BASE, bootrom_data.size(),
                      reinterpret_cast<const char*>(bootrom_data.data()));
  std::cout << "[BOOT] Boot ROM written to 0x" << std::hex << BOOTROM_BASE << std::dec << std::endl;

  // Load Fibonacci ELF
  std::string elf_file = "examples/coralnpu_v2_fibonacci.elf";
  std::cout << "[ELF] Loading " << elf_file << std::endl;

  int fd = open(elf_file.c_str(), O_RDONLY);
  if (fd < 0) {
    std::cerr << "[ERROR] Failed to open ELF file: " << elf_file << std::endl;
    delete simulator;
    return 1;
  }

  struct stat sb;
  if (fstat(fd, &sb) != 0) {
    std::cerr << "[ERROR] Failed to stat file" << std::endl;
    close(fd);
    delete simulator;
    return 1;
  }

  auto file_size = sb.st_size;
  auto file_data = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (file_data == MAP_FAILED) {
    std::cerr << "[ERROR] Failed to mmap file" << std::endl;
    close(fd);
    delete simulator;
    return 1;
  }

  std::cout << "[ELF] Loaded " << file_size << " bytes" << std::endl;

  // Track data section for preloading to DTCM
  size_t data_section_flash_offset = 0;
  size_t data_section_size = 0;
  uint32_t data_section_dtcm_addr = 0;

  // Load ELF sections into Flash buffer
  CopyFn copy_fn = [&](void* dest, const void* src, size_t count) {
    uint32_t addr = static_cast<uint32_t>(reinterpret_cast<uint64_t>(dest));

    if (addr < ITCM_SIZE) {
      // Code section -> goes to Flash offset 0
      std::memcpy(flash_memory.data() + addr, src, count);
      std::cout << "  [FLASH] Code @ 0x" << std::hex << addr
                << " (" << std::dec << count << " bytes)" << std::endl;
    } else if (addr >= DTCM_BASE && addr < DTCM_BASE + DTCM_SIZE) {
      // Data section -> store in Flash for tracking
      uint32_t flash_offset = ITCM_SIZE + (addr - DTCM_BASE);
      if (flash_offset + count <= FLASH_SIZE) {
        std::memcpy(flash_memory.data() + flash_offset, src, count);
        std::cout << "  [FLASH] Data @ 0x" << std::hex << addr
                  << " -> Flash offset 0x" << flash_offset
                  << " (" << std::dec << count << " bytes)" << std::endl;
        data_section_flash_offset = flash_offset;
        data_section_size = count;
        data_section_dtcm_addr = addr;
      }
    }
    return dest;
  };

  uint32_t entry_point = LoadElf(reinterpret_cast<uint8_t*>(file_data), copy_fn);
  munmap(file_data, file_size);
  close(fd);

  std::cout << "[ELF] Entry point: 0x" << std::hex << entry_point << std::dec << std::endl;

  // Preload .data section to DTCM (Boot ROM only copies code)
  if (data_section_size > 0) {
    std::cout << "[DATA] Preloading .data section to DTCM..." << std::endl;
    simulator->WriteTCM(data_section_dtcm_addr, data_section_size,
                        reinterpret_cast<const char*>(flash_memory.data() + data_section_flash_offset));
  }

  // Register Flash read callback (CPU reads from Flash via AXI Master)
  std::cout << "[SIM] Registering Flash memory callback at 0x"
            << std::hex << FLASH_BASE << std::dec << std::endl;

  simulator->RegisterReadCallback([](const AxiAddr& addr) {
    AxiRData response;
    uint32_t address = addr.addr_bits_addr;

    response.read_data_bits_id = addr.addr_bits_id;
    response.read_data_bits_resp = 2;  // SLVERR by default
    response.read_data_bits_last = 1;
    memset(&response.read_data_bits_data[0], 0, 16);

    if (address >= FLASH_BASE && address < (FLASH_BASE + FLASH_SIZE)) {
      uint32_t offset = address - FLASH_BASE;
      uint8_t* rdata = reinterpret_cast<uint8_t*>(&(response.read_data_bits_data[0]));

      // Align to 16-byte boundary for 128-bit bus
      uint32_t aligned_offset = offset & ~0xF;
      for (int i = 0; i < 16 && (aligned_offset + i) < flash_memory.size(); i++) {
        rdata[i] = flash_memory[aligned_offset + i];
      }
      response.read_data_bits_resp = 0;  // OKAY
      flash_read_count++;
    }

    return response;
  });

  // Register write callback to capture mailbox writes
  simulator->RegisterWriteCallback([](const AxiAddr& addr, const AxiWData& data) {
    uint32_t address = addr.addr_bits_addr;
    uint32_t lane_offset = address & 0xF;
    const uint8_t* write_bytes = reinterpret_cast<const uint8_t*>(&data.write_data_bits_data[0]);
    uint32_t value = *reinterpret_cast<const uint32_t*>(write_bytes + lane_offset);

    // Capture writes to external memory region
    if (address >= FLASH_BASE && address < FLASH_BASE + 0x100) {
      uint32_t offset = (address - FLASH_BASE) / 4;
      if (offset < 4) {
        external_mailbox[offset] = value;
        if (write_count < 10) {
          std::cout << "  [EXT WRITE] mailbox[" << offset << "] = 0x"
                    << std::hex << value << std::dec << std::endl;
          write_count++;
        }
      }
    }

    AxiWResp resp;
    resp.write_resp_bits_id = addr.addr_bits_id;
    resp.write_resp_bits_resp = 0;  // OKAY
    return resp;
  });

  // Start execution from Boot ROM
  std::cout << std::endl;
  std::cout << "[BOOT] Starting CPU from Boot ROM at 0x"
            << std::hex << BOOTROM_BASE << std::dec << std::endl;
  std::cout << "[BOOT] Boot ROM will:" << std::endl;
  std::cout << "       1. Copy Flash (0x20000000) -> ITCM (0x00000000)" << std::endl;
  std::cout << "       2. Jump to ITCM base (0x00000000)" << std::endl;
  std::cout << std::endl;

  // Run simulation from Boot ROM
  simulator->Run(BOOTROM_BASE);

  // Wait for termination
  int timeout_ms = 30000;  // 30 seconds
  std::cout << "[CPU] Waiting for termination (timeout: " << timeout_ms << "ms)..." << std::endl;
  bool terminated = simulator->WaitForTermination(timeout_ms);

  std::cout << std::endl;
  if (terminated) {
    std::cout << "[CPU] Program terminated successfully" << std::endl;
  } else {
    std::cout << "[CPU] Timeout - program did not terminate" << std::endl;
  }

  // Read mailbox results
  std::cout << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "  Mailbox Contents (Results)" << std::endl;
  std::cout << "========================================" << std::endl;

  CoralNPUMailbox m = simulator->ReadMailbox();

  for (int i = 0; i < 4; ++i) {
    std::cout << "  mailbox[" << i << "] = 0x"
              << std::hex << std::setw(8) << std::setfill('0') << m.message[i]
              << " (" << std::dec << std::setfill(' ') << static_cast<int32_t>(m.message[i]) << ")"
              << std::endl;
  }

  std::cout << std::endl;
  std::cout << "  Total Flash reads: " << flash_read_count << std::endl;

  // Verify results
  std::cout << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << "  Test Verification" << std::endl;
  std::cout << "========================================" << std::endl;

  bool pass = true;

  if (m.message[0] != EXPECTED_FIB_10) {
    std::cerr << "  FAIL: fib(10) = " << m.message[0] << ", expected " << EXPECTED_FIB_10 << std::endl;
    pass = false;
  } else {
    std::cout << "  PASS: fib(10) = " << m.message[0] << std::endl;
  }

  if (m.message[1] != EXPECTED_FIB_20) {
    std::cerr << "  FAIL: fib(20) = " << m.message[1] << ", expected " << EXPECTED_FIB_20 << std::endl;
    pass = false;
  } else {
    std::cout << "  PASS: fib(20) = " << m.message[1] << std::endl;
  }

  if (m.message[2] != EXPECTED_MAGIC) {
    std::cerr << "  FAIL: magic = 0x" << std::hex << m.message[2]
              << ", expected 0x" << EXPECTED_MAGIC << std::dec << std::endl;
    pass = false;
  } else {
    std::cout << "  PASS: magic = 0x" << std::hex << m.message[2] << std::dec << std::endl;
  }

  if (m.message[3] != EXPECTED_FIB_15) {
    std::cerr << "  FAIL: fib(15) = " << m.message[3] << ", expected " << EXPECTED_FIB_15 << std::endl;
    pass = false;
  } else {
    std::cout << "  PASS: fib(15) = " << m.message[3] << std::endl;
  }

  std::cout << std::endl;
  std::cout << "========================================" << std::endl;
  if (pass) {
    std::cout << "  fibonacci_bootrom_test PASSED" << std::endl;
  } else {
    std::cout << "  fibonacci_bootrom_test FAILED" << std::endl;
  }
  std::cout << "========================================" << std::endl;
  std::cout << std::endl;

  delete simulator;
  return pass ? 0 : 1;
}
