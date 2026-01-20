// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VVgaStandaloneWrapper__Syms.h"


VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_init_sub__TOP__0(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+85,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+86,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+87,0,"io_mmio_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+88,0,"io_mmio_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+89,0,"io_mmio_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+90,0,"io_mmio_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+91,0,"io_pixClock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"io_hsync",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+93,0,"io_vsync",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+94,0,"io_rgb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+95,0,"io_activevideo",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+96,0,"io_x_pos",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+97,0,"io_y_pos",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBit(c+98,0,"io_intr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("VgaStandaloneWrapper", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+85,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+86,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+87,0,"io_mmio_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+88,0,"io_mmio_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+89,0,"io_mmio_wen",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+90,0,"io_mmio_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+91,0,"io_pixClock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"io_hsync",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+93,0,"io_vsync",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+94,0,"io_rgb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+95,0,"io_activevideo",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+96,0,"io_x_pos",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+97,0,"io_y_pos",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBit(c+98,0,"io_intr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("vga", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+85,0,"clock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+86,0,"reset",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+87,0,"io_mmio_address",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+88,0,"io_mmio_write_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+89,0,"io_mmio_write_enable",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+90,0,"io_mmio_read_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+91,0,"io_pixClock",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"io_hsync",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+93,0,"io_vsync",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+94,0,"io_rrggbb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+95,0,"io_activevideo",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+98,0,"io_intr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+96,0,"io_x_pos",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+97,0,"io_y_pos",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+67,0,"ctrlReg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+2,0,"intrStatusReg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+3,0,"uploadAddrReg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+68,0,"paletteReg_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+69,0,"paletteReg_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+70,0,"paletteReg_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+71,0,"paletteReg_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+72,0,"paletteReg_4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+73,0,"paletteReg_5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+74,0,"paletteReg_6",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+75,0,"paletteReg_7",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+76,0,"paletteReg_8",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+77,0,"paletteReg_9",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+78,0,"paletteReg_10",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+79,0,"paletteReg_11",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+80,0,"paletteReg_12",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+81,0,"paletteReg_13",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+82,0,"paletteReg_14",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+83,0,"paletteReg_15",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+99,0,"addr_ctrl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+100,0,"addr_intr_status",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+101,0,"addr_upload_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+102,0,"addr_stream_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+4,0,"vblank_sync1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+5,0,"vblank_synced",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+6,0,"curr_frame_sync1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+7,0,"curr_frame_synced",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+8,0,"vblank_prev",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+9,0,"h_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+10,0,"v_count",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBit(c+11,0,"hsync_d1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"vsync_d1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+13,0,"io_hsync_REG",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"io_vsync_REG",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"x_px",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+16,0,"y_px",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+17,0,"frame_x_mult",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 23,0);
    tracep->declBus(c+18,0,"frame_y_mult",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 23,0);
    tracep->declBus(c+19,0,"curr_frame_sync1_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+20,0,"curr_frame",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBit(c+21,0,"display_enabled_sync1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+22,0,"display_enabled",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+23,0,"blanking_sync1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+24,0,"blanking",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+25,0,"palette_sync1_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+26,0,"palette_sync1_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+27,0,"palette_sync1_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+28,0,"palette_sync1_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+29,0,"palette_sync1_4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+30,0,"palette_sync1_5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+31,0,"palette_sync1_6",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+32,0,"palette_sync1_7",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+33,0,"palette_sync1_8",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+34,0,"palette_sync1_9",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+35,0,"palette_sync1_10",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+36,0,"palette_sync1_11",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+37,0,"palette_sync1_12",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+38,0,"palette_sync1_13",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+39,0,"palette_sync1_14",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+40,0,"palette_sync1_15",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+41,0,"palette_sync_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+42,0,"palette_sync_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+43,0,"palette_sync_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+44,0,"palette_sync_3",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+45,0,"palette_sync_4",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+46,0,"palette_sync_5",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+47,0,"palette_sync_6",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+48,0,"palette_sync_7",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+49,0,"palette_sync_8",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+50,0,"palette_sync_9",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+51,0,"palette_sync_10",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+52,0,"palette_sync_11",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+53,0,"palette_sync_12",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+54,0,"palette_sync_13",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+55,0,"palette_sync_14",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+56,0,"palette_sync_15",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+57,0,"in_display_d1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"h_active_d1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+59,0,"v_active_d1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+60,0,"h_active_d2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+61,0,"v_active_d2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+62,0,"pixel_in_word_d1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+95,0,"io_activevideo_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+63,0,"x_px_d1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+64,0,"y_px_d1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->pushPrefix("framebuffer", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+106,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+107,0,"ADDR_WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+85,0,"clka",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+103,0,"wea",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+104,0,"addra",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 12,0);
    tracep->declBus(c+105,0,"dina",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+91,0,"clkb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+65,0,"addrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 12,0);
    tracep->declBus(c+66,0,"doutb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+1,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INTEGER, false,-1, 31,0);
    tracep->popPrefix();
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+84,0,"addr_palette",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_init_top(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_init_top\n"); );
    // Body
    VVgaStandaloneWrapper___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VVgaStandaloneWrapper___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VVgaStandaloneWrapper___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_register(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_register\n"); );
    // Body
    tracep->addConstCb(&VVgaStandaloneWrapper___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&VVgaStandaloneWrapper___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&VVgaStandaloneWrapper___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&VVgaStandaloneWrapper___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_const_0_sub_0(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_const_0\n"); );
    // Init
    VVgaStandaloneWrapper___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VVgaStandaloneWrapper___024root*>(voidSelf);
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    VVgaStandaloneWrapper___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_const_0_sub_0(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_const_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+106,(0x1800U),32);
    bufp->fullIData(oldp+107,(0xdU),32);
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_full_0_sub_0(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_full_0\n"); );
    // Init
    VVgaStandaloneWrapper___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VVgaStandaloneWrapper___024root*>(voidSelf);
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    VVgaStandaloneWrapper___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_full_0_sub_0(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_full_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+1,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i),32);
    bufp->fullIData(oldp+2,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg),32);
    bufp->fullIData(oldp+3,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg),32);
    bufp->fullBit(oldp+4,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_sync1));
    bufp->fullBit(oldp+5,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_synced));
    bufp->fullCData(oldp+6,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1),4);
    bufp->fullCData(oldp+7,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_synced),4);
    bufp->fullBit(oldp+8,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_prev));
    bufp->fullSData(oldp+9,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count),10);
    bufp->fullSData(oldp+10,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count),10);
    bufp->fullBit(oldp+11,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__hsync_d1));
    bufp->fullBit(oldp+12,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vsync_d1));
    bufp->fullBit(oldp+13,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_hsync_REG));
    bufp->fullBit(oldp+14,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_vsync_REG));
    bufp->fullSData(oldp+15,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px),10);
    bufp->fullSData(oldp+16,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px),10);
    bufp->fullIData(oldp+17,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_x_mult),24);
    bufp->fullIData(oldp+18,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_y_mult),24);
    bufp->fullCData(oldp+19,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1_1),4);
    bufp->fullCData(oldp+20,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame),4);
    bufp->fullBit(oldp+21,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled_sync1));
    bufp->fullBit(oldp+22,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled));
    bufp->fullBit(oldp+23,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking_sync1));
    bufp->fullBit(oldp+24,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking));
    bufp->fullCData(oldp+25,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_0),6);
    bufp->fullCData(oldp+26,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_1),6);
    bufp->fullCData(oldp+27,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_2),6);
    bufp->fullCData(oldp+28,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_3),6);
    bufp->fullCData(oldp+29,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_4),6);
    bufp->fullCData(oldp+30,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_5),6);
    bufp->fullCData(oldp+31,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_6),6);
    bufp->fullCData(oldp+32,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_7),6);
    bufp->fullCData(oldp+33,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_8),6);
    bufp->fullCData(oldp+34,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_9),6);
    bufp->fullCData(oldp+35,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_10),6);
    bufp->fullCData(oldp+36,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_11),6);
    bufp->fullCData(oldp+37,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_12),6);
    bufp->fullCData(oldp+38,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_13),6);
    bufp->fullCData(oldp+39,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_14),6);
    bufp->fullCData(oldp+40,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_15),6);
    bufp->fullCData(oldp+41,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_0),6);
    bufp->fullCData(oldp+42,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_1),6);
    bufp->fullCData(oldp+43,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_2),6);
    bufp->fullCData(oldp+44,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_3),6);
    bufp->fullCData(oldp+45,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_4),6);
    bufp->fullCData(oldp+46,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_5),6);
    bufp->fullCData(oldp+47,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_6),6);
    bufp->fullCData(oldp+48,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_7),6);
    bufp->fullCData(oldp+49,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_8),6);
    bufp->fullCData(oldp+50,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_9),6);
    bufp->fullCData(oldp+51,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_10),6);
    bufp->fullCData(oldp+52,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_11),6);
    bufp->fullCData(oldp+53,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_12),6);
    bufp->fullCData(oldp+54,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_13),6);
    bufp->fullCData(oldp+55,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_14),6);
    bufp->fullCData(oldp+56,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_15),6);
    bufp->fullBit(oldp+57,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__in_display_d1));
    bufp->fullBit(oldp+58,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d1));
    bufp->fullBit(oldp+59,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d1));
    bufp->fullBit(oldp+60,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d2));
    bufp->fullBit(oldp+61,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d2));
    bufp->fullCData(oldp+62,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__pixel_in_word_d1),3);
    bufp->fullSData(oldp+63,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px_d1),10);
    bufp->fullSData(oldp+64,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px_d1),10);
    bufp->fullSData(oldp+65,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addrb),13);
    bufp->fullIData(oldp+66,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___framebuffer_doutb),32);
    bufp->fullIData(oldp+67,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg),32);
    bufp->fullCData(oldp+68,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_0),6);
    bufp->fullCData(oldp+69,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_1),6);
    bufp->fullCData(oldp+70,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_2),6);
    bufp->fullCData(oldp+71,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_3),6);
    bufp->fullCData(oldp+72,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_4),6);
    bufp->fullCData(oldp+73,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_5),6);
    bufp->fullCData(oldp+74,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_6),6);
    bufp->fullCData(oldp+75,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_7),6);
    bufp->fullCData(oldp+76,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_8),6);
    bufp->fullCData(oldp+77,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_9),6);
    bufp->fullCData(oldp+78,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_10),6);
    bufp->fullCData(oldp+79,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_11),6);
    bufp->fullCData(oldp+80,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_12),6);
    bufp->fullCData(oldp+81,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_13),6);
    bufp->fullCData(oldp+82,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_14),6);
    bufp->fullCData(oldp+83,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_15),6);
    bufp->fullBit(oldp+84,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette));
    bufp->fullBit(oldp+85,(vlSelf->clock));
    bufp->fullBit(oldp+86,(vlSelf->reset));
    bufp->fullIData(oldp+87,(vlSelf->io_mmio_addr),32);
    bufp->fullIData(oldp+88,(vlSelf->io_mmio_wdata),32);
    bufp->fullBit(oldp+89,(vlSelf->io_mmio_wen));
    bufp->fullIData(oldp+90,(vlSelf->io_mmio_rdata),32);
    bufp->fullBit(oldp+91,(vlSelf->io_pixClock));
    bufp->fullBit(oldp+92,(vlSelf->io_hsync));
    bufp->fullBit(oldp+93,(vlSelf->io_vsync));
    bufp->fullCData(oldp+94,(vlSelf->io_rgb),6);
    bufp->fullBit(oldp+95,(vlSelf->io_activevideo));
    bufp->fullSData(oldp+96,(vlSelf->io_x_pos),10);
    bufp->fullSData(oldp+97,(vlSelf->io_y_pos),10);
    bufp->fullBit(oldp+98,(vlSelf->io_intr));
    bufp->fullBit(oldp+99,((4U == (0xffU & vlSelf->io_mmio_addr))));
    bufp->fullBit(oldp+100,((0xcU == (0xffU & vlSelf->io_mmio_addr))));
    bufp->fullBit(oldp+101,((0x10U == (0xffU & vlSelf->io_mmio_addr))));
    bufp->fullBit(oldp+102,((0x14U == (0xffU & vlSelf->io_mmio_addr))));
    bufp->fullBit(oldp+103,(((IData)(vlSelf->io_mmio_wen) 
                             & ((~ (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN)) 
                                & (0x14U == (0xffU 
                                             & vlSelf->io_mmio_addr))))));
    bufp->fullSData(oldp+104,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addra),13);
    bufp->fullIData(oldp+105,(((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN_0)
                                ? 0U : vlSelf->io_mmio_wdata)),32);
}
