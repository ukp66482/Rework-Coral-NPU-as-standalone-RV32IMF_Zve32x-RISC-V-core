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
load(
    "//tests/cocotb:build_defs.bzl",
    "VCS_BUILD_ARGS",
    "VCS_DEFINES",
    "VCS_TEST_ARGS",
)

# Test binaries for boot tests
filegroup(
    name = "boot_test_binaries",
    srcs = [
        "//tests/standalone_boot:app.bin",
        "//tests/standalone_boot:app_highmem.bin",
    ],
)

# BEGIN_TESTCASES_FOR_boot_test_default
BOOT_TEST_DEFAULT_TESTCASES = [
    "standalone_boot_test",
]
# END_TESTCASES_FOR_boot_test_default

# BEGIN_TESTCASES_FOR_boot_test_rvv
BOOT_TEST_RVV_TESTCASES = [
    "standalone_boot_test",
]
# END_TESTCASES_FOR_boot_test_rvv

# BEGIN_TESTCASES_FOR_boot_test_highmem
BOOT_TEST_HIGHMEM_TESTCASES = [
    "standalone_boot_highmem_test",
]
# END_TESTCASES_FOR_boot_test_highmem

# BEGIN_TESTCASES_FOR_boot_test_rvv_highmem
BOOT_TEST_RVV_HIGHMEM_TESTCASES = [
    "standalone_boot_highmem_test",
]
# END_TESTCASES_FOR_boot_test_rvv_highmem

# Default configuration boot test (non-RVV)
cocotb_test_suite(
    name = "boot_test_default",
    simulators = [
        "verilator",
        "vcs",
    ],
    testcases = BOOT_TEST_DEFAULT_TESTCASES,
    testcases_vname = "BOOT_TEST_DEFAULT_TESTCASES",
    tests_kwargs = {
        "waves": False,
        "hdl_toplevel": "CoreMiniAxi",
        "seed": "42",
        "test_module": ["boot_test.py"],
        "deps": [
            "//coralnpu_test_utils:core_mini_axi_sim_interface",
            "@bazel_tools//tools/python/runfiles",
        ],
        "data": [
            "//tests/standalone_boot:app.bin",
        ],
        "size": "small",
    },
    vcs_build_args = VCS_BUILD_ARGS,
    vcs_data = [
        "//tests/standalone_boot:app.bin",
        "//tests/cocotb:coverage_exclude.cfg",
    ],
    vcs_defines = VCS_DEFINES,
    vcs_test_args = VCS_TEST_ARGS,
    vcs_verilog_sources = ["//hdl/chisel/src/coralnpu:core_mini_axi_cc_library_verilog"],
    verilator_model = "//tests/cocotb:core_mini_axi_model",
)

# Default configuration boot test (RVV)
cocotb_test_suite(
    name = "boot_test_rvv",
    simulators = [
        "verilator",
        "vcs",
    ],
    testcases = BOOT_TEST_RVV_TESTCASES,
    testcases_vname = "BOOT_TEST_RVV_TESTCASES",
    tests_kwargs = {
        "waves": False,
        "hdl_toplevel": "RvvCoreMiniAxi",
        "seed": "42",
        "test_module": ["boot_test.py"],
        "deps": [
            "//coralnpu_test_utils:core_mini_axi_sim_interface",
            "@bazel_tools//tools/python/runfiles",
        ],
        "data": [
            "//tests/standalone_boot:app.bin",
        ],
        "size": "small",
    },
    vcs_build_args = VCS_BUILD_ARGS,
    vcs_data = [
        "//tests/standalone_boot:app.bin",
        "//tests/cocotb:coverage_exclude.cfg",
    ],
    vcs_defines = VCS_DEFINES,
    vcs_test_args = VCS_TEST_ARGS,
    vcs_verilog_sources = ["//hdl/chisel/src/coralnpu:rvv_core_mini_axi_cc_library_verilog"],
    verilator_model = "//tests/cocotb:rvv_core_mini_axi_model",
)

# HighMem configuration boot test (non-RVV)
cocotb_test_suite(
    name = "boot_test_highmem",
    simulators = [
        "verilator",
        "vcs",
    ],
    testcases = BOOT_TEST_HIGHMEM_TESTCASES,
    testcases_vname = "BOOT_TEST_HIGHMEM_TESTCASES",
    tests_kwargs = {
        "waves": False,
        "hdl_toplevel": "CoreMiniHighmemAxi",
        "seed": "42",
        "test_module": ["boot_test_highmem.py"],
        "deps": [
            "//coralnpu_test_utils:core_mini_axi_sim_interface",
            "@bazel_tools//tools/python/runfiles",
        ],
        "data": [
            "//tests/standalone_boot:app_highmem.bin",
        ],
        "size": "small",
    },
    vcs_build_args = VCS_BUILD_ARGS,
    vcs_data = [
        "//tests/standalone_boot:app_highmem.bin",
        "//tests/cocotb:coverage_exclude.cfg",
    ],
    vcs_defines = VCS_DEFINES,
    vcs_test_args = VCS_TEST_ARGS,
    vcs_verilog_sources = ["//hdl/chisel/src/coralnpu:core_mini_highmem_axi_cc_library_verilog"],
    verilator_model = "//tests/cocotb:core_mini_highmem_axi_model",
)

# HighMem configuration boot test (RVV)
cocotb_test_suite(
    name = "boot_test_rvv_highmem",
    simulators = [
        "verilator",
        "vcs",
    ],
    testcases = BOOT_TEST_RVV_HIGHMEM_TESTCASES,
    testcases_vname = "BOOT_TEST_RVV_HIGHMEM_TESTCASES",
    tests_kwargs = {
        "waves": False,
        "hdl_toplevel": "RvvCoreMiniHighmemAxi",
        "seed": "42",
        "test_module": ["boot_test_highmem.py"],
        "deps": [
            "//coralnpu_test_utils:core_mini_axi_sim_interface",
            "@bazel_tools//tools/python/runfiles",
        ],
        "data": [
            "//tests/standalone_boot:app_highmem.bin",
        ],
        "size": "small",
    },
    vcs_build_args = VCS_BUILD_ARGS,
    vcs_data = [
        "//tests/standalone_boot:app_highmem.bin",
        "//tests/cocotb:coverage_exclude.cfg",
    ],
    vcs_defines = VCS_DEFINES,
    vcs_test_args = VCS_TEST_ARGS,
    vcs_verilog_sources = ["//hdl/chisel/src/coralnpu:rvv_core_mini_highmem_axi_cc_library_verilog"],
    verilator_model = "//tests/cocotb:rvv_core_mini_highmem_axi_model",
)
