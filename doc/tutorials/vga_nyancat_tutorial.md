# VGA 外設實現完整指南 - Nyancat 動畫教學

本文檔詳細說明 CoralNPU Standalone 的 VGA 外設實現過程，包含架構設計、代碼解析和運行 Nyancat 動畫的完整步驟。

## 目錄

1. [系統架構概覽](#1-系統架構概覽)
2. [VGA 時序規格](#2-vga-時序規格)
3. [硬體設計詳解](#3-硬體設計詳解)
4. [記憶體映射 (MMIO)](#4-記憶體映射-mmio)
5. [軟體驅動程式](#5-軟體驅動程式)
6. [如何運行 Nyancat](#6-如何運行-nyancat)
7. [測試驗證](#7-測試驗證)

---

## 1. 系統架構概覽

```
┌─────────────────────────────────────────────────────────────────┐
│                        CoralNPU Core                            │
│                      (RV32IMF_Zve32x)                           │
└──────────────────────────┬──────────────────────────────────────┘
                           │ MMIO Bus
                           ▼
┌─────────────────────────────────────────────────────────────────┐
│                      VGA Controller                              │
│  ┌─────────────┐    ┌──────────────────┐    ┌───────────────┐   │
│  │  MMIO       │    │  TrueDualPortRAM │    │  VGA Timing   │   │
│  │  Registers  │───▶│  (Framebuffer)   │───▶│  Generator    │   │
│  │             │    │  12 frames ×     │    │               │   │
│  │  - CTRL     │    │  64×64 pixels    │    │  640×480@72Hz │   │
│  │  - STATUS   │    │  4-bit indexed   │    │               │   │
│  │  - PALETTE  │    └──────────────────┘    └───────┬───────┘   │
│  │  - UPLOAD   │                                    │           │
│  └─────────────┘                                    ▼           │
│                                              ┌─────────────┐    │
│                                              │  Palette    │    │
│                                              │  Lookup     │    │
│                                              │  16 colors  │    │
│                                              │  6-bit RGB  │    │
│                                              └──────┬──────┘    │
└─────────────────────────────────────────────────────┼───────────┘
                                                      │
                                                      ▼
                                          ┌───────────────────┐
                                          │   VGA Output      │
                                          │   HSYNC, VSYNC    │
                                          │   R[1:0]G[1:0]B[1:0]│
                                          └───────────────────┘
```

### 關鍵設計決策

1. **雙時鐘域設計**: CPU 時鐘 (sysclk) 與像素時鐘 (pixclk ~31.5MHz) 分離
2. **幀緩衝動畫**: 12 個獨立幀，支援流暢動畫切換
3. **縮放顯示**: 64×64 像素縮放 6× 到 384×384，置中於 640×480 螢幕
4. **調色板索引**: 4-bit 索引 → 6-bit RGB，節省記憶體

---

## 2. VGA 時序規格

我們使用 **640×480 @ 72Hz** 標準時序：

| 參數 | 水平 (H) | 垂直 (V) |
|------|---------|---------|
| 可見區域 | 640 像素 | 480 行 |
| 前廊 (Front Porch) | 24 像素 | 9 行 |
| 同步脈衝 (Sync Pulse) | 40 像素 | 3 行 |
| 後廊 (Back Porch) | 128 像素 | 28 行 |
| **總計** | **832 像素** | **520 行** |

像素時鐘頻率: `832 × 520 × 72 Hz ≈ 31.5 MHz`

### 時序圖

```
水平時序 (一行):
    ←─ 640 ─→←24→←40→←─ 128 ─→
    ┌───────┐    ┌──┐
────┤ VIDEO ├────┤  ├──────────
    └───────┘    └──┘
                 HSYNC (負極性)

垂直時序 (一幀):
    ←─ 480 ─→←9→←3→←─ 28 ─→
    ┌───────┐   ┌─┐
────┤ VIDEO ├───┤ ├────────────
    └───────┘   └─┘
                VSYNC (負極性)
```

---

## 3. 硬體設計詳解

### 3.1 檔案結構

```
hdl/
├── chisel/src/peripherals/
│   ├── VGA.scala              # 主 VGA 控制器
│   ├── TrueDualPortRAM32.scala # 雙埠 RAM 包裝
│   ├── VgaStandaloneWrapper.scala # 測試包裝
│   └── VGATest.scala          # 單元測試
└── verilog/
    └── TrueDualPortRAM32.v    # 雙埠 RAM 原語
```

### 3.2 VGA.scala 核心模組

#### 幀緩衝記憶體配置

```scala
// 每幀 64×64 = 4096 像素
// 每像素 4-bit，每 word 32-bit = 8 像素
// 每幀 512 words
// 12 幀 = 6144 words = 24KB
val FRAME_WIDTH      = 64
val FRAME_HEIGHT     = 64
val PIXELS_PER_FRAME = FRAME_WIDTH * FRAME_HEIGHT  // 4096
val WORDS_PER_FRAME  = PIXELS_PER_FRAME / 8        // 512
val NUM_FRAMES       = 12
val TOTAL_WORDS      = WORDS_PER_FRAME * NUM_FRAMES // 6144
```

#### 跨時鐘域同步 (CDC)

CPU 和 VGA 使用不同時鐘，需要同步：

```scala
// CPU → VGA: 控制信號雙暫存器同步
val ctrl_enable_sync1 = withClock(io.pixClock)(RegNext(ctrl_enable))
val ctrl_enable_synced = withClock(io.pixClock)(RegNext(ctrl_enable_sync1))

// VGA → CPU: 狀態信號雙暫存器同步  
val vblank_sync1 = RegNext(wire_in_vblank)
val vblank_synced = RegNext(vblank_sync1)
```

#### 像素縮放邏輯

```scala
// 6× 縮放: 64 → 384 像素
val SCALE = 6
val SCALED_WIDTH = FRAME_WIDTH * SCALE   // 384
val SCALED_HEIGHT = FRAME_HEIGHT * SCALE // 384

// 置中偏移
val X_OFFSET = (640 - SCALED_WIDTH) / 2  // 128
val Y_OFFSET = (480 - SCALED_HEIGHT) / 2 // 48

// 計算幀緩衝座標
val frame_x = (h_count - X_OFFSET) / SCALE
val frame_y = (v_count - Y_OFFSET) / SCALE
```

### 3.3 TrueDualPortRAM32 雙埠 RAM

這是關鍵的記憶體元件，允許：
- **Port A (CPU 時鐘)**: 寫入幀緩衝數據
- **Port B (像素時鐘)**: 讀取像素數據

```verilog
// TrueDualPortRAM32.v
module TrueDualPortRAM32 #(
    parameter DEPTH = 6144
)(
    input clka, clkb,
    input wea,
    input [$clog2(DEPTH)-1:0] addra, addrb,
    input [31:0] dina,
    output reg [31:0] douta, doutb
);
    reg [31:0] mem [0:DEPTH-1];
    
    always @(posedge clka) begin
        if (wea) mem[addra] <= dina;
        douta <= mem[addra];
    end
    
    always @(posedge clkb) begin
        doutb <= mem[addrb];
    end
endmodule
```

---

## 4. 記憶體映射 (MMIO)

VGA 外設位於地址 **0x50000**（或 highmem 0x220000）

| 偏移 | 名稱 | 讀/寫 | 描述 |
|------|------|-------|------|
| 0x00 | ID | R | 識別碼 `0x56474131` ('VGA1') |
| 0x04 | CTRL | R/W | 控制暫存器 |
| 0x08 | STATUS | R | 狀態暫存器 |
| 0x0C | INTR_STATUS | R/W | 中斷狀態（寫1清除） |
| 0x10 | UPLOAD_ADDR | R/W | 上傳地址 [19:16]=幀, [15:0]=像素偏移 |
| 0x14 | STREAM_DATA | W | 串流數據（自動遞增地址） |
| 0x20-0x5F | PALETTE[0-15] | R/W | 16 色調色板，每色 6-bit |

### CTRL 暫存器 (0x04)

| Bit | 名稱 | 描述 |
|-----|------|------|
| 0 | ENABLE | 1=啟用顯示 |
| 1 | VBLANK_IE | 1=啟用 VBlank 中斷 |
| 11:8 | FRAME_SEL | 顯示幀選擇 (0-11) |

### STATUS 暫存器 (0x08)

| Bit | 名稱 | 描述 |
|-----|------|------|
| 0 | UPLOAD_BUSY | 上傳忙碌中 |
| 1 | SAFE_TO_SWAP | VBlank 期間，可安全切換幀 |
| 2 | IN_VBLANK | 目前在垂直消隱期間 |
| 7:4 | CURR_FRAME | 目前顯示的幀 |

---

## 5. 軟體驅動程式

### 5.1 VGA 初始化

```cpp
#define VGA_BASE     0x50000
#define VGA_ID       (*(volatile uint32_t*)(VGA_BASE + 0x00))
#define VGA_CTRL     (*(volatile uint32_t*)(VGA_BASE + 0x04))
#define VGA_STATUS   (*(volatile uint32_t*)(VGA_BASE + 0x08))
#define VGA_UPLOAD   (*(volatile uint32_t*)(VGA_BASE + 0x10))
#define VGA_STREAM   (*(volatile uint32_t*)(VGA_BASE + 0x14))
#define VGA_PALETTE  ((volatile uint32_t*)(VGA_BASE + 0x20))

void vga_init() {
    // 驗證 VGA 存在
    if (VGA_ID != 0x56474131) {
        // VGA not found!
        return;
    }
    
    // 啟用顯示，選擇幀 0
    VGA_CTRL = 0x01;
}
```

### 5.2 設定調色板

```cpp
void vga_set_palette(const uint8_t* colors, int count) {
    for (int i = 0; i < count && i < 16; i++) {
        // 6-bit color: RRGGBB
        VGA_PALETTE[i] = colors[i] & 0x3F;
    }
}

// Nyancat 調色板
const uint8_t nyancat_palette[] = {
    0x01,  // 0: 深藍 (背景)
    0x3F,  // 1: 白色
    0x00,  // 2: 黑色
    0x3E,  // 3: 黃色
    0x3B,  // 4: 淺橙
    0x36,  // 5: 橙色
    0x30,  // 6: 紅色
    0x38,  // 7: 粉紅
    0x3C,  // 8: 淺黃
    0x0C,  // 9: 綠色
    0x0B,  // 10: 青色
    0x17,  // 11: 藍色
    0x2A,  // 12: 紫色
    0x3A,  // 13: 膚色
};
```

### 5.3 上傳幀數據

```cpp
void vga_upload_frame(int frame_num, const uint32_t* data) {
    // 設定上傳地址: [19:16]=幀, [15:0]=像素偏移
    VGA_UPLOAD = (frame_num << 16) | 0;
    
    // 串流 512 個 words (每個 8 像素)
    for (int i = 0; i < 512; i++) {
        VGA_STREAM = data[i];  // 自動遞增 8 像素
    }
}
```

### 5.4 動畫播放

```cpp
void vga_animate() {
    static int current_frame = 0;
    
    // 等待 VBlank
    while (!(VGA_STATUS & 0x04));  // 等待進入 VBlank
    while (VGA_STATUS & 0x04);     // 等待離開 VBlank
    
    // 切換到下一幀
    current_frame = (current_frame + 1) % 12;
    VGA_CTRL = 0x01 | (current_frame << 8);
}
```

---

## 6. 如何運行 Nyancat

### 6.1 前置條件

確保你已經安裝：
- Bazel 構建系統
- RISC-V 工具鏈 (riscv32-unknown-elf-gcc)
- Verilator (用於模擬)

### 6.2 編譯程式

```bash
cd /home/tobyphant/Documents/coding/Rework-Coral-NPU-as-standalone-RV32IMF_Zve32x-RISC-V-core

# 編譯 nyancat_vga 程式
bazel build //examples:coralnpu_v2_nyancat_vga
```

輸出檔案：
- `bazel-bin/examples/coralnpu_v2_nyancat_vga.elf` - ELF 執行檔
- `bazel-bin/examples/coralnpu_v2_nyancat_vga.bin` - 二進制映像
- `bazel-bin/examples/coralnpu_v2_nyancat_vga.vmem` - Verilog 記憶體初始化

### 6.3 驗證 VGA 外設功能（Chisel 測試）

運行 VGA 單元測試來驗證外設功能：

```bash
bazel test //hdl/chisel/src/peripherals:vga_tests --test_output=all
```

預期輸出：
```
VGASpec:
- VGA ID register returns correct value (2 seconds)
- VGA write and read palette registers (1 second)
- VGA control register enables display (1 second)
- VGA upload address register (1 second)
- VGA stream data with auto-increment (1 second)
- VGA initialize nyancat palette (1 second)
- VGA generates sync signals (1 second)
- VGA frame select works (1 second)

Tests: succeeded 8, failed 0
All tests passed.
```

### 6.4 方法一：FPGA 硬體（推薦看到真實動畫）

這是看到真正 Nyancat 動畫的最佳方式：

1. **合成 bitstream**:
```bash
bazel build //fpga:chip_nexus
```

2. **燒錄到 FPGA**:
```bash
# 使用 Vivado
vivado -mode batch -source program_fpga.tcl
```

3. **連接 VGA 顯示器**:
   - 將 FPGA 的 VGA 埠連接到顯示器
   - 顯示器會自動偵測 640×480@72Hz

4. **載入程式**:
```bash
# 透過 GDB/JTAG 載入
riscv32-unknown-elf-gdb bazel-bin/examples/coralnpu_v2_nyancat_vga.elf
(gdb) target remote :3333
(gdb) load
(gdb) continue
```

### 6.5 方法二：Verilator 模擬

目前模擬器使用 stub VGA 外設（僅返回 ID 暫存器），完整的 VGA 模擬需要額外設置像素時鐘。

構建模擬器：
```bash
bazel build //hw_sim:core_mini_axi_simulator_example
```

注意：完整的 VGA 視覺輸出需要修改模擬器以支持：
1. 提供 31.5MHz 像素時鐘
2. 捕獲 VGA 輸出信號
3. 渲染到視窗或保存為圖像

### 6.6 方法三：使用 GTKWave 查看波形

你可以通過波形觀察 VGA 時序信號：

```bash
# 構建並運行帶有 VCD 輸出的測試
bazel test //hdl/chisel/src/peripherals:vga_tests

# 在測試中添加 VCD 輸出（需要修改測試代碼）
```

在 GTKWave 中觀察這些信號：
- `hsync` - 水平同步
- `vsync` - 垂直同步  
- `rgb[5:0]` - 像素顏色
- `activevideo` - 有效視訊區域

### 6.7 預期結果

當程式在 FPGA 上運行時，你會看到：

```
╔═══════════════════════════════════════╗
║           640×480 螢幕                ║
║  ┌─────────────────────────────────┐  ║
║  │                                 │  ║
║  │     ╔═══════════════════╗       │  ║
║  │     ║   Nyancat 動畫    ║       │  ║
║  │     ║   384×384 像素    ║       │  ║
║  │     ║   (64×64 × 6)     ║       │  ║
║  │     ║                   ║       │  ║
║  │     ║    🐱🌈           ║       │  ║
║  │     ║                   ║       │  ║
║  │     ╚═══════════════════╝       │  ║
║  │                                 │  ║
║  └─────────────────────────────────┘  ║
║           深藍色背景                   ║
╚═══════════════════════════════════════╝
```

動畫以 12 幀循環播放，幀率約 6-10 FPS。

---

## 7. 測試驗證

### 7.1 運行單元測試

```bash
bazel test //hdl/chisel/src/peripherals:vga_tests --test_output=all
```

### 7.2 測試項目說明

| 測試名稱 | 驗證內容 |
|---------|---------|
| VGA ID register returns correct value | ID 暫存器返回 0x56474131 |
| VGA write and read palette registers | 調色板讀寫正確 |
| VGA control register enables display | 控制暫存器功能 |
| VGA upload address register | 上傳地址設定 |
| VGA stream data with auto-increment | 串流數據自動遞增 |
| VGA initialize nyancat palette | 完整調色板初始化 |
| VGA generates sync signals | 同步信號生成 |
| VGA frame select works | 幀選擇功能 |

### 7.3 預期輸出

```
VGASpec:
- VGA ID register returns correct value (2 seconds)
- VGA write and read palette registers (1 second)
- VGA control register enables display (1 second)
- VGA upload address register (1 second)
- VGA stream data with auto-increment (1 second)
- VGA initialize nyancat palette (1 second)
- VGA generates sync signals (1 second)
- VGA frame select works (1 second)

Tests: succeeded 8, failed 0
All tests passed.
```

---

## 附錄 A：顏色說明

| 索引 | 顏色 | 6-bit RGB | 用途 |
|------|------|-----------|------|
| 0 | 深藍 | 0x01 | 背景/天空 |
| 1 | 白色 | 0x3F | 星星/高光 |
| 2 | 黑色 | 0x00 | 輪廓 |
| 3 | 黃色 | 0x3E | Pop-Tart 糖霜 |
| 4-6 | 橙/紅 | 0x3B-0x30 | 彩虹 |
| 7 | 粉紅 | 0x38 | Pop-Tart 本體 |
| 8 | 淺黃 | 0x3C | 彩虹 |
| 9-11 | 綠/青/藍 | 0x0C-0x17 | 彩虹 |
| 12 | 紫色 | 0x2A | 彩虹 |
| 13 | 膚色 | 0x3A | 貓咪臉 |

## 附錄 B：常見問題

### Q: 畫面沒有顯示？

1. 確認 VGA_ID 讀取正確 (0x56474131)
2. 確認 VGA_CTRL 的 ENABLE 位元已設定
3. 檢查像素時鐘是否正確 (~31.5MHz)

### Q: 畫面閃爍？

使用 VBlank 同步來切換幀：
```cpp
while (!(VGA_STATUS & 0x04)); // 等待 VBlank
VGA_CTRL = 0x01 | (new_frame << 8);
```

### Q: 顏色不對？

檢查調色板設定，每個顏色值應為 6-bit (0-63)。

### Q: 編譯錯誤？

確保已安裝所有依賴：
```bash
# 安裝 Bazel
sudo apt install bazel

# 確認工具鏈
which riscv32-unknown-elf-gcc
```

---

## 附錄 C：相關檔案

| 檔案 | 說明 |
|------|------|
| `hdl/chisel/src/peripherals/VGA.scala` | VGA 控制器主模組 |
| `hdl/chisel/src/peripherals/TrueDualPortRAM32.scala` | 雙埠 RAM Scala 包裝 |
| `hdl/verilog/TrueDualPortRAM32.v` | 雙埠 RAM Verilog 實現 |
| `hdl/chisel/src/peripherals/VGATest.scala` | 單元測試 |
| `examples/nyancat_vga.cc` | Nyancat 動畫程式 |
| `hdl/chisel/src/common/Parameters.scala` | 記憶體映射配置 |

---

*文檔版本: 1.0*
*最後更新: 2026-01-19*
