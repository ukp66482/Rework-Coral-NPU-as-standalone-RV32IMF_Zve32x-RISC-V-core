# VGA Nyancat SDL2 Demo

This directory contains a Verilator-based VGA simulation with SDL2 display 
for the Nyancat animation, following the same approach as ca2025-mycpu.

## Prerequisites

1. **SDL2 development libraries:**
   ```bash
   sudo apt install libsdl2-dev
   ```

2. **Verilator:**
   ```bash
   sudo apt install verilator
   ```

3. **Bazel** (for generating Verilog from Chisel)

## Quick Start

Run the complete demo:

```bash
make demo
```

This will:
1. Generate Verilog from Chisel using bazel
2. Build Verilator simulation with SDL2 support
3. Run the nyancat animation for 100M cycles (~2-3 seconds on modern hardware)

## Manual Steps

### 1. Generate Verilog

```bash
make verilog
```

### 2. Build Simulation

```bash
make build
```

### 3. Run Demo

```bash
make run SIM_TIME=100000000
```

Or run directly:
```bash
./obj_dir/VVgaStandaloneWrapper -time 50000000
```

## Options

- `SIM_TIME=N` - Run for N simulation cycles (default: 100000000)
- `./obj_dir/VVgaStandaloneWrapper -verbose` - Print MMIO operations
- `./obj_dir/VVgaStandaloneWrapper -help` - Show help

## Files

- `vga_sim.cc` - Main simulator C++ source
- `nyancat_frames.h` - Prepacked 12-frame nyancat animation (copied from examples/)
- `VgaStandaloneWrapper.sv` - Generated Verilog toplevel
- `VGA.sv` - Generated VGA peripheral
- `TrueDualPortRAM32.v` - Dual-port RAM primitive
- `Makefile` - Build automation

## How It Works

1. **VGA Hardware**: The VgaStandaloneWrapper instantiates the VGA peripheral 
   with 640×480@72Hz timing, 64×64 framebuffer with 6× scaling, and 16-color palette.

2. **Frame Upload**: The simulator uploads all 12 nyancat frames to the VGA 
   framebuffer via MMIO (registers at 0x10-0x14).

3. **Animation**: The simulator cycles through frames by updating the CTRL 
   register's frame_select bits [11:8].

4. **SDL2 Display**: VGA signals (hsync, vsync, rgb, x_pos, y_pos) are read 
   directly from the Verilator model and rendered to an SDL2 window.

## Clean Up

```bash
make clean
```

## Notes

- EGL warnings about `/dev/dri/renderD128` permission denied are harmless 
  and don't affect the SDL2 software rendering.
- Press ESC or close the window to stop the simulation early.
- The animation runs at ~12 FPS with proper frame switching.
