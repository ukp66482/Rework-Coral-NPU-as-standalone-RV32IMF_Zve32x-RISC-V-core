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
    data = await core.read_word(0x10000)
    value = int.from_bytes(bytes(data.tolist()), byteorder="little", signed=False)
    assert value == 1, f"Expected DTCM[0x10000]=1, got {hex(value)}"

