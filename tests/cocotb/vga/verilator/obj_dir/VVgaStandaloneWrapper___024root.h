// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VVgaStandaloneWrapper.h for the primary calling header

#ifndef VERILATED_VVGASTANDALONEWRAPPER___024ROOT_H_
#define VERILATED_VVGASTANDALONEWRAPPER___024ROOT_H_  // guard

#include "verilated.h"


class VVgaStandaloneWrapper__Syms;

class alignas(VL_CACHE_LINE_BYTES) VVgaStandaloneWrapper___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clock,0,0);
        VL_IN8(io_pixClock,0,0);
        VL_IN8(reset,0,0);
        VL_IN8(io_mmio_wen,0,0);
        VL_OUT8(io_hsync,0,0);
        VL_OUT8(io_vsync,0,0);
        VL_OUT8(io_rgb,5,0);
        VL_OUT8(io_activevideo,0,0);
        VL_OUT8(io_intr,0,0);
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_0;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_1;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_2;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_3;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_4;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_5;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_6;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_7;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_8;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_9;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_10;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_11;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_12;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_13;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_14;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__paletteReg_15;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__vblank_sync1;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__vblank_synced;
        CData/*3:0*/ VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1;
        CData/*3:0*/ VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_synced;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__vblank_prev;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT___GEN;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT___GEN_0;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__hsync_d1;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__vsync_d1;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__io_hsync_REG;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__io_vsync_REG;
        CData/*3:0*/ VgaStandaloneWrapper__DOT__vga__DOT__curr_frame_sync1_1;
        CData/*3:0*/ VgaStandaloneWrapper__DOT__vga__DOT__curr_frame;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__display_enabled_sync1;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__display_enabled;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__blanking_sync1;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__blanking;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_0;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_1;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_2;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_3;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_4;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_5;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_6;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_7;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_8;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_9;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_10;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_11;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_12;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_13;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_14;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync1_15;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_0;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_1;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_2;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_3;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_4;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_5;
    };
    struct {
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_6;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_7;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_8;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_9;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_10;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_11;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_12;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_13;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_14;
        CData/*5:0*/ VgaStandaloneWrapper__DOT__vga__DOT__palette_sync_15;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__in_display_d1;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__h_active_d1;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__v_active_d1;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__h_active_d2;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__v_active_d2;
        CData/*2:0*/ VgaStandaloneWrapper__DOT__vga__DOT__pixel_in_word_d1;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__addr_palette;
        CData/*0:0*/ VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk3__DOT___GEN_5;
        CData/*0:0*/ __Vdlyvset__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clock__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__io_pixClock__0;
        CData/*0:0*/ __VactContinue;
        VL_OUT16(io_x_pos,9,0);
        VL_OUT16(io_y_pos,9,0);
        SData/*9:0*/ VgaStandaloneWrapper__DOT__vga__DOT__h_count;
        SData/*9:0*/ VgaStandaloneWrapper__DOT__vga__DOT__v_count;
        SData/*9:0*/ VgaStandaloneWrapper__DOT__vga__DOT__x_px;
        SData/*9:0*/ VgaStandaloneWrapper__DOT__vga__DOT__y_px;
        SData/*12:0*/ VgaStandaloneWrapper__DOT__vga__DOT___pixel_idx_T_1;
        SData/*9:0*/ VgaStandaloneWrapper__DOT__vga__DOT__x_px_d1;
        SData/*9:0*/ VgaStandaloneWrapper__DOT__vga__DOT__y_px_d1;
        SData/*12:0*/ VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addrb;
        SData/*12:0*/ VgaStandaloneWrapper__DOT__vga__DOT____Vcellinp__framebuffer__addra;
        SData/*15:0*/ VgaStandaloneWrapper__DOT__vga__DOT__unnamedblk1__DOT__unnamedblk2__DOT___next_addr_T;
        SData/*12:0*/ __Vdlyvdim0__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0;
        VL_IN(io_mmio_addr,31,0);
        VL_IN(io_mmio_wdata,31,0);
        VL_OUT(io_mmio_rdata,31,0);
        IData/*31:0*/ VgaStandaloneWrapper__DOT__vga__DOT___framebuffer_doutb;
        IData/*31:0*/ VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg;
        IData/*31:0*/ VgaStandaloneWrapper__DOT__vga__DOT__intrStatusReg;
        IData/*31:0*/ VgaStandaloneWrapper__DOT__vga__DOT__uploadAddrReg;
        IData/*23:0*/ VgaStandaloneWrapper__DOT__vga__DOT__frame_x_mult;
        IData/*23:0*/ VgaStandaloneWrapper__DOT__vga__DOT__frame_y_mult;
        IData/*31:0*/ VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__i;
        IData/*31:0*/ VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT____Vlvbound_he244be65__0;
        IData/*31:0*/ VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT____Vlvbound_h63da11d2__0;
        IData/*31:0*/ __Vdly__VgaStandaloneWrapper__DOT__vga__DOT__ctrlReg;
        IData/*31:0*/ __Vdlyvval__VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem__v0;
        IData/*31:0*/ __VactIterCount;
        VlUnpacked<IData/*31:0*/, 6144> VgaStandaloneWrapper__DOT__vga__DOT__framebuffer__DOT__mem;
        VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    VVgaStandaloneWrapper__Syms* const vlSymsp;

    // CONSTRUCTORS
    VVgaStandaloneWrapper___024root(VVgaStandaloneWrapper__Syms* symsp, const char* v__name);
    ~VVgaStandaloneWrapper___024root();
    VL_UNCOPYABLE(VVgaStandaloneWrapper___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
