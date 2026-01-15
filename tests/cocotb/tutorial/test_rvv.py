import cocotb
import numpy as np

from bazel_tools.tools.python.runfiles import runfiles
from coralnpu_test_utils.sim_test_fixture import Fixture


@cocotb.test()
async def check_rvv_program(dut):
    """Testbench to run your Coral NPU program with RVV."""
    fixture = await Fixture.Create(dut)
    r = runfiles.Create()
    elf_path = r.Rlocation(
        "coralnpu_hw/tests/cocotb/tutorial/coralnpu_v2_program_rvv.elf")
    
    # Load symbols to find buffer addresses
    await fixture.load_elf_and_lookup_symbols(
        elf_path, ["input1_buffer", "input2_buffer", "output_buffer"])
    
    # Prepare input data
    input1 = np.arange(8, dtype=np.uint32)
    input2 = 8994 * np.ones(8, dtype=np.uint32)
    
    # Write inputs using symbol names
    # Note: write() uses symbol addresses found during lookup
    await fixture.write("input1_buffer", input1)
    await fixture.write("input2_buffer", input2)

    # Run until program halts
    await fixture.run_to_halt()

    # Verify result
    result_words = (await fixture.read("output_buffer", 32)).view(np.uint32)
    
    print(f"I got {result_words}")
    
    expected = input1 + input2
    assert np.array_equal(result_words, expected), "Result mismatch!"
