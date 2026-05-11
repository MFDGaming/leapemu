#ifndef LEAPEMU_CPU_REGISTERS_H
#define LEAPEMU_CPU_REGISTERS_H

/* Core Register Set */
enum ARC_CORE_REGS {
    /* General Purpose Registers */
    ARC_REG_R0, ARC_REG_R1, ARC_REG_R2, ARC_REG_R3,
    ARC_REG_R4, ARC_REG_R5, ARC_REG_R6, ARC_REG_R7,
    ARC_REG_R8, ARC_REG_R9, ARC_REG_R10, ARC_REG_R11,
    ARC_REG_R12, ARC_REG_R13, ARC_REG_R14, ARC_REG_R15,
    ARC_REG_R16, ARC_REG_R17, ARC_REG_R18, ARC_REG_R19,
    ARC_REG_R20, ARC_REG_R21, ARC_REG_R22, ARC_REG_R23,
    ARC_REG_R24, ARC_REG_R25,
    /* Pointer Registers */
    ARC_REG_GP, ARC_REG_FP, ARC_REG_SP,
    /* Link Registers */
    ARC_REG_ILINK1, ARC_REG_ILINK2, ARC_REG_BLINK,
    /* Extension Registers */
    ARC_REG_R32, ARC_REG_R33, ARC_REG_R34, ARC_REG_R35,
    ARC_REG_R36, ARC_REG_R37, ARC_REG_R38, ARC_REG_R39,
    ARC_REG_R40, ARC_REG_R41, ARC_REG_R42, ARC_REG_R43,
    ARC_REG_R44, ARC_REG_R45, ARC_REG_R46, ARC_REG_R47,
    ARC_REG_R48, ARC_REG_R49, ARC_REG_R50, ARC_REG_R51,
    ARC_REG_R52, ARC_REG_R53, ARC_REG_R54, ARC_REG_R55,
    ARC_REG_R56, ARC_REG_R57, ARC_REG_R58, ARC_REG_R59,
    /* Other Registers */
    ARC_REG_LP_COUNT, ARC_REG_RESERVED, ARC_REG_LONG_IMM, ARC_REG_PCL
};

/* Multiply Core Registers */
#define ARC_REG_MLO ARC_REG_R57
#define ARC_REG_MMID ARC_REG_R58
#define ARC_REG_MHI ARC_REG_R59

/* XY Memory Core Registers */
#define ARC_REG_X0_U0 ARC_REG_R32
#define ARC_REG_X0_U1 ARC_REG_R33
#define ARC_REG_X1_U0 ARC_REG_R34
#define ARC_REG_X1_U1 ARC_REG_R35
#define ARC_REG_X2_U0 ARC_REG_R36
#define ARC_REG_X2_U1 ARC_REG_R37
#define ARC_REG_X3_U0 ARC_REG_R38
#define ARC_REG_X3_U1 ARC_REG_R39
#define ARC_REG_Y0_U0 ARC_REG_R40
#define ARC_REG_Y0_U1 ARC_REG_R41
#define ARC_REG_Y1_U0 ARC_REG_R42
#define ARC_REG_Y1_U1 ARC_REG_R43
#define ARC_REG_Y2_U0 ARC_REG_R44
#define ARC_REG_Y2_U1 ARC_REG_R45
#define ARC_REG_Y3_U0 ARC_REG_R46
#define ARC_REG_Y3_U1 ARC_REG_R47
#define ARC_REG_X0_NU ARC_REG_R48
#define ARC_REG_X1_NU ARC_REG_R49
#define ARC_REG_X2_NU ARC_REG_R50
#define ARC_REG_X3_NU ARC_REG_R51
#define ARC_REG_Y0_NU ARC_REG_R52
#define ARC_REG_Y1_NU ARC_REG_R53
#define ARC_REG_Y2_NU ARC_REG_R54
#define ARC_REG_Y3_NU ARC_REG_R55
#define ARC_REG_ACC0 ARC_REG_R56
#define ARC_REG_ACC1 ARC_REG_R57

/* XMAC Core Registers */
#define ARC_REG_XMAC0 ARC_REG_R42
#define ARC_REG_XMAC1 ARC_REG_R43

/* Auxiliary Register Set */
enum ARC_AUX_REGS {
    ARC_REG_STATUS, /* Status */
    ARC_REG_SEMAPHORE, /* Host Semaphore Address */
    ARC_REG_LP_START, /* Loop Start Address */
    ARC_REG_LP_END, /* Loop End Address */
    ARC_REG_IDENTITY, /* ARC Identification */
    ARC_REG_DEBUG, /* Debug */
    ARC_REG_PC32, /* 32-Bit Program Counter */
    ARC_REG_STATUS32 = 0x0a, /* 32-Bit Status */
    ARC_REG_STATUS32_L1, /* 32-Bit Status (No Level 1 Exceptions) */
    ARC_REG_STATUS32_L2, /* 32-Bit Status (No Level 2 Exceptions) */
    ARC_REG_IC_IVIC = 0x10, /* Instruction Cache: Invalidate Instruction Cache */
    ARC_REG_IC_CTRL, /* Instruction Cache: Control */
    ARC_REG_MULHI, /* High Part Of Multiply */
    ARC_REG_IC_LIL, /* Instruction Cache: Lock Instruction Line */
    ARC_REG_IC_IVIL = 0x19, /* Instruction Cache: Invalidate Instruction Line */
    ARC_REG_IC_RAM_ADDR, /* Instruction Cache: RAM Address */
    ARC_REG_IC_TAG, /* Instruction Cache: Tag */
    ARC_REG_IC_WP, /* Instruction Cache: Way Pointer */
    ARC_REG_IC_DATA, /* Instruction Cache: Data */
    ARC_REG_SRAM_SEQ = 0x20, /* SRAM Sequencer Mode Control */
    ARC_REG_COUNT0, /* Timer 0 Count */
    ARC_REG_CONTROL0, /* Timer 0 Control */
    ARC_REG_LIMIT0, /* Timer 0 Limit */
    ARC_REG_PCPORT, /* Control For PC_SEL Line */
    ARC_REG_INT_VECTOR_BASE = 0x25, /* Interrupt Vector Base Address */
    ARC_REG_AUX_MACMODE = 0x41, /* Multiply - Accumulate Mode */
    ARC_REG_AUX_LSP_NEWVAL, /* Low 32-Bit Register Product */
    ARC_REG_AUX_IRQ_LV12, /* Stick Flags For Interrupt Levels */
    ARC_REG_AUX_XMAC0, /* Accumulator Extended Product */
    ARC_REG_AUX_XMAC1, /* Accumulator Most Significant Part */
    ARC_REG_AUX_XMAC2, /* Accumulator Least Significant Part */
    ARC_REG_DC_IVDC, /* Data Cache: Invalidate Data Cache */
    ARC_REG_DC_CTRL, /* Data Cache: Control */
    ARC_REG_DC_LDL, /* Data Cache: Lock Data Line */
    ARC_REG_DC_IVDL, /* Data Cache: Invalidate Data Line */
    ARC_REG_DC_FLSH, /* Data Cache: Flush */
    ARC_REG_DC_FLDL, /* Data Cache: Flush Data Line */
    ARC_REG_DC_RAM_ADDR = 0x58, /* Data Cache: RAM Address */
    ARC_REG_DC_TAG, /* Data Cache: Tag */
    ARC_REG_DC_WP, /* Data Cache: Way Pointer */
    ARC_REG_DC_DATA, /* Data Cache: Data */
    ARC_REG_VBFDW_BUILD = 0x64, /* Build: VBFDW */
    ARC_REG_EXT_ARITH_BUILD, /* Build: Extended Arithmetic */
    ARC_REG_DATASPACE, /* Build: Dataspace */
    ARC_REG_MEMSUBSYS, /* Build: Memory subsystem */
    ARC_REG_VECBASE_AC_BUILD, /* Build: ARCompact Interrupt Vector Base Address */
    ARC_REG_P_BASE_ADDR, /* Peripheral Base Address */
    ARC_REG_D_CACHE_BUILD = 0x72, /* Build: Data Cache */
    ARC_REG_MADI_BUILD, /* Build: Multiple ARC Debug Interface */
    ARC_REG_LDSTRAM_BUILD, /* Build: LD/ST RAM */
    ARC_REG_TIMER_BUILD, /* Build: Timer */
    ARC_REG_AP_BUILD, /* Build: Action Points */
    ARC_REG_I_CACHE_BUILD, /* Build: Instruction Cache */
    ARC_REG_ADDSUB_BUILD, /* Build: Saturated Add/Sub */
    ARC_REG_DSPRAM_BUILD, /* Build: Scratch RAM & XY Memory */
    ARC_REG_MAC_BUILD, /* Build: MUL/MAC */
    ARC_REG_MULTIPLY_BUILD, /* Build: Multiply */
    ARC_REG_SWAP_BUILD, /* Build: Swap */
    ARC_REG_NORM_BUILD, /* Build: Normalize */
    ARC_REG_MINMAX_BUILD, /* Build: Min/Max */
    ARC_REG_BARREL_BUILD, /* Build: Barrel Shift */
    ARC_REG_AX0, /* Address For X0 */
    ARC_REG_AX1, /* Address For X1 */
    ARC_REG_AX2, /* Address For X2 */
    ARC_REG_AX3,/* Address For X3 */
    ARC_REG_AY0, /* Address For Y0 */
    ARC_REG_AY1, /* Address For Y1 */
    ARC_REG_AY2, /* Address For Y2 */
    ARC_REG_AY3, /* Address For Y3 */
    ARC_REG_MX00, /* Modifier 1 For AX0 */
    ARC_REG_MX01, /* Modifier 2 For AX0 */
    ARC_REG_MX10, /* Modifier 1 For AX1 */
    ARC_REG_MX11, /* Modifier 2 For AX1 */
    ARC_REG_MX20, /* Modifier 1 For AX2 */
    ARC_REG_MX21, /* Modifier 2 For AX2 */
    ARC_REG_MX30, /* Modifier 1 For AX3 */
    ARC_REG_MX31, /* Modifier 2 For AX3 */
    ARC_REG_MY00, /* Modifier 1 For AY0 */
    ARC_REG_MY01, /* Modifier 2 For AY0 */
    ARC_REG_MY10, /* Modifier 1 For AY1 */
    ARC_REG_MY11, /* Modifier 2 For AY1 */
    ARC_REG_MY20, /* Modifier 1 For AY2 */
    ARC_REG_MY21, /* Modifier 2 For AY2 */
    ARC_REG_MY30, /* Modifier 1 For AY3 */
    ARC_REG_MY31, /* Modifier 2 For AY3 */
    ARC_REG_XYCONFIG, /* XY Configuration */
    ARC_REG_BURSTSYS, /* Burst System Address */
    ARC_REG_BURSTXYM, /* Burst XY Memory Address */
    ARC_REG_BURSTSZ, /* Burst Size And Destination */
    ARC_REG_BURSTVAL, /* Burst Fill Value */
    ARC_REG_COUNT1 = 0x100, /* Timer 1 Count */
    ARC_REG_CONTROL1, /* Timer 1 Control */
    ARC_REG_LIMIT1, /* Timer 1 Limit */
    ARC_REG_AUX_IRQ_LEV = 0x200, /* Level 1,2 Programming */
    ARC_REG_AUX_IRQ_HINT /* Software Interrupt Trigger Location */
};

/* Note: Aux register data wraps around every 65536 registers. */
#define ARC_AUX_REG(x) (((x % 65536) >= 516) ? ARC_REG_IDENTITY : (x % 65536))

#endif
