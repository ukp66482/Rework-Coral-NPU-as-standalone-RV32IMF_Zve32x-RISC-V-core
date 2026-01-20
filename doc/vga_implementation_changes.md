# VGA Nyancat 動畫實作變更紀錄

本文件記錄了為 CoralNPU Standalone 實作 VGA Nyancat 動畫顯示功能所做的所有修改。

---

## 🎓 VGA 基礎知識（給初學者）

在深入實作細節之前，讓我們先了解 VGA 是如何工作的。

### 什麼是 VGA？

**VGA (Video Graphics Array)** 是一種類比視訊顯示標準，發明於 1987 年。雖然現在大多數顯示器使用數位介面（如 HDMI、DisplayPort），但 VGA 的時序原理仍然是理解所有視訊顯示的基礎。

想像一下老式的 CRT 電視：有一個電子槍從左到右、從上到下逐行掃描螢幕。VGA 就是控制這個掃描過程的標準。

### VGA 信號組成

VGA 介面主要包含 5 個信號：

```
┌─────────────────────────────────────────────────────────┐
│  VGA 信號                                                │
├─────────────────────────────────────────────────────────┤
│  🔴 R (Red)      - 紅色分量 (類比電壓 0~0.7V)            │
│  🟢 G (Green)    - 綠色分量 (類比電壓 0~0.7V)            │
│  🔵 B (Blue)     - 藍色分量 (類比電壓 0~0.7V)            │
│  ↔️ HSYNC        - 水平同步信號 (每掃描一行脈衝一次)      │
│  ↕️ VSYNC        - 垂直同步信號 (每掃描一幀脈衝一次)      │
└─────────────────────────────────────────────────────────┘
```

### VGA 時序原理

#### 掃描一行的過程

顯示器逐行繪製畫面。每一行的時序分為 4 個階段：

```
                    一行的時間 (H_TOTAL = 832 像素時鐘)
    ◄──────────────────────────────────────────────────────────►
    
    ┌──────────────┬────┬──────┬────┐
    │   可見區域    │ 前 │ 同步 │ 後 │
    │  (H_ACTIVE)  │ 廊 │脈衝  │ 廊 │
    │    640 px    │16px│ 64px │112px│
    └──────────────┴────┴──────┴────┘
         顯示像素     ←─ 消隱期間 ─→
                    (電子槍返回起點)
```

1. **Active (可見區域)**: 640 像素 - 實際顯示內容
2. **Front Porch (前廊)**: 16 像素 - 可見區結束到同步脈衝的間隔
3. **Sync Pulse (同步脈衝)**: 64 像素 - HSYNC 信號拉低，告訴顯示器「這行結束了」
4. **Back Porch (後廊)**: 112 像素 - 同步結束到下一行開始的間隔

#### 掃描一幀的過程

同樣的邏輯也適用於垂直方向：

```
         一幀的時間 (V_TOTAL = 520 行)
    ◄───────────────────────────────────────►
    
    ┌──────────────────────────────────────┐ ─┐
    │                                      │  │
    │          可見區域 (V_ACTIVE)          │  │ 480 行
    │              480 行                  │  │
    │                                      │  │
    ├──────────────────────────────────────┤ ─┤
    │ 前廊 (9行) │ 同步脈衝 (3行) │ 後廊 (28行) │  │ 40 行
    └──────────────────────────────────────┘ ─┘
                   消隱期間
               (電子槍返回左上角)
```

#### 計算刷新率

```
像素時鐘 = 31.5 MHz (每秒 31,500,000 個像素)
每行像素 = 832 (包含消隱)
每幀行數 = 520 (包含消隱)

刷新率 = 31,500,000 ÷ (832 × 520) = 72.8 Hz ≈ 72Hz
```

這就是為什麼我們的規格是 **640×480 @ 72Hz**！

### Framebuffer：記憶體中的畫面

**Framebuffer** 是一塊專門用來儲存畫面資料的記憶體。CPU 把想顯示的圖像寫入 framebuffer，VGA 控制器則不斷地讀取它來產生視訊信號。

```
    ┌─────────────────┐         ┌─────────────────┐
    │                 │  寫入   │                 │
    │      CPU        │ ──────► │   Framebuffer   │
    │                 │         │    (記憶體)      │
    └─────────────────┘         └────────┬────────┘
                                         │ 讀取
                                         ▼
                                ┌─────────────────┐
                                │   VGA 控制器    │
                                │   (產生時序)     │
                                └────────┬────────┘
                                         │
                                         ▼
                                    🖥️ 顯示器
```

#### 我們的 Framebuffer 設計

由於完整的 640×480 畫面需要大量記憶體，我們採用**縮小 + 放大**的策略：

```
實際儲存：64×64 像素的小圖
    ┌────────┐
    │ 64×64  │  ← 只需要 4096 像素
    │ pixels │
    └────────┘
        │
        │ 6× 縮放
        ▼
顯示輸出：384×384 像素 (置中於 640×480)
    ┌────────────────────────────────────┐
    │          128px 左邊距               │
    │    ┌────────────────────────┐      │
    │    │                        │      │
    │ 48 │      384×384           │      │ 640×480
    │ px │      顯示區域           │      │ 螢幕
    │    │                        │      │
    │    └────────────────────────┘      │
    │                                    │
    └────────────────────────────────────┘
```

記憶體需求：
- 完整 640×480：307,200 像素 😱
- 我們的 64×64：4,096 像素 ✅ (節省 75 倍！)

### 調色板 (Palette)：用索引代替顏色

直接儲存每個像素的 RGB 顏色需要很多位元。我們使用**調色板**技術：

```
像素資料只儲存索引 (4-bit = 16 種可能)：
    ┌───┬───┬───┬───┬───┬───┬───┬───┐
    │ 0 │ 5 │ 5 │ 1 │ 1 │ 8 │ 8 │ 2 │  ← 每像素只需 4 bits
    └───┴───┴───┴───┴───┴───┴───┴───┘
          │
          │ 查表
          ▼
    ┌─────────────────────────────────┐
    │ 調色板 (16 個顏色)               │
    │ 0: 深藍  1: 白色  2: 黑色       │
    │ 3: 淺粉  4: 粉紅  5: 亮粉       │
    │ 6: 紅色  7: 橙色  8: 黃色       │
    │ 9: 綠色 10: 淺藍 11: 紫色       │
    │ ...                             │
    └─────────────────────────────────┘
          │
          ▼
    實際顯示的 RGB 顏色
```

這樣我們用 4 bits 就能表示 16 種顏色，比直接用 24-bit RGB 省了 6 倍！

### 動畫原理：多個 Frame

Nyancat 動畫有 12 幀。我們把 12 幀全部儲存在 framebuffer 中：

```
Framebuffer 記憶體配置 (6144 words total)：

    ┌──────────────┐ ← 0 words
    │   Frame 0    │
    │  (512 words) │
    ├──────────────┤ ← 512 words
    │   Frame 1    │
    │  (512 words) │
    ├──────────────┤ ← 1024 words
    │   Frame 2    │
    │     ...      │
    ├──────────────┤
    │     ...      │
    ├──────────────┤ ← 5632 words
    │   Frame 11   │
    │  (512 words) │
    └──────────────┘ ← 6144 words
```

動畫播放：透過 CTRL 暫存器的 `frame_select` 位元選擇要顯示的幀：

```c
// 每隔一段時間切換到下一幀
frame = (frame + 1) % 12;  // 0 → 1 → 2 → ... → 11 → 0 → ...
CTRL = (frame << 4) | 1;   // 寫入 frame_select 並啟用顯示
```

### 雙時鐘域設計

VGA 控制器有個特殊挑戰：CPU 和 VGA 使用不同的時鐘！

```
    ┌─────────────────┐              ┌─────────────────┐
    │   CPU 時鐘域     │              │  像素時鐘域      │
    │   (系統時鐘)     │              │  (31.5 MHz)     │
    ├─────────────────┤              ├─────────────────┤
    │ • MMIO 讀寫     │              │ • VGA 時序產生   │
    │ • 調色板設定     │    CDC       │ • Framebuffer  │
    │ • 控制暫存器     │◄────────────►│   讀取          │
    │ • Framebuffer  │  (跨時鐘域    │ • RGB 輸出      │
    │   寫入         │   同步器)     │                 │
    └─────────────────┘              └─────────────────┘
```

**CDC (Clock Domain Crossing)** 是處理兩個時鐘域之間資料傳遞的技術。我們使用雙觸發器 (2-FF synchronizer) 來避免亞穩態問題。

### 完整資料流程

從 CPU 到顯示器的完整流程：

```
    1️⃣ CPU 初始化
    ┌──────────────────────────────────────────────────────────┐
    │ • 寫入調色板 (16 種顏色)                                   │
    │ • 上傳 12 幀圖像資料到 framebuffer                        │
    │ • 設定 CTRL 暫存器啟用顯示                                │
    └──────────────────────────────────────────────────────────┘
                                │
                                ▼
    2️⃣ VGA 控制器持續運作
    ┌──────────────────────────────────────────────────────────┐
    │ for each pixel (x, y):                                   │
    │   1. 根據螢幕座標計算 framebuffer 位址                     │
    │   2. 從 framebuffer 讀取 4-bit 調色板索引                 │
    │   3. 用索引查調色板得到 6-bit RGB                         │
    │   4. 輸出 RGB + 同步信號                                  │
    └──────────────────────────────────────────────────────────┘
                                │
                                ▼
    3️⃣ 動畫播放
    ┌──────────────────────────────────────────────────────────┐
    │ 定時器每 ~83ms 觸發一次 (12 FPS):                         │
    │   frame = (frame + 1) % 12                               │
    │   更新 CTRL 暫存器的 frame_select                         │
    └──────────────────────────────────────────────────────────┘
```

現在你已經了解 VGA 的工作原理了！接下來讓我們看看具體的實作細節。

---

## 🧩 VgaStandaloneWrapper 是什麼？

### 為什麼需要 Wrapper？

在硬體設計中，我們通常會把功能模組包裝成更容易測試的形式。`VgaStandaloneWrapper` 就是這樣一個包裝器：

```
    實際的 VGA 模組（VGA.scala）
    ┌─────────────────────────────────────────────────────────┐
    │                                                         │
    │   VGA 模組使用複雜的 MMIO 介面：                          │
    │   • PeripheralInterface (包含 address, write_data,     │
    │     write_enable, read_data 等信號)                     │
    │   • 這個介面是為了跟整個 SoC 匯流排整合設計的              │
    │                                                         │
    └─────────────────────────────────────────────────────────┘
                            │
                            │ 包裝
                            ▼
    VgaStandaloneWrapper（測試用包裝器）
    ┌─────────────────────────────────────────────────────────┐
    │                                                         │
    │   簡化的獨立介面：                                        │
    │   • mmio_addr, mmio_wdata, mmio_wen, mmio_rdata        │
    │   • hsync, vsync, rgb, activevideo, x_pos, y_pos       │
    │   • pixClock, intr                                      │
    │                                                         │
    │   → 可以直接用 Verilator 模擬，不需要整個 SoC！           │
    │                                                         │
    └─────────────────────────────────────────────────────────┘
```

### VgaStandaloneWrapper 的 IO 介面

```scala
class VgaStandaloneWrapper extends Module {
  val io = IO(new Bundle {
    // MMIO 介面 (CPU 用來控制 VGA)
    val mmio_addr  = Input(UInt(32.W))   // 暫存器位址
    val mmio_wdata = Input(UInt(32.W))   // 寫入資料
    val mmio_wen   = Input(Bool())       // 寫入致能
    val mmio_rdata = Output(UInt(32.W))  // 讀取資料
    
    // VGA 輸出信號 (送到顯示器)
    val pixClock    = Input(Clock())     // 像素時鐘 (31.5 MHz)
    val hsync       = Output(Bool())     // 水平同步
    val vsync       = Output(Bool())     // 垂直同步
    val rgb         = Output(UInt(6.W))  // 6-bit 顏色 (RRGGBB)
    val activevideo = Output(Bool())     // 目前是否在可見區域
    val x_pos       = Output(UInt(10.W)) // 目前 X 座標 (0-639)
    val y_pos       = Output(UInt(10.W)) // 目前 Y 座標 (0-479)
    val intr        = Output(Bool())     // 中斷信號 (vblank)
  })
}
```

### 為什麼這樣設計很重要？

```
    ❌ 沒有 Wrapper 的情況：
    ┌─────────────────────────────────────────────────────────┐
    │   要測試 VGA，必須：                                      │
    │   1. 建構整個 CPU                                        │
    │   2. 建構整個記憶體系統                                    │
    │   3. 建構整個匯流排                                       │
    │   4. 寫 RISC-V 程式來控制 VGA                            │
    │   5. 編譯、載入、執行...                                  │
    │                                                         │
    │   → 非常慢，debug 困難 😫                                │
    └─────────────────────────────────────────────────────────┘

    ✅ 有 Wrapper 的情況：
    ┌─────────────────────────────────────────────────────────┐
    │   要測試 VGA，只需要：                                    │
    │   1. 實例化 VgaStandaloneWrapper                        │
    │   2. 直接驅動 MMIO 信號                                   │
    │   3. 觀察 VGA 輸出                                       │
    │                                                         │
    │   → 快速、直接、容易 debug 🎉                             │
    └─────────────────────────────────────────────────────────┘
```

---

## 💾 記憶體規劃與 ITCM 擴增

### CoralNPU 記憶體架構

CoralNPU 使用典型的嵌入式處理器記憶體架構：

```
    記憶體映射 (Memory Map)
    ┌─────────────────────────────────────────┐ 0x00000000
    │                                         │
    │              ITCM                       │
    │     (Instruction Tightly-Coupled       │
    │              Memory)                    │
    │                                         │
    │   存放：程式碼 + 唯讀資料 (const)         │
    │                                         │
    ├─────────────────────────────────────────┤ 0x00010000 (64KB)
    │                                         │
    │              DTCM                       │
    │      (Data Tightly-Coupled Memory)     │
    │                                         │
    │   存放：變數、堆疊、heap                  │
    │                                         │
    ├─────────────────────────────────────────┤
    │              ...                        │
    ├─────────────────────────────────────────┤ 0x50000000
    │         VGA 暫存器區域                   │
    │   (MMIO - Memory Mapped I/O)           │
    └─────────────────────────────────────────┘
```

### 什麼是 TCM？

**TCM (Tightly-Coupled Memory)** 是直接連接到 CPU 的高速記憶體，沒有 cache 的延遲：

```
    ┌─────────┐     直接連接      ┌─────────┐
    │   CPU   │◄────────────────►│   TCM   │
    │         │   (1 cycle 存取)  │ (SRAM)  │
    └─────────┘                   └─────────┘
         │
         │  經過快取/匯流排
         ▼
    ┌─────────────────────────────────────────┐
    │            主記憶體 (DDR/外部 RAM)        │
    │         (多 cycle 存取，有延遲)          │
    └─────────────────────────────────────────┘
```

- **ITCM**: 存放指令（程式碼），CPU 從這裡取指令
- **DTCM**: 存放資料（變數），CPU 讀寫資料

### 為什麼 ITCM 要擴增到 64KB？

讓我們計算 Nyancat 程式需要多少記憶體：

```
    Nyancat 程式記憶體需求
    ┌─────────────────────────────────────────────────────────┐
    │                                                         │
    │   1. 程式碼 (code)                                       │
    │      • 主程式、函式庫等                                   │
    │      • 估計：~4-8 KB                                    │
    │                                                         │
    │   2. Nyancat 動畫資料 (nyancat-frames.h)                │
    │      • 12 幀 × 512 words × 4 bytes = 24,576 bytes      │
    │      • = 24 KB  ← 這是大頭！                            │
    │                                                         │
    │   3. 其他常數資料                                        │
    │      • 調色板、字串等                                    │
    │      • 估計：~1-2 KB                                    │
    │                                                         │
    ├─────────────────────────────────────────────────────────┤
    │   總計：約 30-35 KB                                      │
    └─────────────────────────────────────────────────────────┘
```

#### 問題：預設 ITCM 只有 16KB！

```
    ❌ 預設 ITCM = 16 KB
    ┌────────────────┐
    │    16 KB       │  ← 放不下 30+ KB 的程式！
    │                │
    └────────────────┘
    
    編譯錯誤：
    "section '.rodata' will not fit in region 'itcm'"
```

#### 解決方案：擴增到 64KB

```
    ✅ 擴增後 ITCM = 64 KB
    ┌────────────────────────────────────────────────────────┐
    │                                                        │
    │    程式碼 (~8 KB)                                       │
    │    ──────────────                                      │
    │    Nyancat 資料 (24 KB)                                │
    │    ──────────────────────────────                      │
    │    其他常數 (~2 KB)                                     │
    │    ─────────────                                       │
    │                                                        │
    │    剩餘空間 (~30 KB)  ← 還有很多餘裕                     │
    │                                                        │
    └────────────────────────────────────────────────────────┘
```

#### 在 BUILD.bazel 中的設定

```python
# examples/BUILD.bazel
coralnpu_cc_binary(
    name = "coralnpu_v2_nyancat_vga",
    srcs = ["nyancat_vga.cc"],
    hdrs = ["nyancat-frames.h"],      # 24KB 的 frame 資料
    itcm_size_kbytes = 64,            # 擴增到 64KB！
    ...
)
```

### 為什麼 frame 資料放在 ITCM？

因為 `nyancat_frames` 是 `static const` 陣列：

```cpp
// nyancat-frames.h
static const uint32_t nyancat_frames[12][512] = { ... };
//       ^^^^^
//       const 資料會放在 .rodata section
//       .rodata 預設放在 ITCM（因為是唯讀的）
```

```
    記憶體 section 分配
    ┌─────────────────────────────────────────┐
    │              ITCM                       │
    │  ┌─────────────────────────────────┐   │
    │  │ .text (程式碼)                   │   │
    │  ├─────────────────────────────────┤   │
    │  │ .rodata (唯讀資料)               │   │ ← nyancat_frames 在這裡
    │  │   • nyancat_frames (24 KB)      │   │
    │  │   • 調色板資料                   │   │
    │  └─────────────────────────────────┘   │
    └─────────────────────────────────────────┘
    
    ┌─────────────────────────────────────────┐
    │              DTCM                       │
    │  ┌─────────────────────────────────┐   │
    │  │ .data (可讀寫變數)               │   │
    │  ├─────────────────────────────────┤   │
    │  │ .bss (未初始化變數)              │   │
    │  ├─────────────────────────────────┤   │
    │  │ stack (堆疊)                    │   │
    │  └─────────────────────────────────┘   │
    └─────────────────────────────────────────┘
```

---

## 目錄

1. [概述](#概述)
2. [VGA 硬體規格](#vga-硬體規格)
3. [檔案變更清單](#檔案變更清單)
4. [詳細變更說明](#詳細變更說明)
5. [如何運行演示](#如何運行演示)
6. [問題排除](#問題排除)

---

## 概述

### 目標
將 ca2025-mycpu 專案中的 VGA Nyancat 動畫功能移植到 CoralNPU Standalone，使用 Verilator + SDL2 進行硬體模擬和視覺化顯示。

### 技術方案
採用與 ca2025-mycpu 相同的方法：
1. 用 Verilator 模擬 VGA 硬體
2. 直接從硬體讀取 VGA 信號（hsync, vsync, rgb, x_pos, y_pos）
3. 使用 SDL2 渲染到視窗

---

## VGA 硬體規格

| 參數 | 數值 |
|------|------|
| 解析度 | 640×480 @ 72Hz |
| Framebuffer 大小 | 64×64 像素 |
| 縮放倍率 | 6× (顯示為 384×384) |
| 色彩深度 | 4-bit 調色板索引 (16 色) |
| 動畫幀數 | 12 幀 |
| 每幀資料量 | 512 words (4096 像素 / 8 像素每 word) |

### 暫存器映射

| 偏移量 | 名稱 | 說明 |
|--------|------|------|
| 0x00 | ID | 識別碼 (0x56474131 = "VGA1") |
| 0x04 | CTRL | 控制暫存器：[7:4]=frame_select, [0]=enable |
| 0x08 | STATUS | 狀態暫存器 |
| 0x10 | UPLOAD_ADDR | 上傳位址：[19:16]=frame, [15:0]=pixel_offset |
| 0x14 | STREAM_DATA | 串流資料寫入 (自動遞增) |
| 0x20-0x5F | PALETTE | 16 個調色板條目 (6-bit RRGGBB) |


---

## 檔案變更清單

### 新增檔案

| 檔案路徑 | 說明 |
|----------|------|
| `tests/cocotb/vga/verilator/vga_sim.cc` | Verilator VGA 模擬器主程式 |
| `tests/cocotb/vga/verilator/Makefile` | 構建自動化腳本 |
| `tests/cocotb/vga/verilator/README.md` | 使用說明文件 |

### 修改檔案

| 檔案路徑 | 修改內容 |
|----------|----------|
| `hdl/chisel/src/peripherals/BUILD` | 新增 VGA.sv 生成規則 |
| `hdl/chisel/src/peripherals/VGA.scala` | 新增 EmitVGA object |
| `hdl/chisel/src/peripherals/VgaStandaloneWrapper.scala` | 新增 io.intr 輸出 |
| `rules/coco_tb.bzl` | 新增 verilog_deps 支援 |
| `tests/cocotb/vga/BUILD` | 新增 verilog_deps 依賴 |
| `examples/BUILD.bazel` | 增加 ITCM 大小到 64KB |

---

## 詳細變更說明

### 1. VGA 測試基礎設施修復

#### 問題
cocotb 測試無法找到 VGA.sv 和 TrueDualPortRAM32.v 依賴。

#### 解決方案

**rules/coco_tb.bzl** - 新增 `verilog_deps` 屬性支援：

```python
# 新增屬性
"verilog_deps": attr.label_list(allow_files = True, default = []),

# 在實作中收集依賴
for dep in ctx.files.verilog_deps:
    all_verilog_sources.append("$PWD/" + dep.path)
    all_verilog_deps.append(dep)
```

**hdl/chisel/src/peripherals/BUILD** - 新增 VGA.sv 生成規則：

```python
genrule(
    name = "VGA_sv_gen",
    outs = ["VGA.sv"],
    cmd = "... ./$(location :vga_emit_binary) --target-dir=$(RULEDIR)",
    tools = [":vga_emit_binary", ...],
)

chisel_binary(
    name = "vga_emit_binary",
    main_class = "peripheral.EmitVGA",
    deps = [":vga"],
)
```

**hdl/chisel/src/peripherals/VGA.scala** - 新增 EmitVGA object：

```scala
object EmitVGA extends App {
  ChiselStage.emitSystemVerilogFile(new VGA(), ...)
}
```

### 2. VgaStandaloneWrapper 修復

#### 問題
VgaStandaloneWrapper 缺少 `io_intr` 輸出，導致 Verilator 構建失敗。

#### 解決方案

**hdl/chisel/src/peripherals/VgaStandaloneWrapper.scala**：

```scala
class VgaStandaloneWrapperIO extends Bundle {
  // ... 其他 IO
  val intr = Output(Bool())  // 新增
}

// 連接中斷信號
io.intr := vga.io.intr
```

### 3. Verilator SDL2 模擬器

#### 設計原理
直接從 Verilator 模型讀取 VGA 硬體信號，使用 SDL2 渲染視窗。這與 ca2025-mycpu 的 `sim.cpp` 方法相同。

**tests/cocotb/vga/verilator/vga_sim.cc** 主要功能：

```cpp
class VGASimulator {
    // 驅動 VgaStandaloneWrapper 硬體
    void tick();
    void writeMMIO(uint32_t addr, uint32_t data);
    uint32_t readMMIO(uint32_t addr);
    
    // VGA 信號存取器
    bool vsync() const { return top_->io_vsync; }
    uint8_t rgb() const { return top_->io_rgb; }
    uint16_t x_pos() const { return top_->io_x_pos; }
    uint16_t y_pos() const { return top_->io_y_pos; }
};

class VGADisplay {
    // SDL2 渲染
    void update_pixel(uint8_t rrggbb, uint8_t activevideo, 
                      uint16_t x_pos, uint16_t y_pos);
    void render();
};
```

#### 動畫邏輯

```cpp
// 每 6 個 vsync 切換一次動畫幀 (~72Hz/6 ≈ 12 FPS)
if (!vsync && prev_vsync) {
    display.render();
    vsync_count++;
    if (vsync_count % 6 == 0) {
        current_frame = (current_frame + 1) % 12;
        sim.selectFrame(current_frame);
    }
}
```

### 4. Frame Select 位元修正

#### 問題
原本 vga_sim.cc 使用 CTRL[11:8] 作為 frame_select，但硬體實際使用 CTRL[7:4]。

#### 證據
從 VGA.scala 第 118 行：
```scala
val ctrl_frame_sel = ctrlReg(7, 4)
```

#### 修正

```cpp
void selectFrame(int frame) {
    // 修正前: CTRL[11:8] (錯誤)
    // writeMMIO(VgaRegs::CTRL, ((frame & 0xF) << 8) | 1);
    
    // 修正後: CTRL[7:4] (正確)
    writeMMIO(VgaRegs::CTRL, ((frame & 0xF) << 4) | 1);
}
```

### 5. Nyancat 資料來源

使用 ca2025-mycpu 提供的預打包 frame 資料 `nyancat-frames.h`：
- 12 幀 × 512 words = 6144 words
- 每個 32-bit word 包含 8 個 4-bit 調色板索引

### 6. SDL2 軟體渲染模式

#### 問題
SSH 連接時沒有 GPU 權限，EGL 初始化會報權限錯誤。

#### 解決方案

**tests/cocotb/vga/verilator/Makefile**：

```makefile
run:
    SDL_RENDER_DRIVER=software ./$(BUILD_DIR)/VVgaStandaloneWrapper -time $(SIM_TIME)
```

---

## 如何運行演示

### 前置需求

```bash
# 安裝 SDL2 開發庫
sudo apt install libsdl2-dev

# 安裝 Verilator
sudo apt install verilator
```

### 運行步驟

```bash
cd tests/cocotb/vga/verilator

# 完整流程（生成 Verilog + 構建 + 運行）
make demo

# 或分步執行
make verilog   # 從 Chisel 生成 Verilog
make build     # 構建 Verilator 模擬器
make run       # 運行演示
```

### 調整參數

```bash
# 運行更長時間
make run SIM_TIME=500000000

# 顯示 MMIO 操作
./obj_dir/VVgaStandaloneWrapper -verbose -time 10000000
```

---

## 問題排除

### 1. EGL Permission Denied 警告

```
libEGL warning: failed to open /dev/dri/renderD128: Permission denied
```

**原因**：沒有 GPU 訪問權限

**解決方案**（二選一）：
```bash
# 方法 1：加入 video/render 群組（需重新登入）
sudo usermod -a -G video,render $USER

# 方法 2：使用軟體渲染（Makefile 已自動設定）
SDL_RENDER_DRIVER=software ./obj_dir/VVgaStandaloneWrapper
```

### 2. SSH 遠程連接無法顯示

**原因**：SSH 沒有 X11 轉發

**解決方案**：
```bash
# 使用 X11 轉發連接
ssh -X user@server

# 然後運行
make run
```

### 3. 動畫不動（只顯示靜態圖片）

**可能原因**：
1. Frame select 位元位置錯誤（已修復）
2. 模擬時間太短

**解決方案**：
確保使用最新版本的 vga_sim.cc，並增加模擬時間：
```bash
make run SIM_TIME=200000000
```

---

## 測試驗證

所有測試都通過：

```bash
# Chisel 單元測試 (8 tests)
bazel test //hdl/chisel/src/peripherals:vga_tests

# Cocotb 整合測試 (6 tests)
bazel test //tests/cocotb/vga:vga_cocotb
```

---

## 參考資料

- ca2025-mycpu VGA 實作：`ca2025-mycpu/2-mmio-trap/src/main/scala/peripheral/VGA.scala`
- ca2025-mycpu Verilator 模擬器：`ca2025-mycpu/2-mmio-trap/verilog/verilator/sim.cpp`
- Nyancat frame 資料：`examples/nyancat-frames.h`
