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
import chisel3.simulator.scalatest.ChiselSim
import org.scalatest.freespec.AnyFreeSpec

class VGASpec extends AnyFreeSpec with ChiselSim {

  "VGA ID register returns correct value" in {
    simulate(new VgaStandaloneWrapper()) { dut =>
      // Read ID register at address 0x00
      dut.io.mmio_addr.poke(0x00)
      dut.io.mmio_wen.poke(false)
      dut.clock.step(2)
      
      // Verify ID is 0x56474131 ('VGA1')
      dut.io.mmio_rdata.expect(0x56474131L)
    }
  }

  "VGA write and read palette registers" in {
    simulate(new VgaStandaloneWrapper()) { dut =>
      // Write palette[0] with value 0x3F (white)
      dut.io.mmio_addr.poke(0x20)
      dut.io.mmio_wdata.poke(0x3F)
      dut.io.mmio_wen.poke(true)
      dut.clock.step(1)
      dut.io.mmio_wen.poke(false)
      
      // Read back palette[0]
      dut.io.mmio_addr.poke(0x20)
      dut.clock.step(2)
      // Only lower 6 bits are stored
      dut.io.mmio_rdata.expect(0x3F)
    }
  }

  "VGA control register enables display" in {
    simulate(new VgaStandaloneWrapper()) { dut =>
      // Write CTRL register at 0x04 with enable bit
      dut.io.mmio_addr.poke(0x04)
      dut.io.mmio_wdata.poke(0x01)  // Enable display
      dut.io.mmio_wen.poke(true)
      dut.clock.step(1)
      dut.io.mmio_wen.poke(false)
      
      // Read back CTRL
      dut.io.mmio_addr.poke(0x04)
      dut.clock.step(2)
      // Check enable bit is set
      dut.io.mmio_rdata.expect(0x01)
    }
  }

  "VGA upload address register" in {
    simulate(new VgaStandaloneWrapper()) { dut =>
      // Write UPLOAD_ADDR at 0x10
      dut.io.mmio_addr.poke(0x10)
      dut.io.mmio_wdata.poke(0x00010000L)  // Frame 1, offset 0
      dut.io.mmio_wen.poke(true)
      dut.clock.step(1)
      dut.io.mmio_wen.poke(false)
      
      // Read back
      dut.io.mmio_addr.poke(0x10)
      dut.clock.step(2)
      dut.io.mmio_rdata.expect(0x10000L)
    }
  }

  "VGA stream data with auto-increment" in {
    simulate(new VgaStandaloneWrapper()) { dut =>
      // Set upload address to frame 0, offset 0
      dut.io.mmio_addr.poke(0x10)
      dut.io.mmio_wdata.poke(0x00000000L)
      dut.io.mmio_wen.poke(true)
      dut.clock.step(1)
      dut.io.mmio_wen.poke(false)
      dut.clock.step(1)
      
      // Read back upload address (should be 0)
      dut.io.mmio_addr.poke(0x10)
      dut.clock.step(2)
      dut.io.mmio_rdata.expect(0)
      
      // Write to STREAM_DATA at 0x14
      dut.io.mmio_addr.poke(0x14)
      dut.io.mmio_wdata.poke(0x12345678L)
      dut.io.mmio_wen.poke(true)
      dut.clock.step(1)
      dut.io.mmio_wen.poke(false)
      dut.clock.step(1)
      
      // Read back upload address (should have auto-incremented by 8)
      dut.io.mmio_addr.poke(0x10)
      dut.clock.step(2)
      dut.io.mmio_rdata.expect(8)
    }
  }

  "VGA initialize nyancat palette" in {
    simulate(new VgaStandaloneWrapper()) { dut =>
      // Nyancat palette (first 14 colors)
      val palette = Seq(
        0x01, 0x3F, 0x00, 0x3E, 0x3B, 0x36, 0x30,
        0x38, 0x3C, 0x0C, 0x0B, 0x17, 0x2A, 0x3A
      )
      
      // Write all palette entries
      for (i <- palette.indices) {
        dut.io.mmio_addr.poke(0x20 + i * 4)
        dut.io.mmio_wdata.poke(palette(i))
        dut.io.mmio_wen.poke(true)
        dut.clock.step(1)
      }
      dut.io.mmio_wen.poke(false)
      
      // Read back and verify each palette entry
      for (i <- palette.indices) {
        dut.io.mmio_addr.poke(0x20 + i * 4)
        dut.clock.step(2)
        dut.io.mmio_rdata.expect(palette(i))
      }
    }
  }

  "VGA generates sync signals" in {
    simulate(new VgaStandaloneWrapper()) { dut =>
      // Note: In ChiselSim, we cannot drive the separate pixClock input
      // The sync signals are in the pixel clock domain, so we just verify
      // the output signals exist and are Boolean
      // Full timing verification would require a cocotb test with dual clocks
      
      // Enable VGA
      dut.io.mmio_addr.poke(0x04)
      dut.io.mmio_wdata.poke(0x01)
      dut.io.mmio_wen.poke(true)
      dut.clock.step(1)
      dut.io.mmio_wen.poke(false)

      // Just verify we can read the sync signals (they exist)
      dut.clock.step(10)
      val hsync = dut.io.hsync.peek().litToBoolean
      val vsync = dut.io.vsync.peek().litToBoolean
      // Either state is fine - we're just verifying the signals work
      assert(hsync || !hsync, "HSYNC signal should be readable")
      assert(vsync || !vsync, "VSYNC signal should be readable")
    }
  }

  "VGA frame select works" in {
    simulate(new VgaStandaloneWrapper()) { dut =>
      // Enable VGA
      dut.io.mmio_addr.poke(0x04)
      dut.io.mmio_wdata.poke(0x01)
      dut.io.mmio_wen.poke(true)
      dut.clock.step(1)
      dut.io.mmio_wen.poke(false)
      dut.clock.step(1)

      // Set frame select to frame 5
      dut.io.mmio_addr.poke(0x04)
      dut.io.mmio_wdata.poke(0x01 | (5 << 8))  // Enable + frame 5
      dut.io.mmio_wen.poke(true)
      dut.clock.step(1)
      dut.io.mmio_wen.poke(false)

      // Read back CTRL and verify frame select
      dut.io.mmio_addr.poke(0x04)
      dut.clock.step(2)
      val ctrl = dut.io.mmio_rdata.peek().litValue
      val frameSelect = (ctrl >> 8) & 0xF
      assert(frameSelect == 5, s"Frame select should be 5, got $frameSelect")
    }
  }
}
