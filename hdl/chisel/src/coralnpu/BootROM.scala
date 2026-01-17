package coralnpu

import chisel3._
import chisel3.util._
import chisel3.util.experimental.loadMemoryFromFileInline

class BootROM(p: Parameters) extends Module {
  val io = IO(new Bundle {
    val fabric = Flipped(new FabricIO(p))
  })

  // 8KB BootROM (matches Parameters.scala)
  val sizeBytes = 8192
  val widthBits = 128 // p.axi2DataBits
  val entries = sizeBytes / (widthBits / 8) // 512 entries
  
  val mem = Mem(entries, UInt(widthBits.W))

  if (p.bootRomFile != "") {
    loadMemoryFromFileInline(mem, p.bootRomFile)
  }

  // Read Logic
  val readAddr = io.fabric.readDataAddr.bits
  // Address is byte-address, convert to index
  val index = readAddr(log2Ceil(sizeBytes)-1, log2Ceil(widthBits/8))
  
  val readData = RegNext(mem(index))
  val readValid = RegNext(io.fabric.readDataAddr.valid)

  io.fabric.readData.bits := readData
  io.fabric.readData.valid := readValid

  // Write Logic (Ignore or Error)
  io.fabric.writeResp := true.B
}
