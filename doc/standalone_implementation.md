# CoralNPU Standalone 實現說明

本文檔說明如何將 CoralNPU 從 Google Coral TPU 的配套處理器改造為獨立運作的 RV32IMF_Zve32x RISC-V 核心。

## 目錄

1. [專案背景](#專案背景)
2. [完成的功能](#完成的功能)
3. [VGA 周邊設備實現](#vga-周邊設備實現)
4. [程式執行器實現](#程式執行器實現)
5. [測試程式](#測試程式)
6. [使用方法](#使用方法)
7. [技術細節](#技術細節)
8. [已知限制](#已知限制)

---

## 專案背景

### 原始架構

```
┌─────────────────────────────────────────────┐
│              Google Coral TPU               │
│  ┌─────────┐    ┌─────────┐    ┌─────────┐  │
│  │   TPU   │←──→│ CoralNPU│←──→│  Memory │  │
│  │  矩陣   │    │ (配角)  │    │         │  │
│  └─────────┘    └─────────┘    └─────────┘  │
└─────────────────────────────────────────────┘
```

### 目標架構

```
┌─────────────────────────────────────────────┐
│           CoralNPU Standalone               │
│  ┌─────────┐    ┌─────────┐    ┌─────────┐  │
│  │ CoralNPU│←──→│   VGA   │←──→│  Memory │  │
│  │ (主角)  │    │ 周邊    │    │  TCM    │  │
│  └─────────┘    └─────────┘    └─────────┘  │
└─────────────────────────────────────────────┘
```

### CoralNPU 規格

| 項目 | 規格 |
|------|------|
| ISA | RV32IMF_Zve32x (RISC-V 32-bit + 向量擴展) |
| 整數乘除 | M 擴展 |
| 浮點運算 | F 擴展 (單精度) |
| 向量運算 | Zve32x (32-bit 向量元素) |
| 記憶體 | ITCM 64KB + DTCM 32KB |

---

## 完成的功能

### 1. VGA 周邊設備

新增 VGA 輸出功能，可以在螢幕上顯示圖形。

**檔案：**
- `hdl/chisel/src/coralnpu/VGA.scala` - VGA 控制器 (Chisel)
- `hdl/chisel/src/coralnpu/VgaStandaloneWrapper.scala` - 測試用包裝器
- `tests/cocotb/vga/test_vga.py` - Cocotb 測試
- `tests/cocotb/vga/verilator/vga_sim.cc` - SDL2 視覺化 Demo

**規格：**
- 解析度：640×480 @ 60Hz (VGA 標準)
- 內部 Framebuffer：64×64 像素
- 顏色：16 色調色盤
- 動畫：支援 12 幀動畫切換

### 2. 程式執行器 (coralnpu_runner)

通用的 RISC-V 程式執行器，可以載入 ELF 檔案並在 CoralNPU 上執行。

**檔案：**
- `hw_sim/coralnpu_runner.cc` - 主程式
- `hw_sim/BUILD` - Bazel 建置規則

**功能：**
- 載入 ELF 格式的 RISC-V 程式
- 在 Verilator 模擬器上執行
- 讀取 Mailbox 結果並顯示
- 支援超時設定

### 3. 範例程式

**Fibonacci (`examples/fibonacci.cc`)：**
- 遞迴計算 fib(10) = 55
- 迭代計算 fib(20) = 6765
- 驗證 CPU 的整數運算和遞迴能力

**Quicksort (`examples/quicksort.cc`)：**
- 找出陣列最小值和最大值
- 驗證 CPU 的比較和分支指令

---

## VGA 周邊設備實現

### 參考來源

參考 `ca2025-mycpu` 專案的 VGA 實現方式，但針對 CoralNPU 的記憶體架構做調整。

### 記憶體映射

```
VGA Base Address: 0x30000000

偏移量          用途              大小
────────────────────────────────────────
0x0000          控制暫存器         4 bytes
0x0004          調色盤 (16色)      64 bytes
0x0100          Framebuffer        2048 bytes (64×64×4bit)
0x0900          動畫幀 0           2048 bytes
0x1100          動畫幀 1           2048 bytes
...
0x6100          動畫幀 11          2048 bytes
```

### 控制暫存器 (CTRL)

```
Bit 位置    用途
────────────────────────
[0]         VGA 啟用 (1=開啟)
[3:1]       保留
[7:4]       動畫幀選擇 (0-11)
[31:8]      保留
```

### VGA 時序

使用標準 VGA 640×480 @ 60Hz 時序：

| 參數 | 值 |
|------|-----|
| 像素時鐘 | 25.175 MHz |
| 水平總計 | 800 像素 |
| 垂直總計 | 525 行 |
| 可見區域 | 640×480 |

### 像素縮放

64×64 的 Framebuffer 透過 6 倍縮放顯示在 384×384 的區域中（置中於 640×480）。

---

## 程式執行器實現

### 架構

```
┌─────────────────────────────────────────────────────┐
│                  coralnpu_runner                     │
├─────────────────────────────────────────────────────┤
│  1. 建立 CoralNPUSimulator (Verilator)              │
│  2. 載入 ELF 檔案到 TCM 記憶體                       │
│  3. 設定 PC 到入口點並開始執行                       │
│  4. 等待 WFI 指令 (程式結束)                         │
│  5. 讀取 Mailbox 內容並顯示結果                      │
└─────────────────────────────────────────────────────┘
```

### Mailbox 通訊機制

Mailbox 是 CPU 與 Host 之間的通訊橋樑：

```cpp
// CPU 端 (RISC-V 程式)
volatile uint32_t* mailbox = (volatile uint32_t*)0x20000000;
mailbox[0] = result;  // 寫入結果
asm("wfi");           // 通知結束

// Host 端 (模擬器)
CoralNPUMailbox m = simulator->ReadMailbox();
std::cout << m.message[0] << std::endl;  // 讀取結果
```

### 支援的程式

| 名稱 | 路徑 | 說明 |
|------|------|------|
| fibonacci | examples/coralnpu_v2_fibonacci.elf | Fibonacci 計算 |
| quicksort | examples/coralnpu_v2_quicksort.elf | 排序演算法 |
| hello | examples/coralnpu_v2_hello_world_add_floats.elf | 浮點加法 |
| mailbox | hw_sim/mailbox_example.elf | Mailbox 測試 |

---

## 測試程式

### Fibonacci 程式

```cpp
// examples/fibonacci.cc

// 遞迴版本
int fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// 迭代版本
int fib_iterative(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main() {
    mailbox[0] = fib_recursive(10);  // 55
    mailbox[1] = fib_iterative(20);  // 6765
    mailbox[2] = 0xF1B0ACC1;         // 標記
    mailbox[3] = fib_iterative(15);  // 610
    asm("wfi");
    return 0;
}
```

### 預期輸出

```
========================================
  Mailbox Contents (Results)
========================================
  mailbox[ 0] = 0x00000037 (55)
  mailbox[ 1] = 0x00001a6d (6765)
  mailbox[ 2] = 0xf1b0acc1 (-240079679)
  mailbox[ 3] = 0x00000262 (610)

  🎉 Fibonacci results verified!
     fib(10) = 55 ✓
     fib(20) = 6765 ✓
```

---

## 使用方法

### 建置環境需求

- Bazel 建置系統
- GCC/Clang C++ 編譯器
- Verilator (Verilog 模擬器)
- SDL2 (VGA Demo 用)

### 執行程式

```bash
# 進入專案目錄
cd /path/to/Rework-Coral-NPU-as-standalone-RV32IMF_Zve32x-RISC-V-core

# 執行 Fibonacci
bazel run //hw_sim:coralnpu_runner -- fibonacci

# 執行 Quicksort
bazel run //hw_sim:coralnpu_runner -- quicksort

# 執行 Mailbox 測試
bazel run //hw_sim:coralnpu_runner -- mailbox

# 自訂超時時間 (毫秒)
bazel run //hw_sim:coralnpu_runner -- fibonacci 5000
```

### VGA Demo

```bash
# 進入 VGA Demo 目錄
cd tests/cocotb/vga/verilator

# 建置並執行
make demo

# SSH/遠端使用時加入軟體渲染
SDL_RENDER_DRIVER=software make demo
```

### 編寫新程式

1. 建立 C++ 源碼：

```cpp
// examples/my_program.cc
#include <cstdint>

volatile uint32_t* mailbox = (volatile uint32_t*)0x20000000;

int main() {
    // 你的程式碼
    mailbox[0] = 42;  // 輸出結果
    asm("wfi");       // 結束
    return 0;
}
```

2. 加入 BUILD 規則：

```python
# examples/BUILD.bazel
coralnpu_v2_binary(
    name = "coralnpu_v2_my_program",
    srcs = ["my_program.cc"],
)
```

3. 建置並執行：

```bash
bazel build //examples:coralnpu_v2_my_program
bazel run //hw_sim:coralnpu_runner -- /path/to/my_program.elf
```

---

## 技術細節

### 建置系統

專案使用 Bazel 建置系統，主要規則：

| 規則 | 用途 |
|------|------|
| `coralnpu_v2_binary` | 編譯 RISC-V 程式 |
| `cc_binary` | 編譯 Host 程式 |
| `chisel_library` | 編譯 Chisel 硬體 |
| `verilator_cc_library` | 生成 Verilator 模擬器 |

### 記憶體配置

```
地址空間                    用途
────────────────────────────────────────
0x00000000 - 0x0000FFFF    ITCM (64KB 指令記憶體)
0x00010000 - 0x00017FFF    DTCM (32KB 資料記憶體)
0x20000000 - 0x2000000F    Mailbox (16 bytes)
0x30000000 - 0x30006FFF    VGA (28KB)
```

### 工具鏈

使用自訂的 RISC-V 工具鏈：
- 編譯器：riscv32-unknown-elf-gcc
- ABI：ilp32 (32-bit int/long/pointer)
- ISA：rv32imf_zve32x

---

## 已知限制

### 1. 只在模擬器上運行

目前所有測試都在 Verilator 模擬器上執行，尚未燒錄到 FPGA。

### 2. Mailbox 只有 4 個字

`CoralNPUMailbox` 結構只有 4 個 32-bit 元素：

```cpp
struct CoralNPUMailbox {
  uint32_t message[4] = {0, 0, 0, 0};
};
```

### 3. 陣列操作可能有問題

在某些情況下，使用本地陣列可能導致結果錯誤，原因可能是：
- 堆疊空間限制
- 記憶體對齊問題
- 編譯器優化問題

**解決方法：** 使用全域變數或簡化邏輯。

### 4. 沒有標準輸出

CoralNPU 沒有 UART，所以 `printf` 不會顯示任何內容。所有輸出必須透過 Mailbox。

### 5. VGA 尚未整合到完整模擬

VGA Demo (`vga_sim.cc`) 是獨立運行的，使用 C++ 直接控制 VGA 暫存器，而不是由 CPU 程式控制。

完整整合需要：
- 修改 CoreAxi.scala 加入 VGA 介面
- 提供像素時鐘 (25.175 MHz)
- 擴展模擬器以支援 VGA 輸出

---

## 檔案結構

```
專案根目錄/
├── doc/
│   ├── standalone_implementation.md  ← 本文檔
│   ├── vga_implementation_changes.md  ← VGA 詳細說明
│   └── vga_peripheral.md              ← VGA 規格
├── examples/
│   ├── fibonacci.cc                   ← Fibonacci 範例
│   ├── quicksort.cc                   ← Quicksort 範例
│   └── BUILD.bazel                    ← 建置規則
├── hdl/chisel/src/coralnpu/
│   ├── VGA.scala                      ← VGA 控制器
│   └── VgaStandaloneWrapper.scala     ← VGA 測試包裝
├── hw_sim/
│   ├── coralnpu_runner.cc             ← 程式執行器
│   ├── coralnpu_simulator.h           ← 模擬器介面
│   └── mailbox.h                      ← Mailbox 定義
└── tests/cocotb/vga/
    ├── test_vga.py                    ← VGA 測試
    └── verilator/
        ├── vga_sim.cc                 ← VGA SDL2 Demo
        └── Makefile                   ← 建置腳本
```

---

## 後續發展方向

1. **FPGA 實現** - 將設計燒錄到 Artix-7 或類似 FPGA
2. **UART 支援** - 加入串口輸出以支援 printf
3. **完整 VGA 整合** - 讓 CPU 程式可以控制 VGA
4. **Boot ROM** - 自動載入程式而不需要 Host
5. **中斷系統** - 支援外部中斷和計時器
6. **更多周邊** - GPIO, SPI, I2C 等

---

## 參考資料

- [RISC-V 規格](https://riscv.org/specifications/)
- [Chisel 文檔](https://www.chisel-lang.org/)
- [Verilator 手冊](https://verilator.org/guide/latest/)
- [VGA 時序標準](http://tinyvga.com/vga-timing/640x480@60Hz)
- [ca2025-mycpu](../ca2025-mycpu/) - VGA 參考實現

---

*文檔版本：1.0*  
*最後更新：2026-01-19*
