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

/**
 * VGA Nyancat Simulator using Verilator
 * 
 * This program simulates the VgaStandaloneWrapper hardware and displays
 * the VGA output using SDL2. It mimics the ca2025-mycpu VGA demo approach.
 */

#include <verilated.h>
#include <verilated_vcd_c.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "VVgaStandaloneWrapper.h"

#ifdef ENABLE_SDL2
#include <SDL.h>
#endif

// Prepacked Nyancat frames - 12 frames × 512 words each
// Each word contains 8 4-bit palette indices (for 64×64 framebuffer)
#include "nyancat_frames.h"

// VGA Register Offsets
namespace VgaRegs {
constexpr uint32_t ID = 0x00;
constexpr uint32_t CTRL = 0x04;
constexpr uint32_t STATUS = 0x08;
constexpr uint32_t UPLOAD_ADDR = 0x10;
constexpr uint32_t STREAM_DATA = 0x14;
constexpr uint32_t PALETTE_BASE = 0x20;
}

// Nyancat 16-color palette (6-bit RRGGBB format)
constexpr uint32_t NYANCAT_PALETTE[16] = {
    0x01,  // 0: Dark blue background
    0x3F,  // 1: White
    0x00,  // 2: Black
    0x3E,  // 3: Light pink/beige
    0x3B,  // 4: Pink
    0x36,  // 5: Hot pink
    0x30,  // 6: Red
    0x38,  // 7: Orange
    0x3C,  // 8: Yellow
    0x0C,  // 9: Green
    0x0B,  // 10: Light blue
    0x17,  // 11: Purple
    0x2A,  // 12: Gray
    0x3A,  // 13: Peach
    0x00,  // 14: Black (unused)
    0x00,  // 15: Black (unused)
};

#ifdef ENABLE_SDL2
class VGADisplay {
    static constexpr int H_RES = 640;
    static constexpr int V_RES = 480;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
    std::vector<uint8_t> framebuffer;
    bool prev_vsync = true;
    bool should_quit = false;

    // Convert 2-bit VGA channel to 8-bit
    static constexpr uint8_t vga2bit_to_8bit(uint8_t val) { return val * 85; }

public:
    VGADisplay() : framebuffer(H_RES * V_RES * 4, 0) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
        }

        window = SDL_CreateWindow(
            "Nyancat VGA - CoralNPU",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            H_RES, V_RES, SDL_WINDOW_SHOWN);
        if (!window) {
            SDL_Quit();
            throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
        }
        
        std::cout << "[SDL2] Window opened: 640x480 'Nyancat VGA - CoralNPU'" << std::endl;
        std::cout << "[SDL2] Press ESC or close window to stop simulation" << std::endl;

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            throw std::runtime_error(std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        texture = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING, H_RES, V_RES);
        if (!texture) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            throw std::runtime_error(std::string("SDL_CreateTexture failed: ") + SDL_GetError());
        }
    }

    ~VGADisplay() {
        if (texture) SDL_DestroyTexture(texture);
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // Update pixel using hardware-provided positions
    void update_pixel(uint8_t rrggbb, uint8_t activevideo, uint16_t x_pos, uint16_t y_pos) {
        if (activevideo && x_pos < H_RES && y_pos < V_RES) {
            int idx = (y_pos * H_RES + x_pos) * 4;
            framebuffer[idx] = vga2bit_to_8bit(rrggbb & 0b11);             // B
            framebuffer[idx + 1] = vga2bit_to_8bit((rrggbb >> 2) & 0b11);  // G
            framebuffer[idx + 2] = vga2bit_to_8bit((rrggbb >> 4) & 0b11);  // R
            framebuffer[idx + 3] = 255;                                    // A
        }
    }

    // Detect vsync falling edge to trigger frame rendering
    void check_vsync(bool vsync) {
        if (!vsync && prev_vsync) render();
        prev_vsync = vsync;
    }

    void render() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) should_quit = true;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) should_quit = true;
        }
        SDL_UpdateTexture(texture, nullptr, framebuffer.data(), H_RES * 4);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    bool quit_requested() const { return should_quit; }
};
#endif

class VGASimulator {
    std::unique_ptr<VVgaStandaloneWrapper> top_;
    uint64_t sim_time_ = 0;
    bool verbose_ = false;

public:
    VGASimulator() : top_(std::make_unique<VVgaStandaloneWrapper>()) {
        reset();
    }

    void setVerbose(bool v) { verbose_ = v; }

    void reset() {
        top_->reset = 1;
        top_->clock = 0;
        top_->io_pixClock = 0;
        top_->io_mmio_wen = 0;
        top_->io_mmio_addr = 0;
        top_->io_mmio_wdata = 0;
        
        for (int i = 0; i < 10; ++i) {
            tick();
        }
        top_->reset = 0;
    }

    void tick() {
        top_->clock = !top_->clock;
        top_->io_pixClock = top_->clock;
        top_->eval();
        sim_time_++;
    }

    void writeMMIO(uint32_t addr, uint32_t data) {
        top_->io_mmio_addr = addr;
        top_->io_mmio_wdata = data;
        top_->io_mmio_wen = 1;
        tick();
        tick();
        top_->io_mmio_wen = 0;
        if (verbose_) {
            std::cout << "[MMIO] Write [0x" << std::hex << addr << "] = 0x" << data << std::dec << std::endl;
        }
    }

    uint32_t readMMIO(uint32_t addr) {
        top_->io_mmio_addr = addr;
        top_->io_mmio_wen = 0;
        tick();
        tick();
        return top_->io_mmio_rdata;
    }

    void initPalette() {
        std::cout << "[VGA] Initializing palette (16 colors)..." << std::endl;
        for (int i = 0; i < 16; ++i) {
            writeMMIO(VgaRegs::PALETTE_BASE + i * 4, NYANCAT_PALETTE[i]);
        }
    }

    void uploadFrame(int frame_idx) {
        if (frame_idx < 0 || frame_idx >= 12) return;
        
        // Set upload address: frame in bits [19:16], nibble offset = 0
        writeMMIO(VgaRegs::UPLOAD_ADDR, (frame_idx << 16) | 0);
        
        // Upload 512 words (64×64 / 8 pixels per word = 512)
        for (int i = 0; i < 512; ++i) {
            writeMMIO(VgaRegs::STREAM_DATA, nyancat_frames[frame_idx][i]);
        }
    }

    void uploadAllFrames() {
        std::cout << "[VGA] Uploading all 12 nyancat frames..." << std::endl;
        for (int f = 0; f < 12; ++f) {
            uploadFrame(f);
            std::cout << "  Frame " << f << " uploaded" << std::endl;
        }
        std::cout << "[VGA] All frames uploaded" << std::endl;
    }

    void selectFrame(int frame) {
        // CTRL register: [7:4] = frame_select, [0] = enable
        writeMMIO(VgaRegs::CTRL, ((frame & 0xF) << 4) | 1);
    }

    // Accessors for VGA signals (used by SDL2 display)
    bool vsync() const { return top_->io_vsync; }
    bool hsync() const { return top_->io_hsync; }
    bool activevideo() const { return top_->io_activevideo; }
    uint8_t rgb() const { return top_->io_rgb; }
    uint16_t x_pos() const { return top_->io_x_pos; }
    uint16_t y_pos() const { return top_->io_y_pos; }
    
    uint32_t idRegister() { return readMMIO(VgaRegs::ID); }
};

void printUsage(const char* prog) {
    std::cout << "Usage: " << prog << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -time N     Run for N cycles (default: 50000000)" << std::endl;
    std::cout << "  -verbose    Print MMIO operations" << std::endl;
    std::cout << "  -help       Show this help" << std::endl;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    uint64_t max_cycles = 50000000;  // 50M cycles default
    bool verbose = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-time" && i + 1 < argc) {
            max_cycles = std::stoull(argv[++i]);
        } else if (arg == "-verbose") {
            verbose = true;
        } else if (arg == "-help") {
            printUsage(argv[0]);
            return 0;
        }
    }

    std::cout << "=== Nyancat VGA Simulator ===" << std::endl;
    std::cout << "Running for " << max_cycles << " cycles" << std::endl;

    try {
        VGASimulator sim;
        sim.setVerbose(verbose);

        // Verify VGA ID
        uint32_t id = sim.idRegister();
        std::cout << "[VGA] ID = 0x" << std::hex << id << std::dec;
        if (id == 0x56474131) {
            std::cout << " ✓ (VGA1)" << std::endl;
        } else {
            std::cout << " ✗ (expected 0x56474131)" << std::endl;
            return 1;
        }

        // Initialize and upload
        sim.initPalette();
        sim.uploadAllFrames();
        sim.selectFrame(0);

#ifdef ENABLE_SDL2
        VGADisplay display;
        
        int current_frame = 0;
        int vsync_count = 0;
        int frames_per_animation = 6;  // Switch animation frame every 6 vsync (~12 FPS at 72Hz)
        bool prev_vsync = true;

        std::cout << "[VGA] Starting animation..." << std::endl;
        std::cout << "[VGA] Animation will cycle through 12 frames" << std::endl;
        
        for (uint64_t cycle = 0; cycle < max_cycles; ++cycle) {
            sim.tick();
            
            // Update SDL display from VGA signals
            display.update_pixel(sim.rgb(), sim.activevideo(), sim.x_pos(), sim.y_pos());
            
            // Detect vsync falling edge (frame complete)
            bool vsync = sim.vsync();
            if (!vsync && prev_vsync) {
                // Frame complete - render to SDL
                display.render();
                vsync_count++;
                
                // Switch animation frame periodically
                if (vsync_count % frames_per_animation == 0) {
                    current_frame = (current_frame + 1) % 12;
                    sim.selectFrame(current_frame);
                }
            }
            prev_vsync = vsync;
            
            if (display.quit_requested()) {
                std::cout << "[VGA] User requested quit at cycle " << cycle << std::endl;
                break;
            }
        }
        
        std::cout << "[VGA] Animation complete!" << std::endl;
#else
        std::cout << "[VGA] SDL2 not enabled. Running " << max_cycles << " cycles without display..." << std::endl;
        for (uint64_t cycle = 0; cycle < max_cycles; ++cycle) {
            sim.tick();
        }
        std::cout << "[VGA] Simulation complete." << std::endl;
#endif

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
