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

#include "hw_sim/vga_display.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

VgaDisplay::VgaDisplay()
    : framebuffer_(NUM_FRAMES * WORDS_PER_FRAME, 0) {
  // Initialize palette with default Nyancat colors
  for (int i = 0; i < 16; ++i) {
    palette_[i] = DEFAULT_PALETTE[i];
  }

#ifdef ENABLE_SDL2
  screen_buffer_.resize(H_RES * V_RES * 4, 0);  // ARGB8888
  InitSDL();
#endif
}

VgaDisplay::~VgaDisplay() {
#ifdef ENABLE_SDL2
  CleanupSDL();
#endif
}

#ifdef ENABLE_SDL2
void VgaDisplay::InitSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
  }

  window_ = SDL_CreateWindow(
      "Nyancat VGA - CoralNPU",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      H_RES, V_RES,
      SDL_WINDOW_SHOWN);

  if (!window_) {
    SDL_Quit();
    throw std::runtime_error(std::string("SDL_CreateWindow failed: ") +
                             SDL_GetError());
  }

  std::cout << "[SDL2] Window opened: 640x480 'Nyancat VGA - CoralNPU'"
            << std::endl;
  std::cout << "[SDL2] Press ESC or close window to stop simulation"
            << std::endl;

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer_) {
    SDL_DestroyWindow(window_);
    SDL_Quit();
    throw std::runtime_error(std::string("SDL_CreateRenderer failed: ") +
                             SDL_GetError());
  }

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);

  texture_ = SDL_CreateTexture(
      renderer_, SDL_PIXELFORMAT_ARGB8888,
      SDL_TEXTUREACCESS_STREAMING, H_RES, V_RES);

  if (!texture_) {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
    throw std::runtime_error(std::string("SDL_CreateTexture failed: ") +
                             SDL_GetError());
  }
}

void VgaDisplay::CleanupSDL() {
  if (texture_) SDL_DestroyTexture(texture_);
  if (renderer_) SDL_DestroyRenderer(renderer_);
  if (window_) SDL_DestroyWindow(window_);
  SDL_Quit();
}

void VgaDisplay::HandleEvents() {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      should_quit_ = true;
    }
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
      should_quit_ = true;
    }
  }
}
#else
void VgaDisplay::InitSDL() {}
void VgaDisplay::CleanupSDL() {}
void VgaDisplay::HandleEvents() {}
#endif

uint32_t VgaDisplay::PaletteToARGB(uint32_t rrggbb) const {
  // Convert 6-bit RRGGBB to 32-bit ARGB8888
  // Each 2-bit channel maps to 8-bit: 0→0, 1→85, 2→170, 3→255
  auto expand2to8 = [](uint8_t val) -> uint8_t {
    return val * 85;
  };

  uint8_t r = expand2to8((rrggbb >> 4) & 0x3);
  uint8_t g = expand2to8((rrggbb >> 2) & 0x3);
  uint8_t b = expand2to8((rrggbb >> 0) & 0x3);

  return 0xFF000000 | (r << 16) | (g << 8) | b;
}

uint32_t VgaDisplay::Read(uint32_t offset) const {
  switch (offset) {
    case REG_ID:
      return VGA_ID;

    case REG_CTRL:
      return (enabled_ ? 1 : 0) | ((current_frame_ & 0xF) << 8);

    case REG_STATUS:
      // Bit 0: vblank (always return 1 for simplicity)
      return 1;

    default:
      if (offset >= REG_PALETTE_BASE && offset < REG_PALETTE_BASE + 64) {
        int idx = (offset - REG_PALETTE_BASE) / 4;
        if (idx < 16) return palette_[idx];
      }
      return 0;
  }
}

void VgaDisplay::Write(uint32_t offset, uint32_t value) {
  switch (offset) {
    case REG_CTRL:
      enabled_ = (value & 1) != 0;
      current_frame_ = (value >> 8) & 0xF;
      if (current_frame_ >= NUM_FRAMES) current_frame_ = 0;
      break;

    case REG_UPLOAD_ADDR:
      upload_frame_ = (value >> 16) & 0xF;
      upload_idx_ = value & 0x1FFF;  // 13-bit word index
      if (upload_frame_ >= NUM_FRAMES) upload_frame_ = 0;
      break;

    case REG_STREAM_DATA: {
      // Write 8 packed pixels to framebuffer
      if (upload_idx_ < WORDS_PER_FRAME) {
        uint32_t base = upload_frame_ * WORDS_PER_FRAME;
        framebuffer_[base + upload_idx_] = value;
        upload_idx_++;
      }
      break;
    }

    default:
      if (offset >= REG_PALETTE_BASE && offset < REG_PALETTE_BASE + 64) {
        int idx = (offset - REG_PALETTE_BASE) / 4;
        if (idx < 16) palette_[idx] = value & 0x3F;  // 6-bit color
      }
      break;
  }
}

void VgaDisplay::Render() {
#ifdef ENABLE_SDL2
  HandleEvents();

  if (!enabled_) {
    // Display black screen when disabled
    std::fill(screen_buffer_.begin(), screen_buffer_.end(), 0);
    SDL_UpdateTexture(texture_, nullptr, screen_buffer_.data(), H_RES * 4);
    SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
    SDL_RenderPresent(renderer_);
    return;
  }

  // Clear to dark blue (Nyancat sky)
  uint32_t bg_color = PaletteToARGB(palette_[9]);  // Light blue sky
  uint32_t* pixels = reinterpret_cast<uint32_t*>(screen_buffer_.data());
  for (int i = 0; i < H_RES * V_RES; ++i) {
    pixels[i] = bg_color;
  }

  // Read current frame data and render with 6× scaling
  uint32_t frame_base = current_frame_ * WORDS_PER_FRAME;

  for (int y = 0; y < FRAME_HEIGHT; ++y) {
    for (int x = 0; x < FRAME_WIDTH; ++x) {
      // Calculate which word and nibble this pixel is in
      int pixel_idx = y * FRAME_WIDTH + x;
      int word_idx = pixel_idx / 8;
      int nibble_idx = pixel_idx % 8;

      // Extract 4-bit palette index (8 nibbles per word, LSB first)
      uint32_t word = framebuffer_[frame_base + word_idx];
      uint8_t palette_idx = (word >> (nibble_idx * 4)) & 0xF;

      // Get color from palette
      uint32_t color = PaletteToARGB(palette_[palette_idx]);

      // Draw 6×6 scaled pixel
      int screen_x = LEFT_MARGIN + x * SCALE;
      int screen_y = TOP_MARGIN + y * SCALE;

      for (int dy = 0; dy < SCALE; ++dy) {
        for (int dx = 0; dx < SCALE; ++dx) {
          int px = screen_x + dx;
          int py = screen_y + dy;
          if (px >= 0 && px < H_RES && py >= 0 && py < V_RES) {
            pixels[py * H_RES + px] = color;
          }
        }
      }
    }
  }

  // Update SDL display
  SDL_UpdateTexture(texture_, nullptr, screen_buffer_.data(), H_RES * 4);
  SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
  SDL_RenderPresent(renderer_);
#endif
}

// Define static constexpr member
constexpr uint32_t VgaDisplay::DEFAULT_PALETTE[16];
