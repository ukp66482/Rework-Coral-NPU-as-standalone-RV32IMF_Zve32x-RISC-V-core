// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VVgaStandaloneWrapper__Syms.h"


void VVgaStandaloneWrapper___024root__trace_chg_0_sub_0(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void VVgaStandaloneWrapper___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_chg_0\n"); );
    // Init
    VVgaStandaloneWrapper___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VVgaStandaloneWrapper___024root*>(voidSelf);
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    VVgaStandaloneWrapper___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void VVgaStandaloneWrapper___024root__trace_chg_0_sub_0(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[0U])) {
        bufp->chgIData(oldp+0,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i),32);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgIData(oldp+1,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg),32);
        bufp->chgIData(oldp+2,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg),32);
        bufp->chgBit(oldp+3,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_sync1));
        bufp->chgBit(oldp+4,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_synced));
        bufp->chgCData(oldp+5,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1),4);
        bufp->chgCData(oldp+6,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_synced),4);
        bufp->chgBit(oldp+7,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_prev));
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgSData(oldp+8,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count),10);
        bufp->chgSData(oldp+9,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count),10);
        bufp->chgBit(oldp+10,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__hsync_d1));
        bufp->chgBit(oldp+11,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vsync_d1));
        bufp->chgBit(oldp+12,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_hsync_REG));
        bufp->chgBit(oldp+13,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_vsync_REG));
        bufp->chgSData(oldp+14,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px),10);
        bufp->chgSData(oldp+15,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px),10);
        bufp->chgIData(oldp+16,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_x_mult),24);
        bufp->chgIData(oldp+17,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_y_mult),24);
        bufp->chgCData(oldp+18,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1_1),4);
        bufp->chgCData(oldp+19,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame),4);
        bufp->chgBit(oldp+20,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled_sync1));
        bufp->chgBit(oldp+21,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled));
        bufp->chgBit(oldp+22,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking_sync1));
        bufp->chgBit(oldp+23,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking));
        bufp->chgCData(oldp+24,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_0),6);
        bufp->chgCData(oldp+25,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_1),6);
        bufp->chgCData(oldp+26,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_2),6);
        bufp->chgCData(oldp+27,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_3),6);
        bufp->chgCData(oldp+28,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_4),6);
        bufp->chgCData(oldp+29,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_5),6);
        bufp->chgCData(oldp+30,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_6),6);
        bufp->chgCData(oldp+31,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_7),6);
        bufp->chgCData(oldp+32,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_8),6);
        bufp->chgCData(oldp+33,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_9),6);
        bufp->chgCData(oldp+34,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_10),6);
        bufp->chgCData(oldp+35,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_11),6);
        bufp->chgCData(oldp+36,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_12),6);
        bufp->chgCData(oldp+37,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_13),6);
        bufp->chgCData(oldp+38,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_14),6);
        bufp->chgCData(oldp+39,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_15),6);
        bufp->chgCData(oldp+40,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_0),6);
        bufp->chgCData(oldp+41,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_1),6);
        bufp->chgCData(oldp+42,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_2),6);
        bufp->chgCData(oldp+43,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_3),6);
        bufp->chgCData(oldp+44,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_4),6);
        bufp->chgCData(oldp+45,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_5),6);
        bufp->chgCData(oldp+46,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_6),6);
        bufp->chgCData(oldp+47,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_7),6);
        bufp->chgCData(oldp+48,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_8),6);
        bufp->chgCData(oldp+49,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_9),6);
        bufp->chgCData(oldp+50,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_10),6);
        bufp->chgCData(oldp+51,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_11),6);
        bufp->chgCData(oldp+52,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_12),6);
        bufp->chgCData(oldp+53,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_13),6);
        bufp->chgCData(oldp+54,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_14),6);
        bufp->chgCData(oldp+55,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_15),6);
        bufp->chgBit(oldp+56,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__in_display_d1));
        bufp->chgBit(oldp+57,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d1));
        bufp->chgBit(oldp+58,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d1));
        bufp->chgBit(oldp+59,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d2));
        bufp->chgBit(oldp+60,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d2));
        bufp->chgCData(oldp+61,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__pixel_in_word_d1),3);
        bufp->chgSData(oldp+62,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px_d1),10);
        bufp->chgSData(oldp+63,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px_d1),10);
        bufp->chgSData(oldp+64,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addrb),13);
        bufp->chgIData(oldp+65,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___framebuffer_doutb),32);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[3U])) {
        bufp->chgIData(oldp+66,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg),32);
        bufp->chgCData(oldp+67,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_0),6);
        bufp->chgCData(oldp+68,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_1),6);
        bufp->chgCData(oldp+69,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_2),6);
        bufp->chgCData(oldp+70,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_3),6);
        bufp->chgCData(oldp+71,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_4),6);
        bufp->chgCData(oldp+72,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_5),6);
        bufp->chgCData(oldp+73,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_6),6);
        bufp->chgCData(oldp+74,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_7),6);
        bufp->chgCData(oldp+75,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_8),6);
        bufp->chgCData(oldp+76,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_9),6);
        bufp->chgCData(oldp+77,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_10),6);
        bufp->chgCData(oldp+78,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_11),6);
        bufp->chgCData(oldp+79,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_12),6);
        bufp->chgCData(oldp+80,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_13),6);
        bufp->chgCData(oldp+81,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_14),6);
        bufp->chgCData(oldp+82,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_15),6);
        bufp->chgBit(oldp+83,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette));
    }
    bufp->chgBit(oldp+84,(vlSelf->clock));
    bufp->chgBit(oldp+85,(vlSelf->reset));
    bufp->chgIData(oldp+86,(vlSelf->io_mmio_addr),32);
    bufp->chgIData(oldp+87,(vlSelf->io_mmio_wdata),32);
    bufp->chgBit(oldp+88,(vlSelf->io_mmio_wen));
    bufp->chgIData(oldp+89,(vlSelf->io_mmio_rdata),32);
    bufp->chgBit(oldp+90,(vlSelf->io_pixClock));
    bufp->chgBit(oldp+91,(vlSelf->io_hsync));
    bufp->chgBit(oldp+92,(vlSelf->io_vsync));
    bufp->chgCData(oldp+93,(vlSelf->io_rgb),6);
    bufp->chgBit(oldp+94,(vlSelf->io_activevideo));
    bufp->chgSData(oldp+95,(vlSelf->io_x_pos),10);
    bufp->chgSData(oldp+96,(vlSelf->io_y_pos),10);
    bufp->chgBit(oldp+97,(vlSelf->io_intr));
    bufp->chgBit(oldp+98,((4U == (0xffU & vlSelf->io_mmio_addr))));
    bufp->chgBit(oldp+99,((0xcU == (0xffU & vlSelf->io_mmio_addr))));
    bufp->chgBit(oldp+100,((0x10U == (0xffU & vlSelf->io_mmio_addr))));
    bufp->chgBit(oldp+101,((0x14U == (0xffU & vlSelf->io_mmio_addr))));
    bufp->chgBit(oldp+102,(((IData)(vlSelf->io_mmio_wen) 
                            & ((~ (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN)) 
                               & (0x14U == (0xffU & vlSelf->io_mmio_addr))))));
    bufp->chgSData(oldp+103,(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addra),13);
    bufp->chgIData(oldp+104,(((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN_0)
                               ? 0U : vlSelf->io_mmio_wdata)),32);
}

void VVgaStandaloneWrapper___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root__trace_cleanup\n"); );
    // Init
    VVgaStandaloneWrapper___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VVgaStandaloneWrapper___024root*>(voidSelf);
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
