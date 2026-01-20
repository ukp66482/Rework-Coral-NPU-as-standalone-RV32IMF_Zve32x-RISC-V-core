// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VVgaStandaloneWrapper.h for the primary calling header

#include "VVgaStandaloneWrapper__pch.h"
#include "VVgaStandaloneWrapper__Syms.h"
#include "VVgaStandaloneWrapper___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__ico(VVgaStandaloneWrapper___024root* vlSelf);
#endif  // VL_DEBUG

void VVgaStandaloneWrapper___024root___eval_triggers__ico(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.set(0U, (IData)(vlSelf->__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VVgaStandaloneWrapper___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__act(VVgaStandaloneWrapper___024root* vlSelf);
#endif  // VL_DEBUG

void VVgaStandaloneWrapper___024root___eval_triggers__act(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clock) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clock__0))));
    vlSelf->__VactTriggered.set(1U, ((IData)(vlSelf->io_pixClock) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__io_pixClock__0))));
    vlSelf->__Vtrigprevexpr___TOP__clock__0 = vlSelf->clock;
    vlSelf->__Vtrigprevexpr___TOP__io_pixClock__0 = vlSelf->io_pixClock;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VVgaStandaloneWrapper___024root___dump_triggers__act(vlSelf);
    }
#endif
}
