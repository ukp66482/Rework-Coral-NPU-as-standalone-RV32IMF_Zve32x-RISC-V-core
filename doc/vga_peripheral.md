# VGA Peripheral for CoralNPU Standalone

This document describes how to use the VGA peripheral with CoralNPU Standalone core.

## Overview

The VGA peripheral adds graphics output capability to the CoralNPU core, enabling:
- 640×480 @ 72Hz VGA output
- 64×64 pixel framebuffer (6× scaled to 384×384)
- 16-color palette (6-bit RRGGBB)
- 12-frame animation support
- Double-buffered frame switching

## Memory Map

| Address Range | Region | Description |
|---------------|--------|-------------|
| 0x00000000 - 0x00001FFF | ITCM | Instruction TCM (8KB) |
| 0x00010000 - 0x00017FFF | DTCM | Data TCM (32KB) |
| 0x00030000 - 0x00030FFF | CSR | Core Status Registers (4KB) |
| 0x00040000 - 0x00041FFF | BootROM | Boot ROM (8KB) |
| 0x00050000 - 0x00050FFF | VGA | VGA Control Registers (4KB) |

## VGA Registers

| Offset | Name | Access | Description |
|--------|------|--------|-------------|
| 0x00 | ID | RO | Peripheral ID (0x56474131 = 'VGA1') |
| 0x04 | CTRL | RW | Control: [0] enable, [7:4] frame_select |
| 0x08 | STATUS | RO | Status: [0] vblank, [1] safe_to_swap |
| 0x10 | UPLOAD_ADDR | RW | Upload address: [19:16] frame, [15:0] offset |
| 0x14 | STREAM_DATA | WO | Stream 8 pixels packed in 32-bit word |
| 0x20-0x5C | PALETTE[0-15] | RW | 6-bit VGA colors (RRGGBB) |

### CTRL Register Bits
- Bit 0: Display enable (1=on, 0=off)
- Bits 7:4: Frame select (0-11)

### Pixel Format
Each 32-bit word in STREAM_DATA contains 8 pixels:
- Bits [3:0]: Pixel 0 (4-bit palette index)
- Bits [7:4]: Pixel 1
- ...
- Bits [31:28]: Pixel 7

## Usage Example (C Code)

```c
#define VGA_BASE 0x00050000U
#define VGA_ID          (VGA_BASE + 0x00)
#define VGA_CTRL        (VGA_BASE + 0x04)
#define VGA_UPLOAD_ADDR (VGA_BASE + 0x10)
#define VGA_STREAM_DATA (VGA_BASE + 0x14)
#define VGA_PALETTE(n)  (VGA_BASE + 0x20 + ((n) << 2))

// Initialize palette
for (int i = 0; i < 16; i++) {
    *(volatile uint32_t *)VGA_PALETTE(i) = palette[i] & 0x3F;
}

// Enable display
*(volatile uint32_t *)VGA_CTRL = 0x01;

// Upload frame 0
*(volatile uint32_t *)VGA_UPLOAD_ADDR = 0x00000000;
for (int word = 0; word < 512; word++) {  // 64×64 / 8 = 512 words
    uint32_t packed = pack_8_pixels(...);
    *(volatile uint32_t *)VGA_STREAM_DATA = packed;
}

// Switch to frame 5
*(volatile uint32_t *)VGA_CTRL = (5 << 4) | 0x01;
```

## Building and Testing

### Build the Nyancat example
```bash
bazel build //examples:coralnpu_v2_nyancat_vga
```

### Run VGA Cocotb tests
```bash
bazel test //tests/cocotb/vga:vga_cocotb_verilator_vga_id_register_test
bazel test //tests/cocotb/vga:vga_cocotb_verilator_vga_palette_test
bazel test //tests/cocotb/vga:vga_cocotb_verilator_vga_nyancat_animation_test
```

### Run all VGA tests
```bash
bazel test //tests/cocotb/vga:...
```

## VGA Timing (640×480 @ 72Hz)

| Parameter | Value |
|-----------|-------|
| Pixel Clock | 31.5 MHz |
| H Active | 640 pixels |
| H Front Porch | 24 pixels |
| H Sync | 40 pixels |
| H Back Porch | 128 pixels |
| H Total | 832 pixels |
| V Active | 480 lines |
| V Front Porch | 9 lines |
| V Sync | 3 lines |
| V Back Porch | 28 lines |
| V Total | 520 lines |

## Animation

The framebuffer supports 12 animation frames. Each frame is 64×64 pixels (4-bit color indices). 
To animate:

1. Upload all frames at initialization
2. Use CTRL register to switch frames
3. Wait for VBlank (STATUS bit 0) for tear-free switching

## Nyancat Demo

The `nyancat_vga.cc` example demonstrates:
1. VGA peripheral detection
2. Palette initialization with Nyancat colors
3. Procedural frame generation
4. Smooth animation loop

## Hardware Integration

The VGA module requires:
- Main clock (aclk): CPU clock domain
- Pixel clock (pixclk): 31.5 MHz for VGA timing
- 6 VGA output signals: hsync, vsync, rgb[5:0], activevideo

## Files

| File | Description |
|------|-------------|
| `hdl/chisel/src/peripherals/VGA.scala` | VGA controller module |
| `hdl/chisel/src/peripherals/TrueDualPortRAM32.scala` | Dual-clock RAM wrapper |
| `hdl/verilog/TrueDualPortRAM32.v` | Verilog RAM implementation |
| `hdl/chisel/src/coralnpu/CoreStandaloneVga.scala` | VGA standalone wrapper |
| `examples/nyancat_vga.cc` | Nyancat animation demo |
| `tests/cocotb/vga/vga_test.py` | VGA Cocotb tests |
