# Copyright 2026 Google LLC
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

import cocotb
import numpy as np

from cocotb.triggers import ClockCycles
from coralnpu_test_utils.core_mini_axi_interface import CoreMiniAxiInterface


@cocotb.test()
async def standalone_boot_writes_dtcm(dut):
    core = CoreMiniAxiInterface(dut)
    await core.init()
    await core.reset()
    cocotb.start_soon(core.clock.start())

    # Standalone boot image writes 1 to DTCM base (0x10000) then executes WFI.
    await ClockCycles(dut.io_aclk, 2000)

    # Debug: Read INPUT1 @ 0x10100 (should be 0,1,2,3,4,5,6,7)
    input1_addr = 0x10100
    input1_data = (await core.read(input1_addr, 4 * 8)).view(np.uint32)
    print(f"INPUT1 @ 0x{input1_addr:X}: {input1_data}", flush=True)

    # Debug: Read INPUT2 @ 0x10120 (should be 10,10,10,10,10,10,10,10)
    input2_addr = 0x10120
    input2_data = (await core.read(input2_addr, 4 * 8)).view(np.uint32)
    print(f"INPUT2 @ 0x{input2_addr:X}: {input2_data}", flush=True)

    # Read OUTPUT @ 0x10140 (should be 10,11,12,13,14,15,16,17)
    output_addr = 0x10140
    rdata = (await core.read(output_addr, 4 * 8)).view(np.uint32)
    print(f"OUTPUT @ 0x{output_addr:X}: {rdata}", flush=True)