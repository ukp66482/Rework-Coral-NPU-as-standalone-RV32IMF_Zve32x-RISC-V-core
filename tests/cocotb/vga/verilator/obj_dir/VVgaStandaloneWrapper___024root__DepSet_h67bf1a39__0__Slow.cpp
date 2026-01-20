// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VVgaStandaloneWrapper.h for the primary calling header

#include "VVgaStandaloneWrapper__pch.h"
#include "VVgaStandaloneWrapper__Syms.h"
#include "VVgaStandaloneWrapper___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VVgaStandaloneWrapper___024root___dump_triggers__stl(VVgaStandaloneWrapper___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void VVgaStandaloneWrapper___024root___eval_triggers__stl(VVgaStandaloneWrapper___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VVgaStandaloneWrapper___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.set(0U, (IData)(vlSelf->__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VVgaStandaloneWrapper___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
