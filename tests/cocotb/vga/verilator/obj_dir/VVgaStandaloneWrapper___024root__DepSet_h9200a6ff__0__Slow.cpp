// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VVgaStandaloneWrapper.h for the primary calling header

#include "VVgaStandaloneWrapper__pch.h"
#include "VVgaStandaloneWrapper___024root.h"

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___eval_static(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_static\n"); );
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___eval_initial__TOP(VVgaStandaloneWrapper___024root* vlSelf);

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___eval_initial(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_initial\n"); );
    // Body
    VVgaStandaloneWrapper___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vm_traceActivity[3U] = 1U;
    vlSelf->__Vm_traceActivity[2U] = 1U;
    vlSelf->__Vm_traceActivity[1U] = 1U;
    vlSelf->__Vm_traceActivity[0U] = 1U;
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = vlSelf->clock;
    vlSelf->__Vtrigprevexpr___TOP__io_pixClock__0 = vlSelf->io_pixClock;
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___eval_initial__TOP(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_initial__TOP\n"); );
    // Body
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i = 0U;
    while (VL_GTS_III(32, 0x1800U, vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i)) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT____Vlvbound_h63da11d2__0 = 0U;
        if (VL_LIKELY((0x17ffU >= (0x1fffU & vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i)))) {
            vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem[(0x1fffU 
                                                                                & vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i)] 
                = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT____Vlvbound_h63da11d2__0;
        }
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i 
            = ((IData)(1U) + vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i);
    }
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___eval_final(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__stl(VVgaStandaloneWrapper___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool VVgaStandaloneWrapper___024root___eval_phase__stl(VVgaStandaloneWrapper___024root* vlSelf);

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___eval_settle(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            VVgaStandaloneWrapper___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("VgaStandaloneWrapper.sv", 2, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (VVgaStandaloneWrapper___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__stl(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___stl_sequent__TOP__0(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___stl_sequent__TOP__0\n"); );
    // Init
    CData/*6:0*/ VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0;
    VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0 = 0;
    VlWide<3>/*95:0*/ __Vtemp_6;
    // Body
    vlSelf->io_hsync = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_hsync_REG;
    vlSelf->io_vsync = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_vsync_REG;
    vlSelf->io_x_pos = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px_d1;
    vlSelf->io_y_pos = vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px_d1;
    vlSelf->io_intr = ((0U != vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg) 
                       & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg 
                          >> 8U));
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
    vlSelf->io_activevideo = ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d2) 
                              & (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d2));
    VgaStandaloneWrapper__DOT__vga__DOT____VdfgTmp_h5c770ce7__0 
        = (0x7fU & ((IData)(6U) * (0xfU & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___framebuffer_doutb 
                                           >> (0x1fU 
                                               & VL_SHIFTL_III(5,5,32, (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__pixel_in_word_d1), 2U))))));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___pixel_idx_T_1 
        = (0x1fffU & ((((0U != (3U & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_y_mult 
                                      >> 0x16U))) ? 0x3fU
                         : (0x3fU & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_y_mult 
                                     >> 0x10U))) << 6U) 
                      + ((0U != (3U & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_x_mult 
                                       >> 0x16U))) ? 0x3fU
                          : (0x3fU & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_x_mult 
                                      >> 0x10U)))));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN_0 
        = (1U & ((~ (IData)(vlSelf->io_mmio_wen)) | 
                 ((0x14U != (0xffU & vlSelf->io_mmio_addr)) 
                  | (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN))));
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
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addrb 
        = (0x1fffU & (((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame) 
                       << 9U) + VL_SHIFTR_III(13,13,32, (IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___pixel_idx_T_1), 3U)));
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addra 
        = ((IData)(vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN_0)
            ? 0U : (0x1fffU & ((0x1e00U & (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
                                           >> 7U)) 
                               + (vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg 
                                  >> 3U))));
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___eval_stl(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VVgaStandaloneWrapper___024root___stl_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[3U] = 1U;
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___eval_triggers__stl(VVgaStandaloneWrapper___024root* vlSelf);

VL_ATTR_COLD bool VVgaStandaloneWrapper___024root___eval_phase__stl(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    VVgaStandaloneWrapper___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        VVgaStandaloneWrapper___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__ico(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__act(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
    if ((2ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge io_pixClock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__nba(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
    if ((2ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge io_pixClock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___ctor_var_reset(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clock = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->io_mmio_addr = VL_RAND_RESET_I(32);
    vlSelf->io_mmio_wdata = VL_RAND_RESET_I(32);
    vlSelf->io_mmio_wen = VL_RAND_RESET_I(1);
    vlSelf->io_mmio_rdata = VL_RAND_RESET_I(32);
    vlSelf->io_pixClock = VL_RAND_RESET_I(1);
    vlSelf->io_hsync = VL_RAND_RESET_I(1);
    vlSelf->io_vsync = VL_RAND_RESET_I(1);
    vlSelf->io_rgb = VL_RAND_RESET_I(6);
    vlSelf->io_activevideo = VL_RAND_RESET_I(1);
    vlSelf->io_x_pos = VL_RAND_RESET_I(10);
    vlSelf->io_y_pos = VL_RAND_RESET_I(10);
    vlSelf->io_intr = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___framebuffer_doutb = VL_RAND_RESET_I(32);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg = VL_RAND_RESET_I(32);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg = VL_RAND_RESET_I(32);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg = VL_RAND_RESET_I(32);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_0 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_1 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_2 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_3 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_4 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_5 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_6 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_7 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_8 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_9 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_10 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_11 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_12 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_13 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_14 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_15 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_sync1 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_synced = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1 = VL_RAND_RESET_I(4);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_synced = VL_RAND_RESET_I(4);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vblank_prev = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___GEN_0 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_count = VL_RAND_RESET_I(10);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_count = VL_RAND_RESET_I(10);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__hsync_d1 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__vsync_d1 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_hsync_REG = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__io_vsync_REG = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px = VL_RAND_RESET_I(10);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px = VL_RAND_RESET_I(10);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_x_mult = VL_RAND_RESET_I(24);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__frame_y_mult = VL_RAND_RESET_I(24);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1_1 = VL_RAND_RESET_I(4);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__curr_frame = VL_RAND_RESET_I(4);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled_sync1 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__display_enabled = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking_sync1 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__blanking = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_0 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_1 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_2 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_3 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_4 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_5 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_6 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_7 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_8 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_9 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_10 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_11 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_12 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_13 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_14 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_15 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_0 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_1 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_2 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_3 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_4 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_5 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_6 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_7 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_8 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_9 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_10 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_11 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_12 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_13 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_14 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_15 = VL_RAND_RESET_I(6);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__in_display_d1 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d1 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d1 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__h_active_d2 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__v_active_d2 = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT___pixel_idx_T_1 = VL_RAND_RESET_I(13);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__pixel_in_word_d1 = VL_RAND_RESET_I(3);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__x_px_d1 = VL_RAND_RESET_I(10);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__y_px_d1 = VL_RAND_RESET_I(10);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addrb = VL_RAND_RESET_I(13);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addra = VL_RAND_RESET_I(13);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette = VL_RAND_RESET_I(1);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__unnamedblk2__DOT___next_addr_T = VL_RAND_RESET_I(16);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk3__DOT___GEN_5 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 6144; ++__Vi0) {
        vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i = VL_RAND_RESET_I(32);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT____Vlvbound_he244be65__0 = VL_RAND_RESET_I(32);
    vlSelf->VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT____Vlvbound_h63da11d2__0 = VL_RAND_RESET_I(32);
    vlSelf->__Vdly__VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg = VL_RAND_RESET_I(32);
    vlSelf->__Vdlyvdim0__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0 = 0;
    vlSelf->__Vdlyvval__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0 = VL_RAND_RESET_I(32);
    vlSelf->__Vdlyvset__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__io_pixClock__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
