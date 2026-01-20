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
import chisel3.experimental._
import chisel3.util._

/**
 * True dual-port, dual-clock RAM with 32-bit data width
 *
 * Port A: Write port (CPU clock domain)
 * Port B: Read port (Pixel clock domain)
 *
 * For synthesis: vendor-specific implementation
 * For Verilator: behavioral model with separate clocks
 *
 * Parameters:
 * - depth: Number of 32-bit words (e.g., 6144 for 12 frames of 64×64 pixels, 8 pixels per word)
 * - addrWidth: Address width in bits
 */
class TrueDualPortRAM32(depth: Int, addrWidth: Int)
    extends BlackBox(
      Map(
        "DEPTH"      -> depth,
        "ADDR_WIDTH" -> addrWidth
      )
    )
    with HasBlackBoxResource {

  val io = IO(new Bundle {
    // Port A: Write port (CPU clock domain)
    val clka  = Input(Clock())
    val wea   = Input(Bool())
    val addra = Input(UInt(addrWidth.W))
    val dina  = Input(UInt(32.W))

    // Port B: Read port (Pixel clock domain)
    val clkb  = Input(Clock())
    val addrb = Input(UInt(addrWidth.W))
    val doutb = Output(UInt(32.W))
  })

  // Add Verilog resource for behavioral model
  addResource("hdl/verilog/TrueDualPortRAM32.v")
}
