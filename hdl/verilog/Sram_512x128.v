// Copyright 2024 Google LLC
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

module Sram_512x128(
  input          clock,
  input          enable,
  input          write,
  input  [8:0]   addr,
  input  [127:0] wdata,
  input  [15:0] wmask,
  output [127:0] rdata
);

///////////////////////////
///// SRAM Selection //////
///////////////////////////
`ifdef USE_TSMC12FFC
///////////////////////////
///// TSMC12FFC SRAM //////
///////////////////////////
    wire [127:0] nwmask;
    genvar i;
    generate
      for (i = 0; i < 16; i++) begin
        assign nwmask[8*i +: 8] = {8{~wmask[i]}};
      end
    endgenerate
    TS1N12FFCLLSBLVTD512X128M4SWBSHO u_12ffcp_sram
    (
      // Mode Control
      .BIST(1'b0),          // Built-In Self-Test (active high)
      // Normal Mode Input
      .SLP(1'b0),           // Sleep
      .DSLP(1'b0),          // Deep Sleep
      .SD(1'b0),            // Shut Down
      .CLK(clock),          // Clock
      .CEB(~enable),        // Chip Enable Bar (active low en)
      .WEB(~write),         // Write Enable Bar (active low WE)
      .A(addr),             // Address                               (input [8:0] DM)
      .D(wdata),            // Data                                  (input [127:0] DM)
      .BWEB(nwmask),        // Bit Write Enable Bar (active low BW)  (input [127:0])


      // BIST Mode Input
      .CEBM(1'b0),          // Chip Enable Bar for BIST Mode
      .WEBM(1'b0),          // Write Enable Bar for BIST Mode
      .AM(9'b0),            // Address for BIST Mode               (input [8:0])
      .DM(128'b0),          // Data Input for BIST Mode            (input [127:0] DM)
      .BWEBM({128{1'b1}}),  // Bit Write Enable Bar for BIST Mode  (input [127:0] DM)

      // Data Output
      .Q(rdata),            // Data Output                          (output [127:0])
      .PUDELAY(),           // Power-Up Delay - Connect for tuning timing in late stage design

      // Test Mode
`ifndef SIMULATION
      .RTSEL(2'b0),         // Read Test Select                (input [1:0])
      .WTSEL(2'b0)          // Write Test Select               (input [1:0])
`else
      .RTSEL(2'b1),         // Read Test Select                (input [1:0])
      .WTSEL(2'b0)          // Write Test Select               (input [1:0])
`endif
     );
`elsif USE_GF22
///////////////////////////
//////// GF22 SRAM ////////
///////////////////////////
    wire [127:0] nwmask;
    genvar i;
    generate
      for (i = 0; i < 16; i++) begin
        assign nwmask[8*i +: 8] = {8{wmask[i]}};
      end
    endgenerate

    sasdulssd8LOW1p512x128m4b1w0c0p0d0l0rm3sdrw01 u_gf22_sram (
      .Q(rdata),
      .ADR(addr),
      .D(wdata),
      .WEM(nwmask),
      .WE(write),
      .ME(enable),
      .CLK(clock),
      .TEST1(1'b0),
      .TEST_RNM(1'b0),
      .RME(1'b0),
      .RM(4'b0),
      .WA(2'b0),
      .WPULSE(3'b0),
      .LS(1'b0),
      .BC0(1'b0),
      .BC1(1'b0),
      .BC2(1'b0)
    );
`else
///////////////////////////
////// Generic SRAM ///////
///////////////////////////
  reg [127:0] mem [0:511];
  reg [8:0] raddr;

  assign rdata = mem[raddr];

`ifdef CORALNPU_STANDALONE_TCM_INIT
  // Standalone "hardware-boot" init (FPGA-friendly).
  // ITCM initialization from program.cc (compiled binary)
  integer i;
  initial begin
    for (i = 0; i < 512; i++) begin
      mem[i] = 128'h0;
    end
  mem[0] = 128'h7F818193_00010197_00010113_00018117;
  mem[1] = 128'h00000413_00000393_00000313_00000213;
  mem[2] = 128'h00000693_00000613_00000593_00000493;
  mem[3] = 128'h00000893_00000813_00000793_00000713;
  mem[4] = 128'h00000A93_00000A13_00000993_00000913;
  mem[5] = 128'h00000C93_00000C13_00000B93_00000B13;
  mem[6] = 128'h00000E93_00000E13_00000D93_00000D13;
  mem[7] = 128'h81018593_81018513_00000F93_00000F13;
  mem[8] = 128'h00947A63_1B000493_1B000413_0C0000EF;
  mem[9] = 128'hFE946AE3_00440413_000280E7_00042283;
  mem[10] = 128'h00010297_30529073_08C28293_00000297;
  mem[11] = 128'h00A2A023_00D50513_0BADD537_F5428293;
  mem[12] = 128'h03408093_00000097_00000593_00000513;
  mem[13] = 128'h00A2A023_F2C28293_00010297_000080E7;
  mem[14] = 128'hB0202573_0100006F_00100073_00050663;
  mem[15] = 128'h000107B7_0000006F_08000073_B82025F3;
  mem[16] = 128'h0007A703_12060613_00010637_10078793;
  mem[17] = 128'h00478793_04E7A023_00D70733_0207A683;
  mem[18] = 128'h00100073_00008067_00000513_FEC796E3;
  mem[19] = 128'h00000000_00000000_00000000_0000006F;
  mem[20] = 128'h00029E63_0032F293_00B562B3_02B57063;
  mem[21] = 128'h00008067_FEB56CE3_00450513_00052023;
  mem[22] = 128'h02B57C63_00100073_00008067_00B51463;
  mem[23] = 128'h02029863_0032F293_00C2E2B3_00B562B3;
  mem[24] = 128'h00062283_0262E263_40A58333_40C502B3;
  mem[25] = 128'hFEB568E3_00450513_00552023_00460613;
  mem[26] = 128'h00100073_00008067_00B51463_00008067;
  end
`else
`ifndef SYNTHESIS
`ifndef VERILATOR
  function automatic bit load_mem_from_plusarg;
    input string plusarg;
    string mem_file;
    begin
      if ($value$plusargs(plusarg, mem_file)) begin
        $display("%m: Loading memory from %s", mem_file);
        $readmemh(mem_file, mem);
        load_mem_from_plusarg = 1'b1;
      end else begin
        load_mem_from_plusarg = 1'b0;
      end
    end
  endfunction
`endif

  task randomMemoryAll;
  for (int i = 0; i < 512; i++) begin
    // $random returns a 32-bit value, so four are concatenated to fill the 128-bit register.
    mem[i] = { $random, $random, $random, $random };
  end
  endtask

  initial begin
    // Prefer deterministic initialization from a mem file when provided.
    // For the default CoralNPU configuration, this 512x128 SRAM backs the 8KB ITCM.
`ifdef VERILATOR
    randomMemoryAll;
`else
    if (!load_mem_from_plusarg("ITCM_MEM_FILE=%s")) begin
      randomMemoryAll;
    end
`endif
  end
`endif
`endif

  always @(posedge clock) begin
    for (int i = 0; i < 16; i++) begin
      if (enable & write & wmask[i]) begin
        mem[addr][i*8 +: 8] <= wdata[8*i +: 8];
      end
    end

    if (enable & ~write) begin
      raddr <= addr;
    end
  end
`endif

endmodule