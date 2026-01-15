# Rework [Coral NPU](https://github.com/google-coral/coralnpu) as standalone RV32IMF_Zve32x RISC-V core
> 黃偉峰, 陳彥宇, 陳識博

## Goals
* The open-source Google [Coral NPU](https://github.com/google-coral/coralnpu) repository contains a hidden gem: a production-grade, superscalar RISC-V core implementing the RV32IMF_Zve32x ISA. This is a rare example of a high-performance, embedded vector processor available in the open hardware ecosystem. However, it is currently deeply embedded within the NPU accelerator logic, making it inaccessible for general-purpose use.
* Your mission is to decouple this high-efficiency core from its NPU surroundings and transform it into a standalone processor. The ultimate goal is to prove that this core is robust enough to serve as a superior drop-in replacement for the [MyCPU](https://github.com/sysprog21/ca2025-mycpu) core used in previous course modules, capable of running legacy student programs and driving complex peripherals like a VGA controller.

- [ ] Phase 1: Architecture Extraction and Analysis

Before you can run software, you must understand the hardware internals.
1. Pipeline Forensics
Analyze the SystemVerilog source code to map the superscalar pipeline. Identify how the core handles instruction dispatch and hazard detection. Document the interface signals specifically related to the "Zve32x" vector unit and how it shares resources with the scalar pipeline.
2. Decoupling Strategy
Locate the boundary between the CPU core and the NPU accelerator logic. You must strip away the dependency on the host command queue. The core is currently designed to wait for instructions from a driver; you must modify the fetch logic or the wrapper to allow it to boot autonomously from a local ROM/RAM at reset.

- [ ] Phase 2: Building the Standalone SoC

You will integrate the extracted core into a system-on-chip (SoC) environment that mimics the interface of the course's standard [MyCPU](https://github.com/sysprog21/ca2025-mycpu).
1. The Wrapper Module
Design a SystemVerilog wrapper that adapts the Coral core's native memory interface (likely AXI or a custom TCM interface) to the simpler bus protocol used by the course's standard memory and peripherals.
2. Memory Subsystem
Implement a Harvard architecture memory layout or a unified von Neumann memory map, depending on what the extracted core expects. Ensure there is sufficient block RAM to load standard C programs.
3. Bus and Peripheral Adaptation
The Coral core likely uses a high-bandwidth bus. You must implement a bus bridge (e.g., AXI to Simple-Bus) to connect low-speed peripherals.

- [ ] Phase 3: Rigorous Compliance Validation (RISCOF)

To prove this core is a reliable replacement for MyCPU, you must verify it adheres strictly to the RISC-V standard.
1. RISCOF Integration
Develop a Python plugin for the RISC-V Compliance Framework (RISCOF) that interfaces with your Verilator simulation of the standalone core.
2. Architecture Configuration
Configure the reference model (Spike) and the test suite to target `RV32IMF_Zve32x`. You must ensure the test suite filters out 64-bit vector element tests, as Zve32x supports only 8, 16, and 32-bit elements.
3. Signature Analysis
Run the official `riscv-arch-test` suite. Investigate any discrepancies between the Coral hardware and the Spike reference model. A successful outcome is a report showing 100% pass rates for Integer (I), Floating Point (F), and Vector (Zve32x) tests.

- [ ] Phase 4: System Verification and VGA Integration
The final test of a general-purpose CPU is its ability to handle real-world I/O and legacy software.
1. Running Legacy "MyCPU" Programs
Compile and run the C programs from previous homework assignments (e.g., sorting algorithms, matrix multiplication) on the new Coral core. Verify that the results match the outputs from the original MyCPU.
2. VGA Peripheral Integration
Connect the course's customized VGA controller module to your standalone Coral SoC. You may need to map the VGA framebuffer to a specific memory address range that the Coral core can access via its load/store unit, running Nyancat animation
3. The "Killer App" Demo
Develop a graphical demonstration that utilizes the Zve32x vector unit. For example, write a Mandelbrot set renderer or a 3D wireframe rotation demo that displays to the VGA screen. This will demonstrate the superscalar and vector performance advantages of the Coral core compared to the scalar MyCPU.

### Deliverables
1. A GitHub repository containing the standalone RTL wrapper and the modified SystemVerilog files.
2. A RISCOF pass report HTML file confirming standard compliance.
3. A video demonstration showing the standalone core booting, running a legacy program, and driving a graphical output on the VGA display.
4. A performance analysis report comparing the cycle counts of the Coral core versus the MyCPU core on the same sorting algorithm.

## Background

### RISC-V Vector and SIMD
**RISC-V vector (SIMD)** allows a single instruction to operate on multiple data elements in parallel.

In contrast to **scalar execution**, where each instruction processes one data element, **vector execution applies the same operation across multiple lanes within a vector register**, which is a wide register that stores multiple data elements simultaneously.

In **[RISC-V Vector Extension (RVV) v1.0](https://lists.riscv.org/g/tech-vector-ext/attachment/691/0/riscv-v-spec-1.0.pdf)**, Software only specifies the data size `SEW` and the number of elements to process `VL`. The hardware decides how many vector lanes are available and executes the operation accordingly.

:::info
**lane calculation:**

$$
\text{Number of lanes} = \frac{\text{Vector register width (VLEN)}}{\text{Data element width (SEW)}}
$$

The number of lanes depends on the hardware vector register width (VLEN) and the selected data element width (SEW).

For example, with a 128-bit vector register:
- SEW = 32 bits → 4 lanes
- SEW = 16 bits → 8 lanes
- SEW = 8 bits → 16 lanes
:::

### Vector Register

**Vector Register** is a wide register designed to hold multiple data elements and enable data-level parallelism in vector processors.

The vector register file consists of **32 vector registers (v0–v31)**. Among them, **v0** is used as the **mask register**, where each bit corresponds to one vector element and determines whether that element participates in the operation.

### Some CSR of RISC-V Vector
In RVV, the behavior of vector instructions is **not fixed**.
Instead, it is **dynamically controlled by a set of Control and Status Registers (CSRs)** that define how vector operations should be interpreted and executed.

#### Vector Length (`vl`)
The `vl` defines how many elements in a vector register participate in vector operations.
- Only elements with index `i < vl` are considered active.
- Elements with index `i >= vl` are treated as tail elements.
- The handling of tail elements depends on the `vtype` configuration.\

`vl` is typically set by `vsetvli` or `vsetvl` instructions

#### Vector Start Index (`vstart`)
The `vstart` CSR indicates the starting element index for vector execution.

- Elements with index < vstart are skipped.
- Execution resumes from element index vstart.

This CSR `vstart` is mainly used for exception and interrupt handling, allowing a vector instruction to resume execution after being interrupted.

#### Vector Type (`vtype`)

![image](https://hackmd.io/_uploads/B1hq32BXbl.png)

- `vill` (Vector Illegal Configuration)
    - Indicates whether the current vector configuration is illegal.
    - If `vill` is set, vector instructions should not be executed.
- `SEW` (Selected Element Width)
    - Specifies the bit-width of each vector element, such as 8, 16, 32, or 64 bits.
    - It determines how vector registers are interpreted and how many elements can fit into a vector register.
- `LMUL` (Vector Length Multiplier)
    - Determines how many vector registers are grouped together to form a single vector operand.
- `VTA` (Vector Tail Agnostic)
    - Controls how tail elements (elements with index `i >= vl`) are handled.
    - When set, the contents of tail elements are treated as `undefined`; otherwise, they `remain unchanged`.
- `VMA` (Vector Mask Agnostic)
    - Controls how masked-off elements are handled.
    - When set, masked elements can be changed freely; otherwise, they keep their original values.

#### Vector Fixed-Point Rounding Mode (`vxrm`)
The `vxrm` CSR specifies the rounding mode for fixed-point vector operations, It affects how intermediate results are rounded during execution

#### Vector Fixed-Point Saturation Flag (`vxsat`)
The `vxsat` CSR is a status register that indicates whether **saturation** occurred during fixed-point vector operations.
- If an overflow is clamped to the maximum or minimum representable value, vxsat is set.
- Software can read this CSR to detect saturation events.

:::info
The widths of vector CSRs are derived from the **maximum architectural vector length**.

For example, the vector register width is defined as `VLEN` = 128 bits. The maximum possible vector length occurs when the minimum element width (`SEW` = 8) and the maximum number of vector registers grouped together (`LMUL` = 8) are selected:

$$
VLMAX_{\text{max}} = \dfrac{VLEN \times LMUL_{\text{max}}}{SEW_{\text{min}}} = VLEN
$$

Therefore, both `vl` and `vstart` are bounded by `VLMAX_max = VLEN`.

- VSTART_WIDTH = clog2(VLEN)
    - `vstart` stores the starting element index of a vector instruction and must be able to index any element in the range [0, VLMAX_max − 1].

- VL_WIDTH = clog2(VLEN) + 1
    - `vl` stores the number of active elements and must represent values from 0 to VLMAX_max, requiring one additional bit.

The vtype CSR fields follow the RVV specification encoding:

- `vill`, `vma`, and `vta` are single-bit control flags.

- `vsew` uses a 3-bit power-of-two index to represent supported element widths.
- `vlmul` uses a 3-bit index to represent vector register grouping factors.

Finally, fixed-point vector CSRs use minimal widths defined by their semantics:

- `vxrm` is 2 bits to select the rounding mode.

- `vxsat` is 1 bit to indicate saturation.
:::

## Overview Coral NPU Architecture
The Coral NPU is built around a custom RISC-V processor implementing the
`rv32imf_zve32x_zicsr_zifencei_zbb` ISA profile.

This combination of extensions is deliberately chosen to balance programmability, performance, and energy efficiency, which are critical requirements for edge AI acceleration.

- `RV32IMF`
    - `rv32i` : 32-bit Base Integer
    - `m` : Multiplication and Division
    - `f` : Single-Precision Float
- `Zve32x`
    - This is a variant of `v` extension optimized for embedded devices.
    - `zve32` : Limits the vector element width to 32 bits and this matches the standard data types used in infernece (INT8, INT16, INT32).
    - `x` : The variant supports vector `integer operations` only.

Although the Coral NPU is mainly built for machine learning acceleration, this project does not fous on its ML-specific logic. Instead, we focus on the **internal RISC-V CPU**, which handles control logic, scalar operations, and vector execution inside the Coral NPU

### Scalar Core
![image](https://hackmd.io/_uploads/B1KEt4SXZg.png)

- Implements a **RISC-V RV32IMF** scalar processor
- **Four-issue in-order** scalar core, capable of dispatching up to four instructions per cycle.
- Responsible for:
    - program control flow
    - **Command dispatch to the vector backend**
- Uses an **in-order** execution model
- Uses a simple static branch policy
    - Backward branches: taken
    - Forward branches: not taken
- Follows a run-to-completion model
    - No operating system
    - No interrupt support
- Instruction encoding customization:
    - Reclaims the standard RISC-V C (compressed) extension  encoding space
    - Uses the freed encoding space to support:
        - larger SIMD / vector register indexing
- Register Set:
    - 31 scalar registers (x1–x31), 32-bit wide
    - Control and Status Registers (CSRs)

### Vector Core (RVV Core)
![image](https://hackmd.io/_uploads/HkbSK4SmZg.png)

- Implements a fixed-lane SIMD vector core based on `RISC-V Zve32x`
- RVV Frontend
    - Aligns and preprocesses instructions.
    - Manages RVV architectural state.
    - Generates `RVVCmd` objects ( include `vl`, `sew`, `lmul`).
- RVV Backend
    - Implements the core out-of-order execution pipeline for vector operations, and it ensures in-order instruction retirement to maintain architectural state consistency
    - `Decode Unit` : Converts `RVVCmd` into micro-operations (`uop`).
    - `Dispatch Unit` : Dispatching `uop` to reservation stations.
    - `Reservation Stations` : Queues that hold `uop` for execution units.
    - `Execution Units` : Perform vector functions.
    - `Vector Register File (VRF)` : Stores 32 vector registers.
    - `Re-Order Buffer (ROB) and Retire Unit` :
        - Ensuring in-order retirement of instructions
        - Handling exceptions
        - Writing results to VRF

## TODO: Scalar and Vector Instruction Flow in Coral NPU

## Scalar Core Architecture Extraction and Analysis
### Architectural Overview

![scalar_core](https://hackmd.io/_uploads/B1kSS8A7bx.png)

The Scalar Core (`SCore`) is implemented in Chisel and features a multi-lane fetch and dispatch pipeline (configurable via `instructionLanes`). It follows a decoupled architecture where the frontend (Fetch) feeds a central Dispatch unit, which then issues instructions to various specialized execution units.

### Key Characteristics:
- **ISA Support**: RISC-V 32-bit (RV32IM), with optional Floating-Point (RV32F) and Vector (RVV) extensions.
- **Pipeline**: Decoupled Fetch-Dispatch-Execute structure.
- **Multi-issue**: Capable of dispatching multiple instructions per cycle (superscalar) if lanes > 1.
- **Vector Integration**: Tightly coupled with `RvvCore` for handling vector instructions.

### Detailed Component Analysis

#### Fetch Unit (`Fetch.scala`)
The Fetch unit is responsible for retrieving instructions from memory.
- **L0 Cache**: It includes an integrated L0 instruction cache to reduce latency.
- **Branch Prediction**: Implements a partial decoder to identify branches early. It uses a static prediction scheme: backwards branches are assumed taken, forward branches are assumed not taken.
- **Interface**: Delivers aligned instruction blocks to the Dispatch unit.

#### Dispatch Unit (`Dispatch.scala`, `Decode.scala`)
The Dispatch unit (`DispatchV2`) is the brain of the core. It handles decoding, dependency checking, and instruction issuance.
- **Decoding**: Converts raw instruction bits into internal control signals (`DecodedInstruction`).
- **Scoreboarding**: Maintains a scoreboard to track register writes and prevent Read-After-Write (RAW) and Write-After-Write (WAW) hazards.
- **Hazard Handling**:
    - **Structural Hazards**: Checks if execution units (like LSU queue) have space.
    - **Control Hazards**: Flushes the pipeline on mispredicted branches.
- **Vector Interlocks**: Manages configuration state (`vsetvli`) and ensures vector store buffers are synchronized.
- **Issue Logic**: Uses a "Try-Dispatch" loop to greedily issue instructions to available functional units.

#### Load/Store Unit (`Lsu.scala`)
The LSU handles all memory traffic for both scalar and vector operations.
- **Scalar Access**: Supports standard byte, half-word, and word accesses.
- **Vector Access**: Handles complex vector addressing modes including:
    - Unit-stride
    - Strided
    - Indexed (Gather/Scatter)
- **Alignment**: Manages data alignment for sub-word accesses.
- **Store Buffer**: Manages pending stores and writebacks.

#### Execution Units
- **ALU (`Alu.scala`)**: Performs standard integer arithmetic and logic operations. One ALU exists per instruction lane.
- **Branch Unit (BRU) (`Bru.scala`)**: Resolves branch conditions and computes jump targets. Only one BRU manages the program counter changes, but multiple can exist for calculation.
- **Multiplier (MLU) & Divider (DVU)**: Handle integer multiplication and division operations.

#### Register File (`Regfile.scala`)
- **Structure**: A multi-ported register file supporting the RV32I base integer registers.
- **Ports**: Configured based on the number of issue lanes to support simultaneous reads and writes from multiple units.
- **Forwarding**: Works in tandem with the Dispatch scoreboard to handle data forwarding where applicable.

#### Floating Point Unit (Optional)
- **FRegfile**: Separate register file for floating-point registers (`f0`-`f31`).
- **FloatCore**: Wraps the FP execution logic.
- **Integration**: The Dispatch unit handles FS status tracking and scoreboard for FP registers similar to GPRs.

### Vector Core Integration
The construction of `SCore` explicitly supports an external `rvvcore`.
- **Instruction Keep-alive**: Vector instructions are decoded in the scalar core and passed to the vector core.
- **LSU Coupling**: The Scalar LSU handles address generation for vector loads/stores, while the data payload transfer is coordinated with the Vector Core.
- **Synchronization**: The Dispatch unit enforces `vstart` and configuration validity checks before issuing vector instructions.

### Control Flow & Exception Handling
- **Fault Manager**: Aggregates fault signals from Fetch, Decode, and Execution units (e.g., illegal instruction, misaligned access).
- **CSRs**: The `Csr` module maintains the processor status (MSTATUS, MEPC, MCAUSE) and handles interrupt enabling/disabling.
- **Debug**: Includes a Debug Module (DM) interface for external debugging control (halt, resume, single-step).

## RVV Architecture Extraction and Analysis

### RVV Frontend
In `hdl/verilog/rvv/design/RvvFrontEnd.sv`, This module assembles decoded `RVVInstructions` into `RVVCmds` and enqueues them into the `RVVInstructionQueue`.

It is also responsible for **capturing the current vector architectural configuration state** (e.g., SEW, LMUL).

Since the scalar core uses a **4-issue dispatch model**, incoming RVV instructions may be **unaligned** (e.g., [invalid, valid, valid, invalid]). The frontend **aligns these inputs by packing valid commands to the front** (e.g., [valid, valid, invalid, invalid]) before dispatching them to the `RVVbackend`.

**Scalar register operands** required by vector instructions (e.g., for vx or configuration instructions) are **read one cycle after dispatch**. Therefore, this module introduces a **one-cycle latency** before issuing `RVVCmds` to the instruction queue.

::: info
RVVFrontEnd (`RVVInstruction`) absorbs all scalar-side complexity and presents a clean, stable interface to the RVVBackend (`RVVCmd`).
:::

#### Aligner
Inputs to the RVV Frontend may be **unaligned**, meaning valid commands can appear in arbitrary issue slots.

The `Aligner` module reorders these inputs by **moving all valid entries to the front, while preserving their original order**.

In `hdl/verilog/rvv/design/Alinger.sv`, This module implements a prefix-sum–based compaction algorithm.

It first computes a **prefix sum** over the `valid_in` signals to count how many valid entries precede each input, then uses this count to determine the output position.

``` yaml
Example :
- slot 0: scalar add   -> valid_in[0] = 0
- slot 1: vector vadd  -> valid_in[1] = 1
- slot 2: branch       -> valid_in[2] = 0
- slot 3: vector vle   -> valid_in[3] = 1

valid_in  = [0, 1, 0, 1]

After Alignment:
valid_out = [1, 1, 0, 0]
data_out  = [vadd, vle, X, X]
```

#### Constructing the RVVCmd from RVVInstruction
`RVVCmd` is built from a decoded `RVVInstruction`.

If needed, the scalar operand (e.g., rs1) is read from the scalar register file.

The current vector CSR state is captured into `arch_state`, so the instruction uses the **correct vector configuration at dispatch time**, even if the scalar core updates CSRs later.

`RVVCmd` is an internal command used by the `RVVCore` and includes the information required for correct vector execution.

```verilog
// A decoded instruction forwarded to the RVVCore from the scalar core.
typedef struct packed {
  logic [`PC_WIDTH-1:0] pc;
  RVVOpCode             opcode;   // effectively bits [6:0] from instruction
  logic [24:0]          bits;     // bits [31:7] from instruction
} RVVInstruction;

                ||
                ||
                ||
                \/

typedef struct packed {
  logic                         vill;      // Illegal vector configuration flag
  logic [`VL_WIDTH-1:0]         vl;        // Current vector length (VL)
  logic [`VSTART_WIDTH-1:0]     vstart;    // Start index for vector execution
  logic [`VTYPE_VMA_WIDTH-1:0]  ma;        // Mask agnostic: 0=undisturbed, 1=agnostic
  logic [`VTYPE_VTA_WIDTH-1:0]  ta;        // Tail agnostic: 0=undisturbed, 1=agnostic
  RVVXRM                        xrm;       // Fixed-point rounding mode
  logic [`VCSR_VXSAT_WIDTH-1:0] xsat;      // Fixed-point saturation flag (reported to scalar core)
  RVVSEW                        sew;       // Selected element width (SEW)
  RVVLMUL                       lmul;      // Vector register grouping (LMUL)
  RVVLMUL                       lmul_orig; // Original LMUL before widening/narrowing
} RVVConfigState;


typedef struct packed {
  RVVOpCode             opcode;
  logic [24:0]          bits;
  logic [31:0]          rs1;
  RVVConfigState        arch_state;
} RVVCmd;
```

#### Scalar register write-back
When the instruction in slot is a `vset*` instruction, the frontend writes the newly computed `vl` back into the scalar `rd`.

#### Trap
If any insturction in the current bundles should trap, frontend asserts `trap_valid_o` and outputs the first trappig instruction.

### Command Queue (CQ)
Once an instruction is fully prepared, the frontend doesn't send it dircetly to the execution unit.
Instead, it enqueue the generated `RVCmd` into the command queue.

### RVV Backend

#### Decode
This module will read instructions from Command Queue and decode the instrucions to `uop` and write to `Uop queue`.

#### Dispatch

#### Vector Register File (VRF)

##### Vector Register
In `hdl/verilog/rvv/design/rvv_backend_vrf_reg.sv`，The Vector Register File provides **32 vector register (v0-v31)** for the RVV backend.

:::danger
Instead of check the source files, you MUST validate the implementation as earlier as possible.
:::

## System Prerequisites
- **Bazel**: 7.4.1
- **Python**: 3.9–3.12
  - Python 3.13 support is currently in progress
- **SRecord**

## Build the RISC-V vector (RV32IMF_Zve32x) version of Coral NPU
This project uses **Bazel** as the build system to manage and generate the hardware description of the Coral NPU.

## HW/SW verification Flow

### Simple Vector program for Coral NPU

#### Cocotb test
The Coral NPU SoC is **not designed to boot autonomously** after reset.
Instead, the core operates in a **driver-controlled (AXI-driven) execution model**, where program loading, execution control, and data movement are all initiated externally.

In the HW/SW verification environment, **Cocotb acts as a software driver** that interacts with the Coral NPU through its AXI interface. This allows functional verification without requiring the core to fetch instructions from a local boot ROM or RAM at reset.

The Cocotb-based verification flow is summarized as follows:
```
          Reset
            ↓
Driver loads ELF program over AXI
            ↓
Driver writes input buffers
            ↓
Driver sets PC and starts execution
            ↓
Core runs and halts
            ↓
Driver reads output buffers
```

## Phase A: Autonomous Boot at Reset (Implemented)

This section documents the **Phase A** work needed to make the core **boot
autonomously from ITCM/DTCM after reset**, without an external driver writing
CSRs to release reset/clock-gate or to set the initial PC.

### What was missing (why the original flow is not Phase A)

In the original CoreAxi integration, the CSR block (`CoreCSR`) defaults to:

- `resetReg = 3` → reset asserted + clock gate enabled (core clock stopped)
- `pcStartReg = 0`

So *even if ITCM contains valid code*, the core will not execute anything until
an external host performs "kickoff writes" over AXI:

1) Write PC start address
2) Release clock gate
3) Release reset

This host-driven kickoff exists in the UVM environment and is also implicitly
performed by cocotb helpers (e.g. `execute_from()`), therefore it does not meet
Phase A requirements.

### Implementation summary (what we changed)

#### 1) Add a "standalone boot" configuration bit

- `hdl/chisel/src/coralnpu/Parameters.scala`
  - Added `standaloneBoot: Boolean` (default `false`).

- `hdl/chisel/src/coralnpu/Core.scala`
  - Added CLI parsing: `--standaloneBoot=True`.

#### 2) Make the CSR defaults release reset/clock-gate when `standaloneBoot=true`

- `hdl/chisel/src/coralnpu/CoreAxiCSR.scala`
  - `resetReg` init is now conditional:
    - default: `3` (legacy behavior, host-driven)
    - standalone: `0` (ungated, not held in reset)
  - `pcStart` remains `0`, so the reset vector is `0x0`.

Effect: after `aresetn` deasserts and internal reset synchronizer releases,
the core immediately starts fetching from `0x0`.

#### 3) Provide standalone ITCM/DTCM initialization (no host writes required)

- `hdl/verilog/Sram_512x128.v`
  - Added `CORALNPU_STANDALONE_TCM_INIT` mode:
    - Initializes ITCM contents in the memory model.
    - Default built-in boot image writes a marker to DTCM base and executes WFI.
    - Optional file-init macros:
      - `CORALNPU_ITCM_INIT_FILE="..."`
      - When provided, attempts `$readmemh` to load ITCM image.

- `hdl/verilog/Sram_2048x128.v`
  - Added `CORALNPU_STANDALONE_TCM_INIT` mode:
    - Initializes DTCM to zero.
    - Optional file-init macro:
      - `CORALNPU_DTCM_INIT_FILE="..."`

Note: file-init via `$readmemh` is primarily for simulation; on real hardware
you would typically use FPGA BRAM init or an SoC boot ROM / loader (Phase 2).

#### 4) Add a standalone CoreMini AXI build variant

- `hdl/chisel/src/coralnpu/BUILD`
  - Added `core_mini_axi_standalone_cc_library` which:
    - Generates `CoreMiniStandaloneAxi.sv`
    - Enables `--standaloneBoot=True`

#### 5) Add standalone boot tests

- `tests/cocotb/standalone_boot_test.py`
  - A minimal smoke test:
    - Reset only (no kickoff writes)
    - Wait cycles
    - Read `0x10000` and check for expected marker.

- `tests/cocotb/BUILD`
  - Added:
    - `core_mini_axi_standalone_boot_cocotb`
    - `core_mini_axi_standalone_fileinit_boot_cocotb`

### Test results

Standalone boot specific tests:

```bash
bazel test //tests/cocotb:core_mini_axi_standalone_boot_cocotb
bazel test //tests/cocotb:core_mini_axi_standalone_fileinit_boot_cocotb
```

Full regression:

```bash
bazel test //...
```

Result: **203/203 tests PASS** (including the newly added standalone boot tests).

### How to run programs after Phase A

Phase A provides a minimal autonomous boot path. There are two practical ways
to run software:

1) **Recommended for development (host-loaded):**
   - Keep using the existing cocotb flow:
     - `load_elf()` writes sections into ITCM/DTCM over AXI
     - `execute_from(entry_point)` sets PC and starts the core
   - This supports arbitrary programs without rebuilding RTL.

2) **Autonomous boot image (reset-vector):**
   - Replace the built-in ITCM boot image (or provide an init file in simulation),
     so code at `0x0` is your program/bootloader.
   - Phase 2 would typically add a proper boot ROM and external program load path.

### Limitation (what Phase A still does not solve)

Phase A **does not** provide a general-purpose “load arbitrary programs at
runtime” mechanism by itself. It only ensures the core is able to start
executing from a reset vector without an external kickoff.

To support arbitrary programs without rebuilding RTL, you still need a loader
(host-driven `load_elf()` in simulation, or a real bootloader / external memory
load path in a standalone SoC). This is intentionally deferred to Phase 2.

## Reference
[Coral NPU Architecture Datasheet](https://developers.google.com/coral/guides/hardware/datasheet)
