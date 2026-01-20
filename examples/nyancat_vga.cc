// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Nyancat VGA animation demo for CoralNPU Standalone
// Uses prepacked frame data for accurate pixel display

#include <stdint.h>

// Include prepacked nyancat frames (12 frames × 512 words each)
#include "nyancat-frames.h"

// ============ VGA MMIO Register Definitions ============
// VGA peripheral base address (matches Parameters.scala default: 0x50000)
#define VGA_BASE 0x00050000U

// Register offsets
#define VGA_ID          (VGA_BASE + 0x00)  // ID register (RO: 0x56474131 = 'VGA1')
#define VGA_CTRL        (VGA_BASE + 0x04)  // Control: [0] enable, [11:8] frame_select
#define VGA_STATUS      (VGA_BASE + 0x08)  // Status: [2] vblank, [1] safe_to_swap
#define VGA_UPLOAD_ADDR (VGA_BASE + 0x10)  // Upload address: [19:16] frame, [15:0] pixel offset
#define VGA_STREAM_DATA (VGA_BASE + 0x14)  // Stream data: 8 pixels packed (4-bit each)
#define VGA_PALETTE(n)  (VGA_BASE + 0x20 + ((n) << 2))  // Palette entries 0-15

// Animation constants
#define FRAME_COUNT 12      // Number of animation frames
#define WORDS_PER_FRAME 512 // 4096 pixels / 8 pixels per word
#define PALETTE_SIZE 14     // Nyancat uses 14 colors

// ============ MMIO Access Functions ============
static inline void vga_write32(uint32_t addr, uint32_t val) {
    *(volatile uint32_t *)addr = val;
}

static inline uint32_t vga_read32(uint32_t addr) {
    return *(volatile uint32_t *)addr;
}

// ============ Nyancat Color Palette ============
// 6-bit RRGGBB format (2 bits per channel)
static const uint8_t nyancat_palette[PALETTE_SIZE] = {
    0x01,  //  0: Dark blue background
    0x3F,  //  1: White (star sparkle)
    0x00,  //  2: Black (cat outline)
    0x3E,  //  3: Light pink/beige (toast face)
    0x3B,  //  4: Pink (cat cheeks)
    0x36,  //  5: Hot pink (rainbow)
    0x30,  //  6: Red (rainbow)
    0x38,  //  7: Orange (rainbow)
    0x3C,  //  8: Yellow (rainbow)
    0x0C,  //  9: Green (rainbow)
    0x0B,  // 10: Light blue (rainbow)
    0x17,  // 11: Purple (rainbow)
    0x2A,  // 12: Gray (cat body)
    0x3A,  // 13: Peach (toast)
};

// ============ Upload Prepacked Frame ============
static void upload_frame(int frame_idx) {
    // Set upload address to frame start: [19:16] = frame, [15:0] = 0
    vga_write32(VGA_UPLOAD_ADDR, ((uint32_t)(frame_idx & 0xF) << 16) | 0);
    
    // Stream all 512 words of prepacked pixel data
    for (int i = 0; i < WORDS_PER_FRAME; i++) {
        vga_write32(VGA_STREAM_DATA, nyancat_frames[frame_idx][i]);
    }
}

// ============ Simple Delay ============
static inline void delay(uint32_t cycles) {
    for (volatile uint32_t i = 0; i < cycles; i++) {
        __asm__ volatile("nop");
    }
}

// ============ Wait for VBlank ============
static inline void wait_vblank(void) {
    // Wait for vblank bit to be set
    while (!(vga_read32(VGA_STATUS) & 0x04));
    // Wait for vblank to end
    while (vga_read32(VGA_STATUS) & 0x04);
}

// ============ Main Entry Point ============
int main() {
    // Step 1: Verify VGA peripheral presence
    uint32_t id = vga_read32(VGA_ID);
    if (id != 0x56474131) {  // 'VGA1' in ASCII
        // VGA peripheral not found, return error
        return 1;
    }
    
    // Step 2: Initialize color palette
    for (int i = 0; i < PALETTE_SIZE; i++) {
        vga_write32(VGA_PALETTE(i), nyancat_palette[i] & 0x3F);
    }
    // Fill remaining palette slots with black
    for (int i = PALETTE_SIZE; i < 16; i++) {
        vga_write32(VGA_PALETTE(i), 0x00);
    }
    
    // Step 3: Enable VGA display
    vga_write32(VGA_CTRL, 0x01);  // Enable display, frame 0
    
    // Step 4: Upload all animation frames
    for (int frame = 0; frame < FRAME_COUNT; frame++) {
        upload_frame(frame);
        // Show frame as we upload it
        vga_write32(VGA_CTRL, (frame << 8) | 0x01);
    }
    
    // Step 5: Animation loop - cycle through frames infinitely
    for (uint32_t frame = 0; ; ) {
        // Select current frame and keep display enabled
        // CTRL register: [11:8] = frame_select, [0] = enable
        vga_write32(VGA_CTRL, (frame << 8) | 0x01);
        
        // Frame timing delay (~10 FPS animation)
        delay(100000);
        
        // Advance to next frame, wrap at end
        frame = (frame + 1) % FRAME_COUNT;
    }
    
    // Never reached
    return 0;
}
