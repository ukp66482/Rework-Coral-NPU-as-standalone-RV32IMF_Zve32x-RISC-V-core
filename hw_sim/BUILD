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

load("//rules:coralnpu_v2.bzl", "coralnpu_v2_binary")

cc_library(
    name = "hw_primitives",
    srcs = [
        "hw_primitives.cc",
    ],
    hdrs = [
        "hw_primitives.h",
    ],
    deps = [
        "@com_google_absl//absl/types:span",
        "@verilator//:libverilator",
    ],
)

cc_library(
    name = "core_mini_axi_wrapper",
    hdrs = [
        "core_mini_axi_wrapper.h",
        "mailbox.h",
    ],
    deps = [
        ":hw_primitives",
        "//hdl/chisel/src/coralnpu:core_mini_axi_cc_library_cc",
        "//hdl/chisel/src/coralnpu:rvv_core_mini_axi_cc_library_cc",
    ],
)

cc_library(
    name = "core_mini_axi_wrapper_highmem",
    hdrs = [
        "core_mini_axi_wrapper.h",
        "mailbox.h",
    ],
    defines = ["HIGHMEM_CONFIG"],
    deps = [
        ":hw_primitives",
        "//hdl/chisel/src/coralnpu:core_mini_highmem_axi_cc_library_cc",
        "//hdl/chisel/src/coralnpu:rvv_core_mini_highmem_axi_cc_library_cc",
    ],
)

cc_library(
    name = "core_mini_axi_wrapper_rvv_highmem",
    hdrs = [
        "core_mini_axi_wrapper.h",
        "mailbox.h",
    ],
    defines = ["ENABLE_RVV", "HIGHMEM_CONFIG"],
    deps = [
        ":hw_primitives",
        "//hdl/chisel/src/coralnpu:rvv_core_mini_highmem_axi_cc_library_cc",
    ],
)

cc_binary(
    name = "core_mini_axi_wrapper_example",
    srcs = [
        "core_mini_axi_wrapper_example.cc",
    ],
    data = [
        "//tests/cocotb:wfi_slot_0.elf",
    ],
    deps = [
        ":core_mini_axi_wrapper",
        "//tests/verilator_sim:elf",
    ],
)

cc_library(
    name = "coralnpu_simulator_headers",
    hdrs = [
        "coralnpu_simulator.h",
        "mailbox.h",
    ],
    deps = [
        ":hw_primitives",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "core_mini_axi_simulator",
    srcs = ["core_mini_axi_simulator.cc"],
    linkstatic = True,
    deps = [
        ":core_mini_axi_wrapper",
        ":coralnpu_simulator_headers",
    ],
    alwayslink = True,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "core_mini_axi_simulator_highmem",
    srcs = ["core_mini_axi_simulator.cc"],
    copts = ["-DHIGHMEM_CONFIG"],
    linkstatic = True,
    deps = [
        ":core_mini_axi_wrapper_highmem",
        ":coralnpu_simulator_headers",
    ],
    alwayslink = True,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "core_mini_axi_simulator_rvv",
    srcs = ["core_mini_axi_simulator.cc"],
    copts = ["-DENABLE_RVV"],
    linkstatic = True,
    deps = [
        ":core_mini_axi_wrapper",
        ":coralnpu_simulator_headers",
    ],
    alwayslink = True,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "core_mini_axi_simulator_rvv_highmem",
    srcs = ["core_mini_axi_simulator.cc"],
    copts = ["-DENABLE_RVV", "-DHIGHMEM_CONFIG"],
    linkstatic = True,
    deps = [
        ":core_mini_axi_wrapper_rvv_highmem",
        ":coralnpu_simulator_headers",
    ],
    alwayslink = True,
    visibility = ["//visibility:public"],
)

coralnpu_v2_binary(
    name = "mailbox_example",
    srcs = [
        "mailbox_example.cc",
    ],
)

cc_binary(
    name = "core_mini_axi_simulator_example",
    srcs = [
        "core_mini_axi_simulator_example.cc",
    ],
    data = [
        ":mailbox_example.elf",
    ],
    deps = [
        ":core_mini_axi_simulator",
        "//tests/verilator_sim:elf",
    ],
)

# generate libraries for external projects
cc_binary(
    name = "libcoralnpu_simulator.so",
    linkshared = True,
    visibility = ["//visibility:public"],
    deps = [":core_mini_axi_simulator"],
)

cc_binary(
    name = "libcoralnpu_simulator_rvv.so",
    linkshared = True,
    visibility = ["//visibility:public"],
    deps = [":core_mini_axi_simulator_rvv"],
)

# VGA Display library (with SDL2 support)
cc_library(
    name = "vga_display",
    srcs = ["vga_display.cc"],
    hdrs = ["vga_display.h"],
    copts = ["-DENABLE_SDL2"],
    linkopts = ["-lSDL2"],
)

cc_library(
    name = "vga_display_no_sdl",
    srcs = ["vga_display.cc"],
    hdrs = ["vga_display.h"],
)

# Nyancat VGA Simulator with SDL2 display
cc_binary(
    name = "nyancat_vga_simulator",
    srcs = ["nyancat_vga_simulator.cc"],
    copts = ["-DENABLE_SDL2"],
    data = ["//examples:coralnpu_v2_nyancat_vga.elf"],
    linkopts = ["-lSDL2"],
    deps = [
        ":core_mini_axi_simulator",
        ":vga_display",
        "//tests/verilator_sim:elf",
    ],
)

# Nyancat VGA Simulator without SDL2 (headless mode)
cc_binary(
    name = "nyancat_vga_simulator_headless",
    srcs = ["nyancat_vga_simulator.cc"],
    data = ["//examples:coralnpu_v2_nyancat_vga.elf"],
    deps = [
        ":core_mini_axi_simulator",
        ":vga_display_no_sdl",
        "//tests/verilator_sim:elf",
    ],
)

# General-purpose CoralNPU program runner
cc_binary(
    name = "coralnpu_runner",
    srcs = ["coralnpu_runner.cc"],
    data = [
        ":mailbox_example.elf",
        "//examples:coralnpu_v2_fibonacci.elf",
        "//examples:coralnpu_v2_quicksort.elf",
        "//examples:coralnpu_v2_hello_world_add_floats.elf",
    ],
    deps = [
        ":core_mini_axi_simulator",
        "//tests/verilator_sim:elf",
    ],
)

# Boot ROM-based CoralNPU program runner (authentic boot process)
# Uses Boot ROM to copy from Flash to ITCM, then executes from ITCM
cc_binary(
    name = "coralnpu_bootrom_runner",
    srcs = ["coralnpu_bootrom_runner.cc"],
    data = [
        "//examples:coralnpu_v2_fibonacci.elf",
        "//examples:coralnpu_v2_quicksort.elf",
        "//examples:coralnpu_v2_hello_world_add_floats.elf",
        "//sw/bootrom:boot_default.bin",
    ],
    deps = [
        ":core_mini_axi_simulator",
        "//tests/verilator_sim:elf",
    ],
)

# Boot ROM Fibonacci Test (bazel test version of coralnpu_bootrom_runner)
# Verifies the AUTHENTIC boot process:
#   1. Program is loaded to Flash (0x20000000)
#   2. CPU starts from Boot ROM (0x00040000)
#   3. Boot ROM copies Flash -> ITCM
#   4. Boot ROM jumps to ITCM to execute Fibonacci
#   5. Fibonacci results are verified from mailbox
#
# Usage:
#   bazel test //hw_sim:fibonacci_bootrom_test --test_output=all
cc_test(
    name = "fibonacci_bootrom_test",
    srcs = ["fibonacci_bootrom_test.cc"],
    data = [
        "//examples:coralnpu_v2_fibonacci.elf",
        "//sw/bootrom:boot_default.bin",
    ],
    deps = [
        ":core_mini_axi_simulator",
        "//tests/verilator_sim:elf",
    ],
)
