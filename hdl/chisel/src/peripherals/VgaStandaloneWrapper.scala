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

package peripheral

import chisel3._
import _root_.circt.stage.ChiselStage

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
    val intr = Output(Bool())
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
  io.intr := vga.io.intr
}

object EmitVgaStandaloneWrapper extends App {
  ChiselStage.emitSystemVerilogFile(
    new VgaStandaloneWrapper(),
    args
  )
}
