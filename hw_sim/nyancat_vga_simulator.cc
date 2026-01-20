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
 * Nyancat VGA Simulator Example
 *
 * This example demonstrates the VGA peripheral by loading the nyancat_vga
 * program and displaying the animation in an SDL2 window.
 *
 * Usage:
 *   bazel run //hw_sim:nyancat_vga_simulator
 */

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

#include "hw_sim/coralnpu_simulator.h"
#include "hw_sim/vga_display.h"
#include "tests/verilator_sim/elf.h"

// VGA base address (matches VGA.scala and Parameters.scala)
static constexpr uint32_t VGA_BASE = 0x50000;
static constexpr uint32_t VGA_SIZE = 0x100;

int main(int argc, char** argv) {
  std::cout << "=== Nyancat VGA Simulator ===" << std::endl;

  // Create simulator
  CoralNPUSimulator* simulator = CoralNPUSimulator::Create();
  if (!simulator) {
    std::cerr << "Failed to create simulator" << std::endl;
    return 1;
  }

  // Create VGA display
#ifdef ENABLE_SDL2
  VgaDisplay vga;
  std::cout << "[VGA] Display initialized" << std::endl;
#else
  std::cout << "[VGA] SDL2 not enabled - display disabled" << std::endl;
#endif

  // Load ELF file
  const char* file_name = "examples/coralnpu_v2_nyancat_vga.elf";
  if (argc > 1) {
    file_name = argv[1];
  }

  int fd = open(file_name, O_RDONLY);
  if (fd < 0) {
    std::cerr << "Failed to open ELF file: " << file_name << std::endl;
    return 1;
  }

  struct stat sb;
  if (fstat(fd, &sb) != 0) {
    std::cerr << "Failed to stat file" << std::endl;
    close(fd);
    return 1;
  }

  auto file_size = sb.st_size;
  auto file_data = mmap(nullptr, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (file_data == MAP_FAILED) {
    std::cerr << "Failed to mmap file" << std::endl;
    close(fd);
    return 1;
  }

  // Copy ELF sections to simulator memory
  CopyFn copy_fn = [simulator](void* dest, const void* src, size_t count) {
    uint32_t addr = static_cast<uint32_t>(reinterpret_cast<uint64_t>(dest));
    simulator->WriteTCM(addr, count, reinterpret_cast<const char*>(src));
    return dest;
  };
  uint32_t start_pc = LoadElf(reinterpret_cast<uint8_t*>(file_data), copy_fn);

  munmap(file_data, file_size);
  close(fd);

  std::cout << "[ELF] Loaded " << file_name << " (entry: 0x"
            << std::hex << start_pc << std::dec << ")" << std::endl;

  // Register VGA MMIO callbacks
#ifdef ENABLE_SDL2
  simulator->RegisterReadCallback([&vga](const AxiAddr& addr) -> AxiRData {
    AxiRData result = {};
    uint32_t address = addr.addr_bits_addr;
    if (address >= VGA_BASE && address < VGA_BASE + VGA_SIZE) {
      result.read_data_bits_data[0] = vga.Read(address - VGA_BASE);
    }
    return result;
  });

  simulator->RegisterWriteCallback(
      [&vga](const AxiAddr& addr, const AxiWData& data) -> AxiWResp {
    uint32_t address = addr.addr_bits_addr;
    if (address >= VGA_BASE && address < VGA_BASE + VGA_SIZE) {
      vga.Write(address - VGA_BASE, data.write_data_bits_data[0]);
    }
    return {0, 0};  // OKAY
  });
#endif

  // Start program execution
  simulator->Run(start_pc);
  std::cout << "[CPU] Started execution" << std::endl;

  // Main loop: run simulation and update display
  int frame_count = 0;
  auto start_time = std::chrono::steady_clock::now();
  const int target_fps = 12;  // Nyancat animation is ~12 FPS
  const auto frame_duration = std::chrono::milliseconds(1000 / target_fps);

  while (true) {
    // Step simulation for a number of cycles
    // (This depends on your simulator implementation)

    // Check for program termination
    if (simulator->WaitForTermination(0)) {
      std::cout << "[CPU] Program terminated" << std::endl;
      break;
    }

#ifdef ENABLE_SDL2
    // Render VGA display
    vga.Render();

    // Check for user quit request
    if (vga.QuitRequested()) {
      std::cout << "[VGA] User requested quit" << std::endl;
      break;
    }

    // Frame timing
    frame_count++;
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - start_time);

    // Print FPS every second
    if (elapsed.count() >= 1000) {
      std::cout << "[VGA] " << frame_count << " FPS, Frame "
                << vga.GetCurrentFrame() << std::endl;
      frame_count = 0;
      start_time = now;
    }

    // Sleep to target ~12 FPS for animation
    std::this_thread::sleep_for(frame_duration);
#else
    // Without SDL2, just run until termination
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
#endif
  }

  std::cout << "=== Simulation complete ===" << std::endl;
  delete simulator;
  return 0;
}
