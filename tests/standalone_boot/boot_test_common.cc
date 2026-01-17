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

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdint>

#include "hw_sim/coralnpu_simulator.h"

// Memory configuration based on build flags
#ifdef HIGHMEM_CONFIG
  // HighMem Configuration
  const uint32_t MAILBOX_BASE = 0x00200000;
  const uint32_t ITCM_SIZE = 1024 * 1024;  // 1MB
  const char* CONFIG_NAME = "HighMem";
#else
  // Default Configuration
  const uint32_t MAILBOX_BASE = 0x00030000;
  const uint32_t ITCM_SIZE = 8 * 1024;     // 8KB
  const char* CONFIG_NAME = "Default";
#endif

// External Flash is the same for both configs
const uint32_t FLASH_BASE = 0x20000000;
const uint32_t FLASH_SIZE = 1024 * 1024; // 1MB

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <app_binary.bin>" << std::endl;
    return -1;
  }

  std::cout << "=== Boot Test (" << CONFIG_NAME << " Configuration) ===" << std::endl;
  std::cout << "MAILBOX_BASE: 0x" << std::hex << MAILBOX_BASE << std::dec << std::endl;
  std::cout << "ITCM_SIZE: " << (ITCM_SIZE / 1024) << " KB" << std::endl;

  // Read application binary
  std::ifstream bin_file(argv[1], std::ios::binary | std::ios::ate);
  if (!bin_file) {
    std::cerr << "Failed to open " << argv[1] << std::endl;
    return -1;
  }
  std::streamsize bin_size = bin_file.tellg();
  bin_file.seekg(0, std::ios::beg);
  std::vector<uint8_t> app_binary(bin_size);
  if (!bin_file.read(reinterpret_cast<char*>(app_binary.data()), bin_size)) {
     std::cerr << "Failed to read binary" << std::endl;
     return -1;
  }
  std::cout << "Loaded App Binary: " << bin_size << " bytes" << std::endl;

  CoralNPUSimulator* simulator = CoralNPUSimulator::Create();

  // Register Flash Simulation Callback
  simulator->RegisterReadCallback([&](const AxiAddr& addr) {
      AxiRData response;
      uint32_t address = addr.addr_bits_addr;
      
      response.read_data_bits_resp = 2; // SLVERR
      response.read_data_bits_last = 1;
      
      if (address >= FLASH_BASE && address < (FLASH_BASE + FLASH_SIZE)) {
          uint32_t offset = address - FLASH_BASE;
          uint8_t* rdata = reinterpret_cast<uint8_t*>(&(response.read_data_bits_data[0]));
          
          for (int i = 0; i < 16; i++) {
              if (offset + i < app_binary.size()) {
                  rdata[i] = app_binary[offset + i];
              } else {
                  rdata[i] = 0;
              }
          }
          response.read_data_bits_resp = 0; // OKAY
      } 
      
      std::cout << "Read Access: 0x" << std::hex << address << std::dec << std::endl;
      
      return response;
  });

  // Register write callback for mailbox
  std::array<uint32_t, 4> mailbox_data = {0, 0, 0, 0};
  simulator->RegisterWriteCallback([&](const AxiAddr& addr, const AxiWData& data) {
      uint32_t address = addr.addr_bits_addr;
      std::cout << "Write Access: 0x" << std::hex << address << std::dec << std::endl;
      
      // Handle mailbox writes based on configuration
      if (address >= MAILBOX_BASE && address < (MAILBOX_BASE + 0x10)) {
          uint32_t offset = address - MAILBOX_BASE;
          const uint8_t* write_bytes = reinterpret_cast<const uint8_t*>(&data.write_data_bits_data[0]);
          uint8_t* mailbox_bytes = reinterpret_cast<uint8_t*>(mailbox_data.data());
          for (int i = 0; i < 16 && (offset + i) < 16; i++) {
              if (data.write_data_bits_strb & (1 << i)) {
                  mailbox_bytes[offset + i] = write_bytes[i];
              }
          }
          std::cout << "  -> Mailbox updated. mailbox[0]=0x" << std::hex << mailbox_data[0] 
                    << ", mailbox[1]=0x" << mailbox_data[1] << std::dec << std::endl;
      }
      
      AxiWResp resp;
      resp.write_resp_bits_id = addr.addr_bits_id;
      resp.write_resp_bits_resp = 0;
      return resp;
  });

  // WORKAROUND: Verilator doesn't properly handle $readmemh in bind statements.
  // So we manually write the app binary to ITCM instead of relying on BootROM.
  std::cout << "Writing app binary directly to ITCM (workaround for BootROM)..." << std::endl;
  simulator->WriteTCM(0x0, app_binary.size(), reinterpret_cast<const char*>(app_binary.data()));
  std::cout << "ITCM loaded with " << app_binary.size() << " bytes" << std::endl;

  // Run!
  simulator->Run(0x20000000);

  // Wait for termination
  if (simulator->WaitForTermination(20000)) {
    std::cout << "Simulation Halted!" << std::endl;
  } else {
    std::cout << "Simulation Timed Out (or running indefinitely)" << std::endl;
  }

  std::cout << "Mailbox[0]: 0x" << std::hex << mailbox_data[0] << std::endl;
  std::cout << "Mailbox[1]: 0x" << std::hex << mailbox_data[1] << std::endl;

  bool success = (mailbox_data[0] == 0xCAFEFEED);
  if (success) {
      std::cout << "SUCCESS: Application executed successfully!" << std::endl;
      return 0;
  } else {
      std::cout << "FAILURE: Magic number mismatch." << std::endl;
      return 1;
  }
}
