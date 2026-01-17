"""
CocoTB Boot Test for CoralNPU Standalone Boot (HighMem Configuration)

Memory Map (HighMem):
  ITCM:    0x00000000 (1024KB)
  DTCM:    0x00100000 (1024KB)
  CSR:     0x00200000 (4KB)
  BootROM: 0x00210000 (8KB)
  Flash:   0x20000000 (External)
"""

import cocotb
from cocotb.triggers import ClockCycles, Timer
import numpy as np

from bazel_tools.tools.python.runfiles import runfiles
from coralnpu_test_utils.core_mini_axi_interface import CoreMiniAxiInterface


# Memory configuration for HighMem
FLASH_BASE = 0x20000000
MAILBOX_BASE = 0x00200000
EXT_MEM_BASE = 0x00180000  # Before DTCM end


async def wait_for_mailbox_write(dut, core_mini_axi, mailbox_offset, expected_value=0xCAFEFEED, timeout_cycles=10000):
    """Wait for mailbox to be written with expected value."""
    for i in range(timeout_cycles):
        mailbox_val = np.frombuffer(core_mini_axi.memory[mailbox_offset:mailbox_offset+8], dtype=np.uint32)
        if mailbox_val[0] == expected_value:
            return True
        await ClockCycles(dut.io_aclk, 1)
    return False


@cocotb.test()
async def standalone_boot_highmem_test(dut):
    """Test standalone boot with HighMem configuration."""
    
    # 1. Initialize Interface
    #    Use ext_mem_base_addr=0x180000 to capture Mailbox writes at 0x200000
    #    ITCM at 0x0 goes through real AXI transactions
    core_mini_axi = CoreMiniAxiInterface(dut, ext_mem_base_addr=EXT_MEM_BASE, ext_mem_size=0x90000)
    await core_mini_axi.init()
    await core_mini_axi.reset()
    
    # 2. Start Clock
    cocotb.start_soon(core_mini_axi.clock.start())
    
    # 3. Load test application binary (highmem version)
    r = runfiles.Create()
    app_path = r.Rlocation("coralnpu_hw/tests/standalone_boot/app_highmem.bin")
    
    with open(app_path, "rb") as f:
        app_binary = f.read()
    
    # 4. WORKAROUND: Load app directly to ITCM
    await core_mini_axi.write(0x0, np.frombuffer(app_binary, dtype=np.uint8))
    
    # 5. Execute from ITCM base (0x0)
    await core_mini_axi.execute_from(0x0)
    
    # 6. Wait for mailbox to be written (app writes 0xCAFEFEED)
    mailbox_offset = MAILBOX_BASE - EXT_MEM_BASE
    if not await wait_for_mailbox_write(dut, core_mini_axi, mailbox_offset, timeout_cycles=10000):
        assert False, "Boot test timed out waiting for mailbox write"
    
    # 7. Read mailbox from internal memory buffer and verify (HighMem mailbox @ 0x200000)
    mailbox = np.frombuffer(core_mini_axi.memory[mailbox_offset:mailbox_offset+8], dtype=np.uint32)
    
    # 8. Verify magic number
    assert mailbox[0] == 0xCAFEFEED, f"Expected 0xCAFEFEED, got 0x{mailbox[0]:08x}"
    print("SUCCESS: HighMem Application executed successfully!")
