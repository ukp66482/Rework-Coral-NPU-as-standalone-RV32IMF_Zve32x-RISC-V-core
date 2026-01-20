// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "VVgaStandaloneWrapper__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

VVgaStandaloneWrapper::VVgaStandaloneWrapper(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new VVgaStandaloneWrapper__Syms(contextp(), _vcname__, this)}
    , clock{vlSymsp->TOP.clock}
    , io_pixClock{vlSymsp->TOP.io_pixClock}
    , reset{vlSymsp->TOP.reset}
    , io_mmio_wen{vlSymsp->TOP.io_mmio_wen}
    , io_hsync{vlSymsp->TOP.io_hsync}
    , io_vsync{vlSymsp->TOP.io_vsync}
    , io_rgb{vlSymsp->TOP.io_rgb}
    , io_activevideo{vlSymsp->TOP.io_activevideo}
    , io_intr{vlSymsp->TOP.io_intr}
    , io_x_pos{vlSymsp->TOP.io_x_pos}
    , io_y_pos{vlSymsp->TOP.io_y_pos}
    , io_mmio_addr{vlSymsp->TOP.io_mmio_addr}
    , io_mmio_wdata{vlSymsp->TOP.io_mmio_wdata}
    , io_mmio_rdata{vlSymsp->TOP.io_mmio_rdata}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

VVgaStandaloneWrapper::VVgaStandaloneWrapper(const char* _vcname__)
    : VVgaStandaloneWrapper(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

VVgaStandaloneWrapper::~VVgaStandaloneWrapper() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void VVgaStandaloneWrapper___024root___eval_debug_assertions(VVgaStandaloneWrapper___024root* vlSelf);
#endif  // VL_DEBUG
void VVgaStandaloneWrapper___024root___eval_static(VVgaStandaloneWrapper___024root* vlSelf);
void VVgaStandaloneWrapper___024root___eval_initial(VVgaStandaloneWrapper___024root* vlSelf);
void VVgaStandaloneWrapper___024root___eval_settle(VVgaStandaloneWrapper___024root* vlSelf);
void VVgaStandaloneWrapper___024root___eval(VVgaStandaloneWrapper___024root* vlSelf);

void VVgaStandaloneWrapper::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VVgaStandaloneWrapper::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    VVgaStandaloneWrapper___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        VVgaStandaloneWrapper___024root___eval_static(&(vlSymsp->TOP));
        VVgaStandaloneWrapper___024root___eval_initial(&(vlSymsp->TOP));
        VVgaStandaloneWrapper___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    VVgaStandaloneWrapper___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool VVgaStandaloneWrapper::eventsPending() { return false; }

uint64_t VVgaStandaloneWrapper::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* VVgaStandaloneWrapper::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void VVgaStandaloneWrapper___024root___eval_final(VVgaStandaloneWrapper___024root* vlSelf);

VL_ATTR_COLD void VVgaStandaloneWrapper::final() {
    VVgaStandaloneWrapper___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* VVgaStandaloneWrapper::hierName() const { return vlSymsp->name(); }
const char* VVgaStandaloneWrapper::modelName() const { return "VVgaStandaloneWrapper"; }
unsigned VVgaStandaloneWrapper::threads() const { return 1; }
void VVgaStandaloneWrapper::prepareClone() const { contextp()->prepareClone(); }
void VVgaStandaloneWrapper::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> VVgaStandaloneWrapper::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void VVgaStandaloneWrapper___024root__trace_decl_types(VerilatedVcd* tracep);

void VVgaStandaloneWrapper___024root__trace_init_top(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    VVgaStandaloneWrapper___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VVgaStandaloneWrapper___024root*>(voidSelf);
    VVgaStandaloneWrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    VVgaStandaloneWrapper___024root__trace_decl_types(tracep);
    VVgaStandaloneWrapper___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void VVgaStandaloneWrapper___024root__trace_register(VVgaStandaloneWrapper___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void VVgaStandaloneWrapper::trace(VerilatedVcdC* tfp, int levels, int options) {
    if (tfp->isOpen()) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'VVgaStandaloneWrapper::trace()' shall not be called after 'VerilatedVcdC::open()'.");
    }
    if (false && levels && options) {}  // Prevent unused
    tfp->spTrace()->addModel(this);
    tfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    VVgaStandaloneWrapper___024root__trace_register(&(vlSymsp->TOP), tfp->spTrace());
}
