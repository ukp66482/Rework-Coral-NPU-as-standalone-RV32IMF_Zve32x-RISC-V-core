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

load("@coralnpu_hw//third_party/python:requirements.bzl", "requirement")
load("//rules:coco_tb.bzl", "cocotb_test_suite", "verilator_cocotb_model")
load(
    "//tests/cocotb:build_defs.bzl",
    "VERILATOR_BUILD_ARGS",
)

package(default_visibility = ["//visibility:public"])

# VGA Standalone Wrapper Verilator Model
verilator_cocotb_model(
    name = "vga_standalone_wrapper_model",
    trace = True,  # Enable waveform tracing for debug
    cflags = VERILATOR_BUILD_ARGS,
    hdl_toplevel = "VgaStandaloneWrapper",
    verilog_source = "//hdl/chisel/src/peripherals:VgaStandaloneWrapper.sv",
    verilog_deps = [
        "//hdl/chisel/src/peripherals:VGA.sv",
        "//hdl/verilog:TrueDualPortRAM32.v",
    ],
)

# VGA Test Cases
VGA_TESTCASES = [
    "vga_id_register_test",
    "vga_palette_test",
    "vga_framebuffer_upload_test",
    "vga_control_enable_test",
    "vga_timing_test",
    "vga_nyancat_animation_test",
]

# VGA Cocotb Test Suite
cocotb_test_suite(
    name = "vga_cocotb",
    simulators = [
        "verilator",
    ],
    testcases = VGA_TESTCASES,
    testcases_vname = "VGA_TESTCASES",
    tests_kwargs = {
        "waves": True,
        "seed": "42",
        "test_module": ["vga_test.py"],
        "size": "small",
        "hdl_toplevel": "VgaStandaloneWrapper",
    },
    verilator_model = ":vga_standalone_wrapper_model",
)
