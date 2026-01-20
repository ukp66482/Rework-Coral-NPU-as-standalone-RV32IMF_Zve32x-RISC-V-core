// Copyright 2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef HW_SIM_VGA_DISPLAY_H_
#define HW_SIM_VGA_DISPLAY_H_

#include <cstdint>
#include <vector>

#ifdef ENABLE_SDL2
#include <SDL2/SDL.h>
#endif

/**
 * VGA Display Simulator with SDL2 backend
 * Emulates the VGA peripheral defined in VGA.scala
 *
 * Memory map (relative to VGA_BASE):
 *   0x00: ID          - Read: 0x56474131 ('VGA1')
 *   0x04: CTRL        - [0]=enable, [11:8]=frame_select
 *   0x08: STATUS      - [0]=vblank
 *   0x10: UPLOAD_ADDR - [19:16]=frame, [12:0]=nibble_idx
 *   0x14: STREAM_DATA - 8 packed pixels (auto-increment)
 *   0x20-0x5C: PALETTE[0-15]
 *
 * Framebuffer: 12 frames × 64×64 pixels × 4-bit palette index
 *              8 pixels packed per 32-bit word (512 words/frame)
 */
class VgaDisplay {
 public:
  static constexpr int H_RES = 640;
  static constexpr int V_RES = 480;
  static constexpr int FRAME_WIDTH = 64;
  static constexpr int FRAME_HEIGHT = 64;
  static constexpr int SCALE = 6;
  static constexpr int DISPLAY_WIDTH = FRAME_WIDTH * SCALE;   // 384
  static constexpr int DISPLAY_HEIGHT = FRAME_HEIGHT * SCALE; // 384
  static constexpr int LEFT_MARGIN = (H_RES - DISPLAY_WIDTH) / 2;  // 128
  static constexpr int TOP_MARGIN = (V_RES - DISPLAY_HEIGHT) / 2;  // 48
  static constexpr int NUM_FRAMES = 12;
  static constexpr int WORDS_PER_FRAME = 512;  // 4096 pixels / 8 per word

  VgaDisplay();
  ~VgaDisplay();

  // MMIO interface (called by simulator on VGA memory access)
  uint32_t Read(uint32_t offset) const;
  void Write(uint32_t offset, uint32_t value);

  // Render current frame to SDL2 window
  void Render();

  // Check if user requested quit (ESC or window close)
  bool QuitRequested() const { return should_quit_; }

  // Get current state
  bool IsEnabled() const { return enabled_; }
  int GetCurrentFrame() const { return current_frame_; }

 private:
  // Register offsets
  static constexpr uint32_t REG_ID = 0x00;
  static constexpr uint32_t REG_CTRL = 0x04;
  static constexpr uint32_t REG_STATUS = 0x08;
  static constexpr uint32_t REG_UPLOAD_ADDR = 0x10;
  static constexpr uint32_t REG_STREAM_DATA = 0x14;
  static constexpr uint32_t REG_PALETTE_BASE = 0x20;

  // Peripheral ID
  static constexpr uint32_t VGA_ID = 0x56474131;  // 'VGA1'

  // Default Nyancat 16-color palette (6-bit RRGGBB)
  static constexpr uint32_t DEFAULT_PALETTE[16] = {
      0x00, // 0: Black
      0x03, // 1: Dark Blue
      0x0C, // 2: Dark Green
      0x0F, // 3: Dark Cyan
      0x30, // 4: Dark Red
      0x33, // 5: Dark Magenta
      0x3C, // 6: Brown/Orange
      0x2D, // 7: Light Gray
      0x15, // 8: Dark Gray
      0x1F, // 9: Light Blue (sky)
      0x1C, // 10: Light Green
      0x3F, // 11: Light Cyan
      0x38, // 12: Light Red (pink)
      0x3B, // 13: Light Magenta
      0x3E, // 14: Yellow
      0x3F  // 15: White
  };

  void InitSDL();
  void CleanupSDL();
  void HandleEvents();
  uint32_t PaletteToARGB(uint32_t rrggbb) const;

  // Framebuffer: 12 frames × 512 words
  std::vector<uint32_t> framebuffer_;

  // Palette: 16 colors, 6-bit RRGGBB
  uint32_t palette_[16];

  // Control state
  bool enabled_ = false;
  int current_frame_ = 0;

  // Upload state
  uint32_t upload_frame_ = 0;
  uint32_t upload_idx_ = 0;

#ifdef ENABLE_SDL2
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  SDL_Texture* texture_ = nullptr;
  std::vector<uint8_t> screen_buffer_;  // ARGB8888
#endif

  bool should_quit_ = false;
};

#endif  // HW_SIM_VGA_DISPLAY_H_
