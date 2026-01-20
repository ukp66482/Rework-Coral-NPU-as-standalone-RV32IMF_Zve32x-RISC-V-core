# Copyright 2025 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
CocoTB Boot ROM Fibonacci Test for CoralNPU

This test verifies the complete Boot ROM boot flow:
1. CPU starts from Boot ROM (0x40000)
2. Boot ROM reads program from Flash (0x20000000) via AXI Master
3. Boot ROM copies program to ITCM (0x0)
4. Boot ROM jumps to ITCM to execute Fibonacci program
5. Fibonacci writes results to mailbox (0x20000000)
6. Test verifies mailbox results

Memory Map:
  ITCM:    0x00000000 (8KB)  - Instruction memory
  DTCM:    0x00010000 (32KB) - Data memory  
  CSR:     0x00030000 (4KB)  - Control/Status registers
  BootROM: 0x00040000 (8KB)  - Boot ROM code
  Flash:   0x20000000        - External Flash (AXI Master simulated)

Expected Results:
  mailbox[0] = fib(10) = 55
  mailbox[1] = fib(20) = 6765
  mailbox[2] = 0xF1B0ACC1 (Magic marker)
  mailbox[3] = fib(15) = 610

Note: Boot ROM only copies code (ITCM). We need to preload .data section
(DTCM) before execution, since it contains the mailbox pointer variable.
"""

import cocotb
from cocotb.triggers import ClockCycles, Timer, RisingEdge
import numpy as np
import struct

from bazel_tools.tools.python.runfiles import runfiles
from coralnpu_test_utils.core_mini_axi_interface import CoreMiniAxiInterface


# Memory configuration
ITCM_BASE = 0x00000000
ITCM_SIZE = 0x2000       # 8KB
DTCM_BASE = 0x00010000
DTCM_SIZE = 0x8000       # 32KB
CSR_BASE = 0x00030000
BOOTROM_BASE = 0x00040000
FLASH_BASE = 0x20000000

# Expected Fibonacci results
EXPECTED_FIB_10 = 55
EXPECTED_FIB_20 = 6765
EXPECTED_MAGIC = 0xF1B0ACC1
EXPECTED_FIB_15 = 610


@cocotb.test()
async def fibonacci_bootrom_test(dut):
    """
    Test Fibonacci program execution via Boot ROM.
    
    This test uses the REAL Boot ROM flow with ITCM + DTCM loading:
    1. Load code to Flash offset 0 (Boot ROM copies to ITCM)
    2. Load .data to Flash offset 0x2000 (Boot ROM copies to DTCM)
    3. Set PC start to Boot ROM (0x40000)
    4. Boot ROM reads from Flash via AXI Master
    5. Boot ROM copies code to ITCM (8KB) and .data to DTCM (256 bytes)
    6. Boot ROM jumps to ITCM
    7. Fibonacci executes and writes to mailbox
    8. Verify mailbox results
    
    Flash Layout (matching Boot ROM expectations):
      Flash + 0x0000: Code  -> ITCM 0x00000000 (8KB)
      Flash + 0x2000: Data  -> DTCM 0x00010000 (256 bytes)
    
    This is the FULLY REALISTIC boot flow - no test-side DTCM preloading!
    """
    
    # Initialize core interface
    # ext_mem_base_addr=0x20000000 is where:
    # - Boot ROM reads program FROM (Flash simulation)
    # - Fibonacci writes results TO (Mailbox)
    core = CoreMiniAxiInterface(dut, ext_mem_base_addr=FLASH_BASE, ext_mem_size=0x20000)
    await core.init()
    await core.reset()
    
    # Start clock
    cocotb.start_soon(core.clock.start())
    
    # Load Fibonacci program binary
    r = runfiles.Create()
    app_path = r.Rlocation("coralnpu_hw/examples/coralnpu_v2_fibonacci.bin")
    
    with open(app_path, "rb") as f:
        app_binary = f.read()
    
    cocotb.log.info(f"Loaded {len(app_binary)} bytes from Fibonacci binary")
    
    # Binary structure:
    # - Code (ITCM): binary offset 0x0000 - 0x1FFF (8KB)
    # - Gap: binary offset 0x2000 - 0xFFFF (zero padding)
    # - Data (DTCM): binary offset 0x10000+ (.data section)
    #
    # Flash Layout (what Boot ROM expects):
    # - Flash + 0x0000: Code (8KB) -> copied to ITCM by Boot ROM
    # - Flash + 0x2000: Data (256B) -> copied to DTCM by Boot ROM
    
    # Load code section to Flash offset 0 (Boot ROM copies to ITCM)
    code_size = min(len(app_binary), ITCM_SIZE)
    core.memory[0:code_size] = np.frombuffer(app_binary[:code_size], dtype=np.uint8)
    cocotb.log.info(f"Loaded {code_size} bytes of code to Flash @ 0x{FLASH_BASE:08X}")
    
    # Load .data section to Flash offset 0x2000 (Boot ROM copies to DTCM)
    # In binary, .data is at offset 0x10000; we put it at Flash+0x2000 for Boot ROM
    FLASH_DATA_OFFSET = ITCM_SIZE  # 0x2000 = 8KB
    if len(app_binary) > DTCM_BASE:
        data_binary_offset = DTCM_BASE  # 0x10000 in binary
        data_size = min(len(app_binary) - data_binary_offset, 256)  # Boot ROM copies 256 bytes
        
        data_section = app_binary[data_binary_offset:data_binary_offset + data_size]
        core.memory[FLASH_DATA_OFFSET:FLASH_DATA_OFFSET + data_size] = np.frombuffer(data_section, dtype=np.uint8)
        cocotb.log.info(f"Loaded {data_size} bytes of .data to Flash @ 0x{FLASH_BASE + FLASH_DATA_OFFSET:08X}")
        cocotb.log.info(f"Boot ROM will copy: Flash+0x2000 -> DTCM 0x{DTCM_BASE:08X}")
    else:
        cocotb.log.info("No .data section found in binary")
    
    # Start execution from Boot ROM (0x40000)
    # This sets pcStart CSR and releases reset
    await core.execute_from(BOOTROM_BASE)
    cocotb.log.info(f"Starting execution from Boot ROM @ 0x{BOOTROM_BASE:08X}")
    
    # Wait for Boot ROM copy + Fibonacci execution
    # Boot ROM copies 8KB (~8000 cycles) + Fibonacci (~25000 cycles)
    # Give extra time for safety
    cocotb.log.info("Waiting for Boot ROM copy and Fibonacci computation...")
    
    # Wait in chunks and check for WFI
    for i in range(10):
        await ClockCycles(dut.io_aclk, 5000)
        # Check if CPU has reached WFI
        if dut.io_wfi.value == 1:
            cocotb.log.info(f"CPU reached WFI after {(i+1)*5000} cycles")
            break
    else:
        cocotb.log.warning("CPU did not reach WFI within 50000 cycles")
    
    # Read mailbox results from memory buffer
    # Fibonacci writes to 0x20000000, which is captured in core.memory[0:]
    # Note: After Boot ROM copy, the program data is overwritten by mailbox writes
    mailbox_data = np.frombuffer(core.memory[0:16], dtype=np.uint32)
    
    # Print results in the expected format (matching standalone_boot_test style)
    print(f"\nFIBONACCI @ 0x{FLASH_BASE:08X}: [{mailbox_data[0]} {mailbox_data[1]} 0x{mailbox_data[2]:08X} {mailbox_data[3]}]", flush=True)
    print("", flush=True)
    
    # Detailed output
    print(f"mailbox[0] = fib(10) = {mailbox_data[0]} (expected: {EXPECTED_FIB_10})", flush=True)
    print(f"mailbox[1] = fib(20) = {mailbox_data[1]} (expected: {EXPECTED_FIB_20})", flush=True)
    print(f"mailbox[2] = magic   = 0x{mailbox_data[2]:08X} (expected: 0x{EXPECTED_MAGIC:08X})", flush=True)
    print(f"mailbox[3] = fib(15) = {mailbox_data[3]} (expected: {EXPECTED_FIB_15})", flush=True)
    
    # Verify results
    assert mailbox_data[0] == EXPECTED_FIB_10, f"fib(10): expected {EXPECTED_FIB_10}, got {mailbox_data[0]}"
    assert mailbox_data[1] == EXPECTED_FIB_20, f"fib(20): expected {EXPECTED_FIB_20}, got {mailbox_data[1]}"
    assert mailbox_data[2] == EXPECTED_MAGIC, f"Magic: expected 0x{EXPECTED_MAGIC:08X}, got 0x{mailbox_data[2]:08X}"
    assert mailbox_data[3] == EXPECTED_FIB_15, f"fib(15): expected {EXPECTED_FIB_15}, got {mailbox_data[3]}"
    
    print("", flush=True)
    print("fibonacci_bootrom_test passed", flush=True)
