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
 * CoralNPU Program Runner
 * 
 * A general-purpose runner for executing RISC-V programs on CoralNPU.
 * This uses the full CoralNPU simulator (including CPU, memory, and peripherals).
 * 
 * Usage:
 *   bazel run //hw_sim:coralnpu_runner -- <program_name> [timeout_ms]
 * 
 * Example:
 *   bazel run //hw_sim:coralnpu_runner -- fibonacci
 *   bazel run //hw_sim:coralnpu_runner -- quicksort 5000
 */

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#include "hw_sim/coralnpu_simulator.h"
#include "tests/verilator_sim/elf.h"

// Available programs (relative paths for bazel runfiles)
const std::map<std::string, std::string> kPrograms = {
    {"fibonacci", "examples/coralnpu_v2_fibonacci.elf"},
    {"quicksort", "examples/coralnpu_v2_quicksort.elf"},
    {"hello", "examples/coralnpu_v2_hello_world_add_floats.elf"},
    {"add_floats", "examples/coralnpu_v2_hello_world_add_floats.elf"},
    {"mailbox", "hw_sim/mailbox_example.elf"},
};

void print_usage(const char* prog) {
    std::cout << "Usage: " << prog << " <program_name> [timeout_ms]" << std::endl;
    std::cout << std::endl;
    std::cout << "Available programs:" << std::endl;
    for (const auto& [name, path] : kPrograms) {
        std::cout << "  " << name << " -> " << path << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  program_name  Name of the program to run (or full path to .elf)" << std::endl;
    std::cout << "  timeout_ms    Timeout in milliseconds (default: 10000)" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  " << prog << " fibonacci" << std::endl;
    std::cout << "  " << prog << " quicksort 5000" << std::endl;
}

int main(int argc, char** argv) {
    std::cout << "========================================" << std::endl;
    std::cout << "  CoralNPU Program Runner" << std::endl;
    std::cout << "  RV32IMF_Zve32x RISC-V Core" << std::endl;
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

    // Load ELF into simulator memory
    std::cout << "[ELF] Loading " << elf_file << " (" << file_size << " bytes)" << std::endl;
    
    CopyFn copy_fn = [simulator](void* dest, const void* src, size_t count) {
        uint32_t addr = static_cast<uint32_t>(reinterpret_cast<uint64_t>(dest));
        simulator->WriteTCM(addr, count, reinterpret_cast<const char*>(src));
        return dest;
    };
    
    uint32_t start_pc = LoadElf(reinterpret_cast<uint8_t*>(file_data), copy_fn);

    munmap(file_data, file_size);
    close(fd);

    std::cout << "[ELF] Entry point: 0x" << std::hex << start_pc << std::dec << std::endl;
    std::cout << std::endl;

    // Start execution
    std::cout << "[CPU] Starting execution..." << std::endl;
    simulator->Run(start_pc);

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
    
    // Display mailbox entries (CoralNPUMailbox has 4 entries)
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
    } else if (m.message[2] == 0xF1B0ACC1) {
        // Has fibonacci marker but values different
        std::cout << std::endl;
        std::cout << "  📊 Fibonacci results:" << std::endl;
        std::cout << "     Result 1 = " << m.message[0] << std::endl;
        std::cout << "     Result 2 = " << m.message[1] << std::endl;
    }

    // Check for mailbox example (0xDEADBEEF)
    if (m.message[0] == 0xDEADBEEF) {
        std::cout << std::endl;
        std::cout << "  🎉 Mailbox example verified!" << std::endl;
        std::cout << "     mailbox[0] = 0xDEADBEEF ✓" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  Simulation complete" << std::endl;
    std::cout << "========================================" << std::endl;

    delete simulator;
    return terminated ? 0 : 1;
}
