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

load("//rules:coco_tb.bzl", "cocotb_test_suite")
load("//rules:coralnpu_v2.bzl", "coralnpu_v2_binary")
load("//rules:utils.bzl", "generate_cc_arrays")
load(
    "//tests/cocotb:build_defs.bzl",
    "VCS_BUILD_ARGS",
    "VCS_DEFINES",
    "VCS_TEST_ARGS",
)

# BEGIN_TESTCASES_FOR_tutorial
TUTORIAL_TESTCASES = [
    "core_mini_axi_tutorial",
]
# END_TESTCASES_FOR_tutorial

# BEGIN_TESTCASES_FOR_tutorial_rvv
TEST_RVV_TESTCASES = [
    "RvvCoreMiniAxi_tutorial",
]
# END_TESTCASES_FOR_tutorial_rvv


cocotb_test_suite(
    name = "test_rvv",
    simulators = [
        "verilator",
        "vcs",
    ],
    testcases = TEST_RVV_TESTCASES,
    testcases_vname = "TEST_RVV_TESTCASES",
    tests_kwargs = {
        "waves": False,
        "hdl_toplevel": "RvvCoreMiniAxi",
        "seed": "42",
        "test_module": ["test_rvv.py"],
        "deps": [
            "//coralnpu_test_utils:core_mini_axi_sim_interface",
            "//coralnpu_test_utils:sim_test_fixture",
            "@rules_python//python/runfiles",
        ],
        "data": [":coralnpu_v2_program_rvv"],
        "size": "small",
    },
    vcs_build_args = VCS_BUILD_ARGS,
    vcs_data = [
        ":coralnpu_v2_program_rvv",
        "//tests/cocotb:coverage_exclude.cfg",
    ],
    vcs_defines = VCS_DEFINES,
    vcs_test_args = VCS_TEST_ARGS,
    vcs_verilog_sources = ["//hdl/chisel/src/coralnpu:rvv_core_mini_axi_cc_library_verilog"],
    verilator_model = "//tests/cocotb:rvv_core_mini_axi_model",
)

cocotb_test_suite(
    name = "tutorial",
    simulators = [
        "verilator",
        "vcs",
    ],
    testcases = TUTORIAL_TESTCASES,
    testcases_vname = "TUTORIAL_TESTCASES",
    tests_kwargs = {
        "waves": False,
        "hdl_toplevel": "CoreMiniAxi",
        "seed": "42",
        "test_module": ["tutorial.py"],
        "deps": [
            "//coralnpu_test_utils:core_mini_axi_sim_interface",
            "@rules_python//python/runfiles",
        ],
        "data": [":coralnpu_v2_program"],
        "size": "small",
    },
    vcs_build_args = VCS_BUILD_ARGS,
    vcs_data = [
        ":coralnpu_v2_program",
        "//tests/cocotb:coverage_exclude.cfg",
    ],
    vcs_defines = VCS_DEFINES,
    vcs_test_args = VCS_TEST_ARGS,
    vcs_verilog_sources = ["//hdl/chisel/src/coralnpu:core_mini_axi_cc_library_verilog"],
    verilator_model = "//tests/cocotb:core_mini_axi_model",
)

coralnpu_v2_binary(
    name = "coralnpu_v2_program",
    srcs = ["program.cc"],
)

coralnpu_v2_binary(
    name = "coralnpu_v2_program_rvv",
    srcs = ["program_rvv.cc"],
)
