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

// Define external memory region
const uint32_t FLASH_BASE = 0x20000000;
const uint32_t FLASH_SIZE = 1024 * 1024; // 1MB

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <app_binary.bin>" << std::endl;
    return -1;
  }

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
  // This simulates the behavior of an external memory mapped at 0x20000000
  simulator->RegisterReadCallback([&](const AxiAddr& addr) {
      AxiRData response;
      uint32_t address = addr.addr_bits_addr;
      
      // Default to error
      response.read_data_bits_resp = 2; // SLVERR
      response.read_data_bits_last = 1;
      
      // Check if access is within Flash range
      if (address >= FLASH_BASE && address < (FLASH_BASE + FLASH_SIZE)) {
          uint32_t offset = address - FLASH_BASE;
          uint8_t* rdata = reinterpret_cast<uint8_t*>(&(response.read_data_bits_data[0]));
          
          // Calculate how many bytes are left in our binary
          // Note: This model is simplified. It assumes linear burst reads or single word reads.
          // In real AXI, we should handle wrap/incr and length. 
          // But our FSBL only does `lw` (length=0, size=2, width=4 bytes).
          
          // Fill 16 bytes (128-bit bus width of simulator, usually)
          // HW_SIM uses VlWide<4> which is 128-bit.
          for (int i = 0; i < 16; i++) {
              if (offset + i < app_binary.size()) {
                  rdata[i] = app_binary[offset + i];
              } else {
                  rdata[i] = 0; // Padding
              }
          }
          response.read_data_bits_resp = 0; // OKAY
      } 
      
      // Important debugging
      std::cout << "Read Access: 0x" << std::hex << address << std::dec << std::endl;
      
      return response;
  });

  // Also register a write callback that handles mailbox writes
  // The mailbox is at address 0x30000 in the external address space
  // We need to capture these writes for verification
  std::array<uint32_t, 4> mailbox_data = {0, 0, 0, 0};
  simulator->RegisterWriteCallback([&](const AxiAddr& addr, const AxiWData& data) {
      uint32_t address = addr.addr_bits_addr;
      std::cout << "Write Access: 0x" << std::hex << address << std::dec << std::endl;
      
      // Handle mailbox writes (CSR region accessed externally)
      // The app writes to 0x30000 and 0x30004
      if (address >= 0x30000 && address < 0x30010) {
          uint32_t offset = address - 0x30000;
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

  // NO WriteTCM here! We rely on BootROM -> FSBL -> Copy from Flash Callback -> ITCM

  // Run!
  // Note: For standalone boot, the Start Address passed to Run() might be irrelevant 
  // if the hardware forces start from Reset Vector, OR it might set the Reset Vector.
  // In `core_mini_axi_simulator.cc`, `Run` writes to CSRs. 
  // But we modified hardware to ignore CSR reset hold.
  // Let's pass 0x10000 to start at BootROM
  simulator->Run(0x20000000);

  // Wait for termination
  if (simulator->WaitForTermination(20000)) { // Give it enough cycles for FSBL copy
    std::cout << "Simulation Halted!" << std::endl;
  } else {
    std::cout << "Simulation Timed Out (or running indefinitely)" << std::endl;
  }

  // Use our captured mailbox_data instead of simulator->ReadMailbox()
  // since app writes go through AXI Master to our callback
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
