// Copyright 2026 Google LLC
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

package coralnpu

import chisel3._
import chisel3.util._
import peripheral.VGA

/**
 * CoreMiniStandaloneVgaAxi: CoralNPU Standalone Core with VGA peripheral
 * 
 * This module wraps the standalone core and adds a VGA peripheral
 * for graphics output. The VGA peripheral is memory-mapped at 0x50000.
 * 
 * Memory Map:
 *   0x00000000 - 0x00001FFF: ITCM (8KB)
 *   0x00010000 - 0x00017FFF: DTCM (32KB)
 *   0x00030000 - 0x00030FFF: CSR (4KB)
 *   0x00040000 - 0x00041FFF: BootROM (8KB)
 *   0x00050000 - 0x00050FFF: VGA Control Registers (4KB)
 * 
 * VGA Registers (offset from 0x50000):
 *   0x00: ID          - Read 0x56474131 ('VGA1')
 *   0x04: CTRL        - Display control
 *   0x08: STATUS      - VBlank status
 *   0x10: UPLOAD_ADDR - Framebuffer address
 *   0x14: STREAM_DATA - Pixel data upload
 *   0x20-0x5C: PALETTE[0-15] - Color palette
 */
class CoreStandaloneVgaIO(p: Parameters) extends Bundle {
  // Core signals
  val aclk = Input(Clock())
  val aresetn = Input(AsyncReset())
  val halted = Output(Bool())
  val fault = Output(Bool())
  val wfi = Output(Bool())
  val irq = Input(Bool())
  val te = Input(Bool())
  
  // VGA signals
  val vga_pixclk = Input(Clock())
  val vga_hsync = Output(Bool())
  val vga_vsync = Output(Bool())
  val vga_rgb = Output(UInt(6.W))
  val vga_activevideo = Output(Bool())
  val vga_x_pos = Output(UInt(10.W))
  val vga_y_pos = Output(UInt(10.W))
}

/**
 * Simple VGA wrapper module for testing
 * This creates a standalone VGA peripheral that can be tested independently
 */
class VgaStandaloneWrapper extends Module {
  val io = IO(new Bundle {
    // MMIO interface
    val mmio_addr = Input(UInt(32.W))
    val mmio_wdata = Input(UInt(32.W))
    val mmio_wen = Input(Bool())
    val mmio_rdata = Output(UInt(32.W))
    
    // VGA output
    val pixClock = Input(Clock())
    val hsync = Output(Bool())
    val vsync = Output(Bool())
    val rgb = Output(UInt(6.W))
    val activevideo = Output(Bool())
    val x_pos = Output(UInt(10.W))
    val y_pos = Output(UInt(10.W))
  })
  
  val vga = Module(new VGA)
  
  // Connect MMIO
  vga.io.mmio.address := io.mmio_addr
  vga.io.mmio.write_data := io.mmio_wdata
  vga.io.mmio.write_enable := io.mmio_wen
  io.mmio_rdata := vga.io.mmio.read_data
  
  // Connect VGA output
  vga.io.pixClock := io.pixClock
  io.hsync := vga.io.hsync
  io.vsync := vga.io.vsync
  io.rgb := vga.io.rrggbb
  io.activevideo := vga.io.activevideo
  io.x_pos := vga.io.x_pos
  io.y_pos := vga.io.y_pos
}

object EmitVgaStandaloneWrapper extends App {
  import circt.stage.ChiselStage
  
  val systemVerilogSource = ChiselStage.emitSystemVerilog(
    new VgaStandaloneWrapper(),
    Array("--target-dir", "hdl/chisel/generated")
  )
  println(systemVerilogSource)
}
