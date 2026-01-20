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

"""Fibonacci Boot ROM Test - Tests Boot ROM boot flow with Fibonacci program."""

load("//rules:coco_tb.bzl", "cocotb_test_suite")
load(
    "//tests/cocotb:build_defs.bzl",
    "VERILATOR_BUILD_ARGS",
)

package(default_visibility = ["//visibility:public"])

# Test binaries for fibonacci boot ROM tests
filegroup(
    name = "fibonacci_bootrom_test_binaries",
    srcs = [
        "//examples:coralnpu_v2_fibonacci.bin",
    ],
)

# BEGIN_TESTCASES_FOR_fibonacci_bootrom
FIBONACCI_BOOTROM_TESTCASES = [
    "fibonacci_bootrom_test",
]
# END_TESTCASES_FOR_fibonacci_bootrom

# Fibonacci Boot ROM test - Uses real Boot ROM flow
# Boot ROM reads program from Flash (AXI Master) and copies to ITCM
cocotb_test_suite(
    name = "fibonacci_bootrom_cocotb",
    simulators = [
        "verilator",
    ],
    testcases = FIBONACCI_BOOTROM_TESTCASES,
    testcases_vname = "FIBONACCI_BOOTROM_TESTCASES",
    tests_kwargs = {
        "waves": False,
        "hdl_toplevel": "CoreMiniAxi",
        "seed": "42",
        "test_module": ["fibonacci_bootrom_test.py"],
        "deps": [
            "//coralnpu_test_utils:core_mini_axi_sim_interface",
            "@bazel_tools//tools/python/runfiles",
        ],
        "data": [
            "//examples:coralnpu_v2_fibonacci.bin",
        ],
        "size": "small",
        "default_testcase_size": "small",
    },
    verilator_model = "//tests/cocotb:core_mini_axi_model",
)
