// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VVgaStandaloneWrapper.h for the primary calling header

#include "VVgaStandaloneWrapper__pch.h"
#include "VVgaStandaloneWrapper___024root.h"

VL_INLINE_OPT void VVgaStandaloneWrapper___024root___ico_sequent__TOP__0(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN 
        = ((4U == (0xffU & vlSelf->io_mmio_addr)) | 
           ((0xcU == (0xffU & vlSelf->io_mmio_addr)) 
            | (0x10U == (0xffU & vlSelf->io_mmio_addr))));
    vlSelf->io_mmio_rdata = ((0x5cU == (0xffU & vlSelf->io_mmio_addr))
                              ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_15)
                              : ((0x58U == (0xffU & vlSelf->io_mmio_addr))
                                  ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_14)
                                  : ((0x54U == (0xffU 
                                                & vlSelf->io_mmio_addr))
                                      ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_13)
                                      : ((0x50U == 
                                          (0xffU & vlSelf->io_mmio_addr))
                                          ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_12)
                                          : ((0x4cU 
                                              == (0xffU 
                                                  & vlSelf->io_mmio_addr))
                                              ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_11)
                                              : ((0x48U 
                                                  == 
                                                  (0xffU 
                                                   & vlSelf->io_mmio_addr))
                                                  ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_10)
                                                  : 
                                                 ((0x44U 
                                                   == 
                                                   (0xffU 
                                                    & vlSelf->io_mmio_addr))
                                                   ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_9)
                                                   : 
                                                  ((0x40U 
                                                    == 
                                                    (0xffU 
                                                     & vlSelf->io_mmio_addr))
                                                    ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_8)
                                                    : 
                                                   ((0x3cU 
                                                     == 
                                                     (0xffU 
                                                      & vlSelf->io_mmio_addr))
                                                     ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_7)
                                                     : 
                                                    ((0x38U 
                                                      == 
                                                      (0xffU 
                                                       & vlSelf->io_mmio_addr))
                                                      ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_6)
                                                      : 
                                                     ((0x34U 
                                                       == 
                                                       (0xffU 
                                                        & vlSelf->io_mmio_addr))
                                                       ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_5)
                                                       : 
                                                      ((0x30U 
                                                        == 
                                                        (0xffU 
                                                         & vlSelf->io_mmio_addr))
                                                        ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_4)
                                                        : 
                                                       ((0x2cU 
                                                         == 
                                                         (0xffU 
                                                          & vlSelf->io_mmio_addr))
                                                         ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_3)
                                                         : 
                                                        ((0x28U 
                                                          == 
                                                          (0xffU 
                                                           & vlSelf->io_mmio_addr))
                                                          ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_2)
                                                          : 
                                                         ((0x24U 
                                                           == 
                                                           (0xffU 
                                                            & vlSelf->io_mmio_addr))
                                                           ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_1)
                                                           : 
                                                          ((0x20U 
                                                            == 
                                                            (0xffU 
                                                             & vlSelf->io_mmio_addr))
                                                            ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_0)
                                                            : 
                                                           ((0x10U 
                                                             == 
                                                             (0xffU 
                                                              & vlSelf->io_mmio_addr))
                                                             ? vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg
                                                             : 
                                                            ((0xcU 
                                                              == 
                                                              (0xffU 
                                                               & vlSelf->io_mmio_addr))
                                                              ? vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg
                                                              : 
                                                             ((8U 
                                                               == 
                                                               (0xffU 
                                                                & vlSelf->io_mmio_addr))
                                                               ? 
                                                              (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_synced) 
                                                                << 5U) 
                                                               | (3U 
                                                                  & (- (IData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_synced)))))
                                                               : 
                                                              ((4U 
                                                                == 
                                                                (0xffU 
                                                                 & vlSelf->io_mmio_addr))
                                                                ? vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg
                                                                : 
                                                               ((0U 
                                                                 == 
                                                                 (0xffU 
                                                                  & vlSelf->io_mmio_addr))
                                                                 ? 0x56474131U
                                                                 : 0U)))))))))))))))))))));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN_0 
        = (1U & ((~ (IData)(vlSelf->io_mmio_wen)) | 
                 ((0x14U != (0xffU & vlSelf->io_mmio_addr)) 
                  | (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN))));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addra 
        = ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN_0)
            ? 0U : (0x1fffU & ((0x1e00U & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
                                           >> 7U)) 
                               + (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
                                  >> 3U))));
}

void VVgaStandaloneWrapper___024root___eval_ico(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_ico\n"); );
    // Body
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        VVgaStandaloneWrapper___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void VVgaStandaloneWrapper___024root___eval_triggers__ico(VVgaStandaloneWrapper___024root* vlSelf);

bool VVgaStandaloneWrapper___024root___eval_phase__ico(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    VVgaStandaloneWrapper___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        VVgaStandaloneWrapper___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void VVgaStandaloneWrapper___024root___eval_act(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_act\n"); );
}

VL_INLINE_OPT void VVgaStandaloneWrapper___024root___nba_sequent__TOP__0(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___nba_sequent__TOP__0\n"); );
    // Init
    IData/*31:0*/ __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg;
    __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg = 0;
    IData/*31:0*/ __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg;
    __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg = 0;
    // Body
    vlSelf->__Vdlyvset__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0 = 0U;
    __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg;
    __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg;
    vlSelf->__Vdly__VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg;
    if (((IData)(vlSelf->io_mmio_wen) & ((~ (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN)) 
                                         & (0x14U == 
                                            (0xffU 
                                             & vlSelf->io_mmio_addr))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT____Vlvbound_he244be65__0 
            = ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN_0)
                ? 0U : vlSelf->io_mmio_wdata);
        if ((0x17ffU >= (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addra))) {
            vlSelf->__Vdlyvval__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0 
                = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT____Vlvbound_he244be65__0;
            vlSelf->__Vdlyvset__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0 = 1U;
            vlSelf->__Vdlyvdim0__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0 
                = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addra;
        }
    }
    if (vlSelf->reset) {
        __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg = 0U;
        vlSelf->__Vdly__VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg = 0U;
        __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg = 0U;
    } else {
        if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                       | (4U == (0xffU & vlSelf->io_mmio_addr))) 
                      | (0xcU == (0xffU & vlSelf->io_mmio_addr)))))) {
            if ((0x10U == (0xffU & vlSelf->io_mmio_addr))) {
                __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
                    = vlSelf->io_mmio_wdata;
            } else if ((0x14U == (0xffU & vlSelf->io_mmio_addr))) {
                vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__unnamedblk2__DOT___next_addr_T 
                    = (0xffffU & ((IData)(8U) + vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg));
                __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
                    = ((0xf0000U & vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg) 
                       | ((0U != (0xfU & ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__unnamedblk2__DOT___next_addr_T) 
                                          >> 0xcU)))
                           ? 0U : (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__unnamedblk2__DOT___next_addr_T)));
            }
        }
        if (((IData)(vlSelf->io_mmio_wen) & (4U == 
                                             (0xffU 
                                              & vlSelf->io_mmio_addr)))) {
            vlSelf->__Vdly__VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg 
                = ((3U != (3U & (vlSelf->io_mmio_wdata 
                                 >> 6U))) ? vlSelf->io_mmio_wdata
                    : ((0xfffffff0U & vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg) 
                       | (1U & vlSelf->io_mmio_wdata)));
        }
        if ((1U & (((~ (IData)(vlSelf->io_mmio_wen)) 
                    | (4U == (0xffU & vlSelf->io_mmio_addr))) 
                   | (0xcU != (0xffU & vlSelf->io_mmio_addr))))) {
            if ((((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_synced) 
                  & (~ (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_prev))) 
                 & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg 
                    >> 8U))) {
                __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg = 1U;
            }
        } else {
            __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg 
                = (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg 
                   & (~ vlSelf->io_mmio_wdata));
        }
    }
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_prev 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_synced;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_synced 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
        = __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg 
        = __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_synced 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_sync1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_sync1 
        = (0x1dfU < (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count));
}

VL_INLINE_OPT void VVgaStandaloneWrapper___024root___nba_sequent__TOP__1(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___nba_sequent__TOP__1\n"); );
    // Init
    CData/*6:0*/ VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0;
    VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0 = 0;
    SData/*9:0*/ __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__h_count;
    __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__h_count = 0;
    SData/*9:0*/ __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__v_count;
    __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__v_count = 0;
    VlWide<3>/*95:0*/ __Vtemp_6;
    // Body
    __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__v_count 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count;
    __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__h_count 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__pixel_in_word_d1 
        = (7U & (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___pixel_idx_T_1));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___framebuffer_doutb 
        = ((0x17ffU >= (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addrb))
            ? vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem
           [vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addrb]
            : 0U);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking_sync1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled_sync1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_vsync_REG 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vsync_d1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_hsync_REG 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__hsync_d1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d2 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d2 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__in_display_d1 
        = ((((0U != (7U & ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px) 
                           >> 7U))) & (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px) 
                                          >> 9U))) 
            & (0x2fU < (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px))) 
           & (0x1b0U > (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px)));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px_d1 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px_d1 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_15 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_15;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_14 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_14;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_12 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_12;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_11 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_11;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_9 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_9;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_8 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_8;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_7 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_7;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_5 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_5;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_4 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_4;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_3 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_3;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_13 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_13;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_10 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_10;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_2 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_2;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_6 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_6;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_0 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_0;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_1 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1_1;
    VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0 
        = (0x7fU & ((IData)(6U) * (0xfU & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___framebuffer_doutb 
                                           >> (0x1fU 
                                               & VL_SHIFTL_III(5,5,32, (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__pixel_in_word_d1), 2U))))));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking_sync1 
        = (1U & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg 
                 >> 1U));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled_sync1 
        = (1U & vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg);
    vlSelf->io_vsync = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_vsync_REG;
    vlSelf->io_hsync = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_hsync_REG;
    vlSelf->io_activevideo = ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d2) 
                              & (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d2));
    vlSelf->io_x_pos = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px_d1;
    vlSelf->io_y_pos = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px_d1;
    if (vlSelf->reset) {
        __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__h_count = 0U;
        __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__v_count = 0U;
    } else {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk3__DOT___GEN_5 
            = (0x33fU == (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count));
        if (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk3__DOT___GEN_5) {
            __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__h_count = 0U;
            __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__v_count 
                = ((0x207U == (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count))
                    ? 0U : (0x3ffU & ((IData)(1U) + (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count))));
        } else {
            __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__h_count 
                = (0x3ffU & ((IData)(1U) + (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count)));
        }
    }
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__hsync_d1 
        = (1U & (~ ((0x297U < (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count)) 
                    & (0x2c0U > (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count)))));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vsync_d1 
        = (1U & (~ ((0x1e8U < (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count)) 
                    & (0x1ecU > (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count)))));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d1 
        = (0x280U > (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d1 
        = (0x1e0U > (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_15 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_15;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_14 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_14;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_12 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_12;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_11 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_11;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_9 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_9;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_8 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_8;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_7 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_7;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_5 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_5;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_4 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_4;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_3 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_3;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_13 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_13;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_10 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_10;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_2 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_2;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_6 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_6;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_0 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_0;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_1 
        = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_1;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1_1 
        = (0xfU & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg 
                   >> 4U));
    __Vtemp_6[0U] = (IData)((((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_9)) 
                              << 0x36U) | (((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_8)) 
                                            << 0x30U) 
                                           | (((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_7)) 
                                               << 0x2aU) 
                                              | (((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_6)) 
                                                  << 0x24U) 
                                                 | (((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_5)) 
                                                     << 0x1eU) 
                                                    | (QData)((IData)(
                                                                      (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_4) 
                                                                        << 0x18U) 
                                                                       | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_3) 
                                                                           << 0x12U) 
                                                                          | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_2) 
                                                                              << 0xcU) 
                                                                             | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_1) 
                                                                                << 6U) 
                                                                                | (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_0)))))))))))));
    __Vtemp_6[1U] = (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_10) 
                      << 0x1cU) | (IData)(((((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_9)) 
                                             << 0x36U) 
                                            | (((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_8)) 
                                                << 0x30U) 
                                               | (((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_7)) 
                                                   << 0x2aU) 
                                                  | (((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_6)) 
                                                      << 0x24U) 
                                                     | (((QData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_5)) 
                                                         << 0x1eU) 
                                                        | (QData)((IData)(
                                                                          (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_4) 
                                                                            << 0x18U) 
                                                                           | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_3) 
                                                                               << 0x12U) 
                                                                              | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_2) 
                                                                                << 0xcU) 
                                                                                | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_1) 
                                                                                << 6U) 
                                                                                | (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_0)))))))))))) 
                                           >> 0x20U)));
    __Vtemp_6[2U] = (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_15) 
                      << 0x1aU) | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_14) 
                                    << 0x14U) | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_13) 
                                                  << 0xeU) 
                                                 | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_12) 
                                                     << 8U) 
                                                    | (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_11) 
                                                        << 2U) 
                                                       | ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_10) 
                                                          >> 4U))))));
    vlSelf->io_rgb = ((1U & ((~ (IData)(vlSelf->io_activevideo)) 
                             | (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking)))
                       ? 0U : (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled) 
                                & (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__in_display_d1))
                                ? ((0x5fU >= (IData)(VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0))
                                    ? (0x3fU & (((0U 
                                                  == 
                                                  (0x1fU 
                                                   & (IData)(VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0)))
                                                  ? 0U
                                                  : 
                                                 (__Vtemp_6[
                                                  (((IData)(5U) 
                                                    + (IData)(VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0)) 
                                                   >> 5U)] 
                                                  << 
                                                  ((IData)(0x20U) 
                                                   - 
                                                   (0x1fU 
                                                    & (IData)(VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0))))) 
                                                | (__Vtemp_6[
                                                   ((IData)(VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0) 
                                                    >> 5U)] 
                                                   >> 
                                                   (0x1fU 
                                                    & (IData)(VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0)))))
                                    : 0U) : 1U));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count 
        = __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__h_count;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count 
        = __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__v_count;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_x_mult 
        = (0xffffffU & ((IData)(0x2aabU) * ((0U != 
                                             (7U & 
                                              ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px) 
                                               >> 7U)))
                                             ? (0x3ffU 
                                                & ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px) 
                                                   - (IData)(0x80U)))
                                             : 0U)));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_y_mult 
        = (0xffffffU & ((IData)(0x2aabU) * ((0x2fU 
                                             < (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px))
                                             ? (0x3ffU 
                                                & ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px) 
                                                   - (IData)(0x30U)))
                                             : 0U)));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___pixel_idx_T_1 
        = (0x1fffU & ((((0U != (3U & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_y_mult 
                                      >> 0x16U))) ? 0x3fU
                         : (0x3fU & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_y_mult 
                                     >> 0x10U))) << 6U) 
                      + ((0U != (3U & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_x_mult 
                                       >> 0x16U))) ? 0x3fU
                          : (0x3fU & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_x_mult 
                                      >> 0x10U)))));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addrb 
        = (0x1fffU & (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame) 
                       << 9U) + VL_SHIFTR_III(13,13,32, (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___pixel_idx_T_1), 3U)));
}

VL_INLINE_OPT void VVgaStandaloneWrapper___024root___nba_sequent__TOP__2(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___nba_sequent__TOP__2\n"); );
    // Init
    CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3;
    VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3 = 0;
    CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4;
    VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4 = 0;
    // Body
    if (vlSelf->__Vdlyvset__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem[vlSelf->__Vdlyvdim0__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0] 
            = vlSelf->__Vdlyvval__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0;
    }
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg 
        = vlSelf->__Vdly__VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg;
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addra 
        = ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN_0)
            ? 0U : (0x1fffU & ((0x1e00U & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
                                           >> 7U)) 
                               + (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
                                  >> 3U))));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette 
        = ((0U != (7U & (vlSelf->io_mmio_addr >> 5U))) 
           & (0x60U > (0xffU & vlSelf->io_mmio_addr)));
    VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3 
        = (0x3fU & (vlSelf->io_mmio_addr - (IData)(0x20U)));
    VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4 
        = ((((4U == (0xffU & vlSelf->io_mmio_addr)) 
             | (0xcU == (0xffU & vlSelf->io_mmio_addr))) 
            | (0x10U == (0xffU & vlSelf->io_mmio_addr))) 
           | (0x14U == (0xffU & vlSelf->io_mmio_addr)));
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_0 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (4U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_1 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (8U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_2 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0xcU == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_3 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x10U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_4 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x14U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_5 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x18U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_6 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x1cU == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_7 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x20U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_8 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x24U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_9 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x28U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_10 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x2cU == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_11 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x30U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_12 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x34U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_13 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x38U == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_14 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    if ((1U & (~ (((~ (IData)(vlSelf->io_mmio_wen)) 
                   | (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_4)) 
                  | (~ ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette) 
                        & (0x3cU == (0x3cU & (IData)(VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT___GEN_3))))))))) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_15 
            = (0x3fU & vlSelf->io_mmio_wdata);
    }
    vlSelf->io_intr = ((0U != vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg) 
                       & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg 
                          >> 8U));
    vlSelf->io_mmio_rdata = ((0x5cU == (0xffU & vlSelf->io_mmio_addr))
                              ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_15)
                              : ((0x58U == (0xffU & vlSelf->io_mmio_addr))
                                  ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_14)
                                  : ((0x54U == (0xffU 
                                                & vlSelf->io_mmio_addr))
                                      ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_13)
                                      : ((0x50U == 
                                          (0xffU & vlSelf->io_mmio_addr))
                                          ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_12)
                                          : ((0x4cU 
                                              == (0xffU 
                                                  & vlSelf->io_mmio_addr))
                                              ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_11)
                                              : ((0x48U 
                                                  == 
                                                  (0xffU 
                                                   & vlSelf->io_mmio_addr))
                                                  ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_10)
                                                  : 
                                                 ((0x44U 
                                                   == 
                                                   (0xffU 
                                                    & vlSelf->io_mmio_addr))
                                                   ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_9)
                                                   : 
                                                  ((0x40U 
                                                    == 
                                                    (0xffU 
                                                     & vlSelf->io_mmio_addr))
                                                    ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_8)
                                                    : 
                                                   ((0x3cU 
                                                     == 
                                                     (0xffU 
                                                      & vlSelf->io_mmio_addr))
                                                     ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_7)
                                                     : 
                                                    ((0x38U 
                                                      == 
                                                      (0xffU 
                                                       & vlSelf->io_mmio_addr))
                                                      ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_6)
                                                      : 
                                                     ((0x34U 
                                                       == 
                                                       (0xffU 
                                                        & vlSelf->io_mmio_addr))
                                                       ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_5)
                                                       : 
                                                      ((0x30U 
                                                        == 
                                                        (0xffU 
                                                         & vlSelf->io_mmio_addr))
                                                        ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_4)
                                                        : 
                                                       ((0x2cU 
                                                         == 
                                                         (0xffU 
                                                          & vlSelf->io_mmio_addr))
                                                         ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_3)
                                                         : 
                                                        ((0x28U 
                                                          == 
                                                          (0xffU 
                                                           & vlSelf->io_mmio_addr))
                                                          ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_2)
                                                          : 
                                                         ((0x24U 
                                                           == 
                                                           (0xffU 
                                                            & vlSelf->io_mmio_addr))
                                                           ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_1)
                                                           : 
                                                          ((0x20U 
                                                            == 
                                                            (0xffU 
                                                             & vlSelf->io_mmio_addr))
                                                            ? (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_0)
                                                            : 
                                                           ((0x10U 
                                                             == 
                                                             (0xffU 
                                                              & vlSelf->io_mmio_addr))
                                                             ? vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg
                                                             : 
                                                            ((0xcU 
                                                              == 
                                                              (0xffU 
                                                               & vlSelf->io_mmio_addr))
                                                              ? vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg
                                                              : 
                                                             ((8U 
                                                               == 
                                                               (0xffU 
                                                                & vlSelf->io_mmio_addr))
                                                               ? 
                                                              (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_synced) 
                                                                << 5U) 
                                                               | (3U 
                                                                  & (- (IData)((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_synced)))))
                                                               : 
                                                              ((4U 
                                                                == 
                                                                (0xffU 
                                                                 & vlSelf->io_mmio_addr))
                                                                ? vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg
                                                                : 
                                                               ((0U 
                                                                 == 
                                                                 (0xffU 
                                                                  & vlSelf->io_mmio_addr))
                                                                 ? 0x56474131U
                                                                 : 0U)))))))))))))))))))));
}

void VVgaStandaloneWrapper___024root___eval_nba(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VVgaStandaloneWrapper___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VVgaStandaloneWrapper___024root___nba_sequent__TOP__1(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VVgaStandaloneWrapper___024root___nba_sequent__TOP__2(vlSelf);
        vlSelf->__Vm_traceActivity[3U] = 1U;
    }
}

void VVgaStandaloneWrapper___024root___eval_triggers__act(VVgaStandaloneWrapper___024root* vlSelf);

bool VVgaStandaloneWrapper___024root___eval_phase__act(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    VVgaStandaloneWrapper___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        VVgaStandaloneWrapper___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool VVgaStandaloneWrapper___024root___eval_phase__nba(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        VVgaStandaloneWrapper___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__ico(VVgaStandaloneWrapper___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__nba(VVgaStandaloneWrapper___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__act(VVgaStandaloneWrapper___024root* vlSelf);
#endif  // VL_DEBUG

void VVgaStandaloneWrapper___024root___eval(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelf->__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            VVgaStandaloneWrapper___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("VgaStandaloneWrapper.sv", 2, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (VVgaStandaloneWrapper___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            VVgaStandaloneWrapper___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("VgaStandaloneWrapper.sv", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                VVgaStandaloneWrapper___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("VgaStandaloneWrapper.sv", 2, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (VVgaStandaloneWrapper___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (VVgaStandaloneWrapper___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void VVgaStandaloneWrapper___024root___eval_debug_assertions(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clock & 0xfeU))) {
        Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((vlSelf->reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((vlSelf->io_mmio_wen & 0xfeU))) {
        Verilated::overWidthError("io_mmio_wen");}
    if (VL_UNLIKELY((vlSelf->io_pixClock & 0xfeU))) {
        Verilated::overWidthError("io_pixClock");}
}
#endif  // VL_DEBUG
