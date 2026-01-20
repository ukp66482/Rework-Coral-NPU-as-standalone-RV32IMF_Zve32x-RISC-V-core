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

# VGA Nyancat SDL2 Demo Makefile
# 
# This Makefile builds a Verilator simulation of VgaStandaloneWrapper
# with SDL2 visualization for the Nyancat animation.
#
# Usage:
#   make verilog   - Generate Verilog from Chisel
#   make build     - Build Verilator simulation with SDL2
#   make run       - Run the demo
#   make demo      - Complete workflow: verilog + build + run

SHELL := /bin/bash

# Project root directory
ROOT_DIR := $(shell cd ../../../.. && pwd)

# Verilog source locations
CHISEL_DIR := $(ROOT_DIR)/hdl/chisel
VERILOG_DIR := $(ROOT_DIR)/hdl/verilog

# Generated Verilog files (will be copied here)
VGA_WRAPPER_SV := VgaStandaloneWrapper.sv
VGA_SV := VGA.sv
TRUE_DUAL_PORT_RAM := TrueDualPortRAM32.v

# Nyancat frames header
NYANCAT_FRAMES := $(ROOT_DIR)/examples/nyancat-frames.h

# Build directory
BUILD_DIR := obj_dir

# Verilator settings (use system verilator)
VERILATOR := verilator
VERILATOR_FLAGS := --cc --exe --trace -Wno-WIDTHEXPAND -Wno-WIDTH -Wno-TIMESCALEMOD

# SDL2 flags
SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LDFLAGS := $(shell sdl2-config --libs)

# Default simulation time
SIM_TIME ?= 100000000

.PHONY: all clean verilog build run demo help

all: demo

help:
	@echo "VGA Nyancat SDL2 Demo"
	@echo ""
	@echo "Targets:"
	@echo "  make verilog  - Generate Verilog from Chisel (via bazel)"
	@echo "  make build    - Build Verilator simulation with SDL2"
	@echo "  make run      - Run the demo (SIM_TIME=100000000)"
	@echo "  make demo     - Complete workflow: verilog + build + run"
	@echo "  make clean    - Clean build artifacts"
	@echo ""
	@echo "Options:"
	@echo "  SIM_TIME=N    - Run for N simulation cycles (default: 100000000)"
	@echo ""
	@echo "Requirements:"
	@echo "  - Verilator installed"
	@echo "  - SDL2 development libraries (libsdl2-dev)"
	@echo "  - Bazel for Chisel -> Verilog generation"

# Generate Verilog from Chisel using bazel
verilog:
	@echo "=== Generating Verilog from Chisel ==="
	cd $(ROOT_DIR) && bazel build //hdl/chisel/src/peripherals:vga_standalone_wrapper_cc_library_emit_verilog
	cd $(ROOT_DIR) && bazel build //hdl/chisel/src/peripherals:VGA.sv
	@echo "Copying generated Verilog files..."
	cp $(ROOT_DIR)/bazel-bin/hdl/chisel/src/peripherals/VgaStandaloneWrapper.sv ./
	cp $(ROOT_DIR)/bazel-bin/hdl/chisel/src/peripherals/VGA.sv ./
	cp $(VERILOG_DIR)/TrueDualPortRAM32.v ./
	@echo "=== Verilog generation complete ==="

# Copy nyancat frames header
nyancat_frames.h: $(NYANCAT_FRAMES)
	cp $< $@

# Build Verilator simulation with SDL2
build: $(VGA_WRAPPER_SV) $(VGA_SV) $(TRUE_DUAL_PORT_RAM) nyancat_frames.h
	@echo "=== Building Verilator simulation with SDL2 ==="
	$(VERILATOR) $(VERILATOR_FLAGS) \
		--top-module VgaStandaloneWrapper \
		-CFLAGS "-DENABLE_SDL2 $(SDL2_CFLAGS)" \
		-LDFLAGS "$(SDL2_LDFLAGS)" \
		vga_sim.cc \
		$(VGA_WRAPPER_SV) $(VGA_SV) $(TRUE_DUAL_PORT_RAM)
	make -j8 -C $(BUILD_DIR) -f VVgaStandaloneWrapper.mk
	@echo "=== Build complete ==="

# Run the demo
run:
	@echo "=== Running Nyancat VGA Demo ==="
	@echo "🐱 Displaying Nyancat animation via VGA..."
	@echo "   Press ESC or close window to stop"
	@echo ""
	SDL_RENDER_DRIVER=software ./$(BUILD_DIR)/VVgaStandaloneWrapper -time $(SIM_TIME)
	@echo ""
	@echo "=== Demo complete ==="

# Complete workflow
demo: verilog build run

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(VGA_WRAPPER_SV) $(VGA_SV) $(TRUE_DUAL_PORT_RAM)
	rm -f nyancat_frames.h
	rm -f *.vcd
