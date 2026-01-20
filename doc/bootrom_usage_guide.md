# CoralNPU Boot ROM 使用指南

## 概述

本文件說明如何使用 Boot ROM 來載入並執行程式（以 Fibonacci 為例）。

### Boot ROM 開機流程

```
┌─────────────────────────────────────────────────────────────────┐
│                        開機流程圖                                │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  1. CPU 從 Boot ROM (0x40000) 開始執行                          │
│                     ↓                                           │
│  2. Boot ROM 從 Flash (0x20000000) 讀取程式碼                   │
│                     ↓                                           │
│  3. Boot ROM 將程式碼複製到 ITCM (0x00000000)                   │
│                     ↓                                           │
│  4. Boot ROM 跳轉到 ITCM 基址執行應用程式                       │
│                     ↓                                           │
│  5. 應用程式開始執行                                            │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### 記憶體映射

| 區域 | 起始地址 | 大小 | 用途 |
|------|----------|------|------|
| ITCM | 0x00000000 | 8KB | 指令記憶體（程式碼執行區） |
| DTCM | 0x00010000 | 32KB | 資料記憶體（堆疊、全域變數） |
| CSR  | 0x00030000 | 4KB | 控制狀態暫存器 |
| Boot ROM | 0x00040000 | 8KB | 開機載入程式（唯讀） |
| Flash | 0x20000000 | 外部 | 程式儲存區（透過 AXI Master 存取） |

---

## 快速開始

### 執行 Fibonacci 程式（使用 Boot ROM）

```bash
cd /home/tobyphant/Documents/coding/Rework-Coral-NPU-as-standalone-RV32IMF_Zve32x-RISC-V-core

# 執行 Boot ROM runner
bazel run //hw_sim:coralnpu_bootrom_runner -- fibonacci 30000
```

參數說明：
- `fibonacci`：要執行的程式名稱
- `30000`：超時時間（毫秒）

### 預期輸出

```
========================================
  CoralNPU Boot ROM Runner
  RV32IMF_Zve32x RISC-V Core
  (Authentic Boot Process)
========================================

[BOOT] Loading Boot ROM from sw/bootrom/boot_default.bin
[BOOT] Boot ROM loaded: 48 bytes
[ELF] Loading examples/coralnpu_v2_fibonacci.elf
[DATA] Preloading .data section to DTCM...

[BOOT] Starting CPU from Boot ROM at 0x40000
[BOOT] Boot ROM will:
       1. Copy Flash (0x20000000) -> ITCM (0x00000000)
       2. Jump to ITCM base (0x00000000)

[CPU] ✓ Program terminated successfully

  External Mailbox (via AXI writes):
  ext_mailbox[ 0] = 0x00000037 (55)      <- fib(10)
  ext_mailbox[ 1] = 0x00001a6d (6765)    <- fib(20)
  ext_mailbox[ 2] = 0xf1b0acc1           <- 魔術標記
  ext_mailbox[ 3] = 0x00000262 (610)     <- fib(15)

  🎉 External Fibonacci results verified!
     fib(10) = 55 ✓
     fib(20) = 6765 ✓
```

---

## 與原始 Runner 的比較

### 原始方式（直接載入）

```bash
bazel run //hw_sim:coralnpu_runner -- fibonacci 10000
```

**流程：**
1. Host 透過 AXI Slave 直接將 ELF 寫入 ITCM
2. CPU 從 ITCM 地址 0x0 開始執行

**優點：** 簡單快速
**缺點：** 不符合真實硬體開機流程

### Boot ROM 方式（真實開機流程）

```bash
bazel run //hw_sim:coralnpu_bootrom_runner -- fibonacci 30000
```

**流程：**
1. Boot ROM 載入到 0x40000
2. ELF 程式載入到模擬 Flash (0x20000000)
3. .data 區段預載到 DTCM
4. CPU 從 Boot ROM 開始執行
5. Boot ROM 複製 Flash → ITCM
6. 跳轉到 ITCM 執行應用程式

**優點：** 模擬真實 FPGA/ASIC 開機流程
**缺點：** 稍慢（需要複製 8KB）

---

## Boot ROM 程式碼解析

Boot ROM 位於 `sw/bootrom/boot_default.S`：

```assembly
_start:
    # 1. 設定來源、目的、大小
    li s0, 0x20000000       # 來源：Flash
    li s1, 0x00000000       # 目的：ITCM
    li s2, 0x00002000       # 大小：8KB
    add s2, s2, s1          # 結束地址

copy_loop:
    # 2. 複製迴圈（每次 4 bytes）
    lw t0, 0(s0)            # 從 Flash 讀取
    sw t0, 0(s1)            # 寫入 ITCM
    addi s0, s0, 4          # 來源指標 +4
    addi s1, s1, 4          # 目的指標 +4
    blt s1, s2, copy_loop   # 繼續直到完成

    # 3. 同步指令快取
    fence.i

    # 4. 跳轉到 ITCM 執行
    li t0, 0x00000000
    jr t0
```

---

## 支援的程式

| 程式名稱 | ELF 路徑 | 說明 |
|----------|----------|------|
| fibonacci | examples/coralnpu_v2_fibonacci.elf | 計算 Fibonacci 數列 |
| quicksort | examples/coralnpu_v2_quicksort.elf | 快速排序演算法 |

### 執行其他程式

```bash
# 執行 quicksort
bazel run //hw_sim:coralnpu_bootrom_runner -- quicksort 30000

# 執行自訂 ELF
bazel run //hw_sim:coralnpu_bootrom_runner -- /path/to/your/program.elf 30000
```

---

## 技術細節

### 為什麼需要預載 .data 區段？

Boot ROM 只複製程式碼（.text）從 Flash 到 ITCM，但不處理資料區段（.data）。

例如 Fibonacci 程式中的全域變數：
```cpp
volatile uint32_t* mailbox = reinterpret_cast<volatile uint32_t*>(0x20000000L);
```

這個 `mailbox` 指標存放在 .data 區段（0x10000，DTCM），如果不預載，程式會讀到未初始化的值。

### Boot ROM Runner 的處理方式

```cpp
// 預載 .data 區段到 DTCM
if (data_section_size > 0) {
    simulator->WriteTCM(data_section_dtcm_addr, data_section_size,
                        flash_memory.data() + data_section_flash_offset);
}
```

---

## 常見問題

### Q1: 為什麼 Total Flash reads 是 2048？

因為 Boot ROM 複製 8KB = 8192 bytes = 2048 個 32-bit 字組。

### Q2: 為什麼 mailbox (CSR) 顯示 0，但 ext_mailbox 有值？

- `mailbox`：從 CSR 區域（0x30000）讀取，程式沒有寫這裡
- `ext_mailbox`：從 AXI Master 寫入攔截，程式寫到 0x20000000

Fibonacci 程式寫入的是外部地址 0x20000000，所以結果在 `ext_mailbox` 中。

### Q3: 如何增加 ITCM 大小？

修改 `examples/BUILD.bazel`：
```python
coralnpu_v2_binary(
    name = "coralnpu_v2_your_program",
    srcs = ["your_program.cc"],
    itcm_size_kbytes = 64,  # 預設是 8KB
)
```

---

## 相關檔案

| 檔案 | 說明 |
|------|------|
| `hw_sim/coralnpu_bootrom_runner.cc` | Boot ROM runner 主程式 |
| `sw/bootrom/boot_default.S` | Boot ROM 組合語言原始碼 |
| `sw/bootrom/boot_default.bin` | Boot ROM 二進位檔 |
| `hdl/chisel/src/coralnpu/CoreAxi.scala` | 核心 AXI 包裝器 |
| `hdl/chisel/src/coralnpu/scalar/Lsu.scala` | 載入/儲存單元 |
| `hdl/chisel/src/coralnpu/scalar/UncachedFetch.scala` | 指令擷取單元 |

---

## 修改歷程

為了讓 Boot ROM 流程正常運作，進行了以下修改：

1. **UncachedFetch.scala**：PC 初始值改用 CSR 而非編譯時常數
2. **CoreAxi.scala**：新增 DBus 寫入 ITCM 的路徑
3. **Lsu.scala**：ITCM 儲存改走 DBus，並移除相關錯誤觸發
4. **coralnpu_bootrom_runner.cc**：實作 Flash 模擬和 .data 預載
