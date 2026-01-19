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

load("@coralnpu_hw//third_party/python:requirements.bzl", "requirement")
load("@rules_pkg//:pkg.bzl", "pkg_zip")
load("//rules:coco_tb.bzl", "cocotb_test_suite", "verilator_cocotb_model")
load("//rules:coralnpu_v2.bzl", "coralnpu_v2_binary")
load("//rules:utils.bzl", "template_rule")
load(
    "//tests/cocotb:build_defs.bzl",
    "VCS_BUILD_ARGS",
    "VCS_DEFINES",
    "VCS_TEST_ARGS",
    "VERILATOR_BUILD_ARGS",
)
load("//tests/cocotb:wfi_targets.bzl", "get_wfi_slot_targets")

package(default_visibility = ["//visibility:public"])

verilator_cocotb_model(
    name = "core_mini_axi_standalone_model",
    trace = False,
    cflags = VERILATOR_BUILD_ARGS + [
        "-DCORALNPU_STANDALONE_TCM_INIT",
    ],
    hdl_toplevel = "CoreMiniStandaloneAxi",
    verilog_source = "//hdl/chisel/src/coralnpu:CoreMiniStandaloneAxi.sv",
)

cocotb_test_suite(
    name = "core_mini_axi_standalone_boot_cocotb",
    simulators = [
        "verilator",
    ],
    testcases = [
        "standalone_boot_writes_dtcm",
    ],
    testcases_vname = "CORE_MINI_AXI_STANDALONE_BOOT_TESTCASES",
    tests_kwargs = {
        "hdl_toplevel": "CoreMiniStandaloneAxi",
        "waves": False,
        "seed": "42",
        "test_module": ["standalone_boot_test.py"],
        "deps": [
            "//coralnpu_test_utils:core_mini_axi_sim_interface",
        ],
        "default_testcase_size": "small",
        "size": "small",
    },
    verilator_model = ":core_mini_axi_standalone_model",
)