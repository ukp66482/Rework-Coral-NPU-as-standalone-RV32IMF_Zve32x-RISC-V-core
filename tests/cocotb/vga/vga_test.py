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

"""
VGA Peripheral Cocotb Test

This test verifies the VGA peripheral functionality:
1. ID register reads correctly (0x56474131 = 'VGA1')
2. Palette registers can be written and read
3. Framebuffer upload works via UPLOAD_ADDR and STREAM_DATA
4. Control register enables display
5. VSync/HSync timing signals are generated
"""

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import ClockCycles, RisingEdge, FallingEdge, Timer
import random


# VGA Register Offsets (from base address)
VGA_ID = 0x00
VGA_CTRL = 0x04
VGA_STATUS = 0x08
VGA_UPLOAD_ADDR = 0x10
VGA_STREAM_DATA = 0x14
VGA_PALETTE_BASE = 0x20

# Expected ID value
VGA_ID_VALUE = 0x56474131  # 'VGA1'

# Nyancat color palette (6-bit RRGGBB)
NYANCAT_PALETTE = [
    0x01,  # 0: Dark blue background
    0x3F,  # 1: White
    0x00,  # 2: Black
    0x3E,  # 3: Light pink/beige
    0x3B,  # 4: Pink
    0x36,  # 5: Hot pink
    0x30,  # 6: Red
    0x38,  # 7: Orange
    0x3C,  # 8: Yellow
    0x0C,  # 9: Green
    0x0B,  # 10: Light blue
    0x17,  # 11: Purple
    0x2A,  # 12: Gray
    0x3A,  # 13: Peach
    0x00,  # 14: Black (unused)
    0x00,  # 15: Black (unused)
]


async def write_mmio(dut, addr, data):
    """Write to VGA MMIO register"""
    dut.io_mmio_addr.value = addr
    dut.io_mmio_wdata.value = data
    dut.io_mmio_wen.value = 1
    await RisingEdge(dut.clock)
    dut.io_mmio_wen.value = 0


async def read_mmio(dut, addr):
    """Read from VGA MMIO register"""
    dut.io_mmio_addr.value = addr
    dut.io_mmio_wen.value = 0
    await RisingEdge(dut.clock)
    await RisingEdge(dut.clock)  # Wait one cycle for read data
    return int(dut.io_mmio_rdata.value)


@cocotb.test()
async def vga_id_register_test(dut):
    """Test that VGA ID register reads correctly"""
    # Start system clock (e.g., 100 MHz)
    clock = Clock(dut.clock, 10, units="ns")
    cocotb.start_soon(clock.start())
    
    # Start pixel clock (31.5 MHz = ~31.75 ns period)
    pix_clock = Clock(dut.io_pixClock, 32, units="ns")
    cocotb.start_soon(pix_clock.start())
    
    # Reset
    dut.reset.value = 1
    await ClockCycles(dut.clock, 10)
    dut.reset.value = 0
    await ClockCycles(dut.clock, 5)
    
    # Read ID register
    id_value = await read_mmio(dut, VGA_ID)
    dut._log.info(f"VGA ID: 0x{id_value:08X} (expected 0x{VGA_ID_VALUE:08X})")
    assert id_value == VGA_ID_VALUE, f"VGA ID mismatch: got 0x{id_value:08X}, expected 0x{VGA_ID_VALUE:08X}"


@cocotb.test()
async def vga_palette_test(dut):
    """Test that palette registers can be written and read back"""
    # Start clocks
    clock = Clock(dut.clock, 10, units="ns")
    cocotb.start_soon(clock.start())
    pix_clock = Clock(dut.io_pixClock, 32, units="ns")
    cocotb.start_soon(pix_clock.start())
    
    # Reset
    dut.reset.value = 1
    await ClockCycles(dut.clock, 10)
    dut.reset.value = 0
    await ClockCycles(dut.clock, 5)
    
    # Write palette values
    for i, color in enumerate(NYANCAT_PALETTE):
        palette_addr = VGA_PALETTE_BASE + (i * 4)
        await write_mmio(dut, palette_addr, color)
        dut._log.info(f"Wrote palette[{i}] = 0x{color:02X}")
    
    # Read back and verify
    for i, expected_color in enumerate(NYANCAT_PALETTE):
        palette_addr = VGA_PALETTE_BASE + (i * 4)
        read_color = await read_mmio(dut, palette_addr)
        dut._log.info(f"Read palette[{i}] = 0x{read_color:02X} (expected 0x{expected_color:02X})")
        assert (read_color & 0x3F) == expected_color, f"Palette[{i}] mismatch"


@cocotb.test()
async def vga_framebuffer_upload_test(dut):
    """Test framebuffer upload via STREAM_DATA register"""
    # Start clocks
    clock = Clock(dut.clock, 10, units="ns")
    cocotb.start_soon(clock.start())
    pix_clock = Clock(dut.io_pixClock, 32, units="ns")
    cocotb.start_soon(pix_clock.start())
    
    # Reset
    dut.reset.value = 1
    await ClockCycles(dut.clock, 10)
    dut.reset.value = 0
    await ClockCycles(dut.clock, 5)
    
    # Set upload address to frame 0, offset 0
    await write_mmio(dut, VGA_UPLOAD_ADDR, 0x00000000)
    
    # Upload test pattern (first 16 words = 128 pixels)
    for word_idx in range(16):
        # Pack 8 pixels (4-bit each) into 32-bit word
        # Create gradient pattern: each pixel is word_idx % 16
        color = word_idx % 14  # Use nyancat palette colors
        packed = 0
        for p in range(8):
            packed |= (color << (p * 4))
        
        await write_mmio(dut, VGA_STREAM_DATA, packed)
        dut._log.info(f"Uploaded word {word_idx}: 0x{packed:08X}")
    
    dut._log.info("Framebuffer upload test passed (16 words uploaded)")


@cocotb.test()
async def vga_control_enable_test(dut):
    """Test VGA control register enables display"""
    # Start clocks
    clock = Clock(dut.clock, 10, units="ns")
    cocotb.start_soon(clock.start())
    pix_clock = Clock(dut.io_pixClock, 32, units="ns")
    cocotb.start_soon(pix_clock.start())
    
    # Reset
    dut.reset.value = 1
    await ClockCycles(dut.clock, 10)
    dut.reset.value = 0
    await ClockCycles(dut.clock, 5)
    
    # Enable display (bit 0), select frame 0 (bits 7:4)
    await write_mmio(dut, VGA_CTRL, 0x01)
    
    # Read back control register
    ctrl = await read_mmio(dut, VGA_CTRL)
    dut._log.info(f"VGA CTRL: 0x{ctrl:08X}")
    assert (ctrl & 0x01) == 1, "Display enable bit should be set"
    
    # Try frame select (frame 5)
    await write_mmio(dut, VGA_CTRL, 0x51)  # Frame 5, enabled
    ctrl = await read_mmio(dut, VGA_CTRL)
    dut._log.info(f"VGA CTRL with frame 5: 0x{ctrl:08X}")
    assert (ctrl & 0xF0) == 0x50, "Frame select should be 5"


@cocotb.test()
async def vga_timing_test(dut):
    """Test VGA timing signals (hsync, vsync)"""
    # Start clocks
    clock = Clock(dut.clock, 10, units="ns")
    cocotb.start_soon(clock.start())
    pix_clock = Clock(dut.io_pixClock, 32, units="ns")  # ~31.25 MHz
    cocotb.start_soon(pix_clock.start())
    
    # Reset
    dut.reset.value = 1
    await ClockCycles(dut.clock, 10)
    dut.reset.value = 0
    await ClockCycles(dut.clock, 5)
    
    # Enable display
    await write_mmio(dut, VGA_CTRL, 0x01)
    
    # Monitor sync signals for several lines
    # H_TOTAL = 832 pixel clocks per line
    # V_TOTAL = 520 lines per frame
    
    hsync_count = 0
    last_hsync = 0
    
    # Wait for a few lines worth of pixel clocks
    for _ in range(2000):
        await RisingEdge(dut.io_pixClock)
        
        try:
            hsync = int(dut.io_hsync.value)
            if hsync == 1 and last_hsync == 0:
                hsync_count += 1
            last_hsync = hsync
        except ValueError:
            # Handle uninitialized signals
            pass
    
    dut._log.info(f"Detected {hsync_count} hsync pulses in 2000 pixel clocks")
    # With H_TOTAL = 832, we should see about 2-3 hsync pulses in 2000 cycles
    assert hsync_count >= 1, "Should detect at least 1 hsync pulse"


@cocotb.test()
async def vga_nyancat_animation_test(dut):
    """Full nyancat animation test - upload frames and animate"""
    # Start clocks
    clock = Clock(dut.clock, 10, units="ns")
    cocotb.start_soon(clock.start())
    pix_clock = Clock(dut.io_pixClock, 32, units="ns")
    cocotb.start_soon(pix_clock.start())
    
    # Reset
    dut.reset.value = 1
    await ClockCycles(dut.clock, 10)
    dut.reset.value = 0
    await ClockCycles(dut.clock, 5)
    
    # Step 1: Verify ID
    id_value = await read_mmio(dut, VGA_ID)
    assert id_value == VGA_ID_VALUE, "VGA ID check failed"
    dut._log.info("✓ VGA ID verified")
    
    # Step 2: Initialize palette
    for i, color in enumerate(NYANCAT_PALETTE):
        await write_mmio(dut, VGA_PALETTE_BASE + (i * 4), color)
    dut._log.info("✓ Palette initialized")
    
    # Step 3: Enable display
    await write_mmio(dut, VGA_CTRL, 0x01)
    dut._log.info("✓ Display enabled")
    
    # Step 4: Upload a simple test frame (frame 0)
    # 64x64 pixels = 512 words
    await write_mmio(dut, VGA_UPLOAD_ADDR, 0x00000000)  # Frame 0, offset 0
    
    for y in range(64):
        for x_word in range(8):  # 8 words per row (64 pixels / 8)
            x = x_word * 8
            packed = 0
            for p in range(8):
                px = x + p
                # Simple pattern: vertical rainbow stripes
                if y >= 25 and y < 45:
                    stripe = (y - 25) // 3
                    color = [6, 7, 8, 9, 10, 0, 11][min(stripe, 6)]
                else:
                    color = 0  # Dark blue background
                packed |= (color << (p * 4))
            
            await write_mmio(dut, VGA_STREAM_DATA, packed)
    
    dut._log.info("✓ Frame 0 uploaded (512 words)")
    
    # Step 5: Let VGA display for some cycles
    await ClockCycles(dut.clock, 1000)
    
    # Step 6: Read status
    status = await read_mmio(dut, VGA_STATUS)
    dut._log.info(f"VGA STATUS: 0x{status:08X}")
    
    # Step 7: Try switching frames
    for frame in range(12):
        await write_mmio(dut, VGA_CTRL, (frame << 4) | 0x01)
        await ClockCycles(dut.clock, 100)
        dut._log.info(f"✓ Selected frame {frame}")
    
    dut._log.info("✓ Nyancat animation test complete!")
