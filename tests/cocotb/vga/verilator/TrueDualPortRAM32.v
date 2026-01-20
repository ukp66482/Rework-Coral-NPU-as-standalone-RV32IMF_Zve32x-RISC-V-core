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

// True dual-port, dual-clock RAM behavioral model for VGA framebuffer
// Port A: Write port (CPU clock domain)
// Port B: Read port (Pixel clock domain)

module TrueDualPortRAM32 #(
    parameter DEPTH = 6144,       // Number of 32-bit words
    parameter ADDR_WIDTH = 13     // Address width in bits
) (
    // Port A: Write port (CPU clock domain)
    input wire clka,
    input wire wea,
    input wire [ADDR_WIDTH-1:0] addra,
    input wire [31:0] dina,

    // Port B: Read port (Pixel clock domain)
    input wire clkb,
    input wire [ADDR_WIDTH-1:0] addrb,
    output reg [31:0] doutb
);

    // RAM storage
    reg [31:0] mem [0:DEPTH-1];

    // Port A: Write port
    always @(posedge clka) begin
        if (wea) begin
            mem[addra] <= dina;
        end
    end

    // Port B: Read port
    always @(posedge clkb) begin
        doutb <= mem[addrb];
    end

    // Initialize memory to zero
    integer i;
    initial begin
        for (i = 0; i < DEPTH; i = i + 1) begin
            mem[i] = 32'h0;
        end
    end

endmodule
