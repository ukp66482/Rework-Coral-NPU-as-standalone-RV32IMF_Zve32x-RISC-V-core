import cocotb
import numpy as np

from bazel_tools.tools.python.runfiles import runfiles
from coralnpu_test_utils.core_mini_axi_interface import CoreMiniAxiInterface

@cocotb.test()
async def core_mini_axi_tutorial(dut):
    """Testbench to run your Coral NPU program as a Standalone Processor."""
    
    # 1. Initialize Interface
    core_mini_axi = CoreMiniAxiInterface(dut)
    await core_mini_axi.init()
    
    # 2. Start Clock, but keep Reset asserted (True/Low Active)
    #    We assume aresetn is active low (0 = reset).
    cocotb.start_soon(core_mini_axi.clock.start())
    dut.aresetn.value = 0  # Hold Reset! Do not let the Core run yet!
    
    # 3. Prepare ELF file
    r = runfiles.Create()
    elf_path = r.Rlocation("coralnpu_hw/tests/cocotb/tutorial/coralnpu_v2_program.elf")
    
    # 4. [CRITICAL] Pre-load Memory (ITCM/DTCM)
    #    Since we modified the hardware for Autonomous Boot, the Core will fetch
    #    from 0x0 immediately upon Reset release. We MUST have code there beforehand.
    #    We perform AXI writes while the Core is held in reset.
    with open(elf_path, "rb") as f:
        # load_elf uses AXI Write Transactions under the hood.
        # Ensure your AXI Slave interface is responsive even when Core is in reset.
        entry_point = await core_mini_axi.load_elf(f) 
        
        # Look up symbol addresses for data placement
        inputs1_addr = core_mini_axi.lookup_symbol(f, "input1_buffer")
        inputs2_addr = core_mini_axi.lookup_symbol(f, "input2_buffer")
        outputs_addr = core_mini_axi.lookup_symbol(f, "output_buffer")

    # Write test data to buffers
    input1_data = np.arange(8, dtype=np.uint32)
    input2_data = 8994 * np.ones(8, dtype=np.uint32)
    await core_mini_axi.write(inputs1_addr, input1_data)
    await core_mini_axi.write(inputs2_addr, input2_data)

    print("Memory Pre-loaded inside Reset window. Releasing Reset now...")

    # 5. [CRITICAL] Release Reset -> Core Starts (Autonomous Boot)
    #    We DO NOT call core_mini_axi.execute_from(entry_point) anymore.
    #    Because we modified the RTL, releasing connection reset (aresetn=1) 
    #    will automatically de-assert the internal soft-reset and clock-gate.
    await cocotb.triggers.Timer(100, units="ns") # Short delay for stability
    dut.aresetn.value = 1  # Release the Kraken!
    
    # 6. Wait for Core execution to finish (Halted)
    #    The software should end with a WFI or ebreak instruction, signaling halt.
    await core_mini_axi.wait_for_halted()

    # 7. Verify Results
    rdata = (await core_mini_axi.read(outputs_addr, 4 * 8)).view(np.uint32)
    print(f"I got {rdata}")