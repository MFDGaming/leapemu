#include <stdlib.h>

#include "aux_registers.h"
#include "cpu.h"

#define IC_CTRL_STATUS_BIT (1 << 3)
#define IC_CTRL_ADDR_DEBUG_TYPE (1 << 5)

uint32_t arc_aux_reg_read_default(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return reg_map->regs[reg_id].val;
}

void arc_aux_reg_write_default(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id, uint32_t reg_val) {
    reg_map->regs[reg_id].val = reg_val;
}

uint32_t arc_aux_reg_read_status(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    uint32_t pc32 = reg_map->regs[ARC_REG_PC32].val;
    uint32_t status32 = reg_map->regs[ARC_REG_STATUS32].val;
    uint32_t status = ((pc32 >> 2) & 0xffffff);
    status |= (status32 & 7) << 24;
    status |= ((status32 >> 8) & 15) << 27;
    return status;
}

void arc_aux_reg_write_ic_ivic(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id, uint32_t reg_val) {
    arc_cache_invalidate(&cpu->i_cache, &cpu->memory_map, reg_val, 0);
}

void arc_aux_reg_write_ic_lil(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id, uint32_t reg_val) {
    if (arc_cache_invalidate_line(&cpu->i_cache, &cpu->memory_map, reg_val, 0) == ARC_CACHE_STATUS_HIT) {
        reg_map->regs[ARC_REG_IC_CTRL].val |= IC_CTRL_STATUS_BIT;
    } else {
        reg_map->regs[ARC_REG_IC_CTRL].val &= ~IC_CTRL_STATUS_BIT;
    }
}

void arc_aux_reg_write_ic_ivil(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id, uint32_t reg_val) {
    if (arc_cache_lock(&cpu->i_cache, &cpu->memory_map, reg_val, 0) != ARC_CACHE_STATUS_ERROR) {
        reg_map->regs[ARC_REG_IC_CTRL].val |= IC_CTRL_STATUS_BIT;
    } else {
        reg_map->regs[ARC_REG_IC_CTRL].val &= ~IC_CTRL_STATUS_BIT;
    }
}

void arc_aux_reg_write_ic_ram_addr(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id, uint32_t reg_val) {
    uint32_t tag_way = reg_val >> ARC_ADDR_TAG_WAY;
    uint32_t idx = (reg_val >> ARC_ADDR_IDX) & (ARC_CACHE_SETS - 1);
    uint32_t off = (reg_val & (ARC_CACHE_LINE_SIZE - 1)) & ~3;
    if (reg_map->regs[ARC_REG_IC_CTRL].val & IC_CTRL_ADDR_DEBUG_TYPE) {
        arc_cache_line_t line = cpu->i_cache.lines[idx][tag_way & (ARC_CACHE_WAYS - 1)];
        reg_map->regs[ARC_REG_IC_TAG].val |= (line.tag << ARC_ADDR_TAG_WAY) | ((line.locked & 1) << 1) | (line.valid & 1);
    } else {
        
    }
}

uint32_t arc_aux_reg_read_identity(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x0d010112;
}

uint32_t arc_aux_reg_read_vbfdw_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000000;
}

uint32_t arc_aux_reg_read_ext_arith_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000001;
}

uint32_t arc_aux_reg_read_dataspace(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000000a;
}

uint32_t arc_aux_reg_read_memsubsys(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000001;
}

uint32_t arc_aux_reg_read_vecbase_ac_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000001;
}

uint32_t arc_aux_reg_read_p_base_addr(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00fc0001;
}

uint32_t arc_aux_reg_read_d_cache_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00006201;
}

uint32_t arc_aux_reg_read_madi_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000000;
}

uint32_t arc_aux_reg_read_ldstram_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000000;
}

uint32_t arc_aux_reg_read_timer_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000302;
}

uint32_t arc_aux_reg_read_ap_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000000;
}

uint32_t arc_aux_reg_read_i_cache_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00016401;
}

uint32_t arc_aux_reg_read_addsub_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000000;
}

uint32_t arc_aux_reg_read_dspram_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00001203;
}

uint32_t arc_aux_reg_read_mac_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000203;
}

uint32_t arc_aux_reg_read_multiply_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000001;
}

uint32_t arc_aux_reg_read_swap_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000001;
}

uint32_t arc_aux_reg_read_norm_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000002;
}

uint32_t arc_aux_reg_read_minmax_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000000;
}

uint32_t arc_aux_reg_read_barrel_build(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id) {
    return 0x00000002;
}

void arc_aux_reg_map_init(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map) {
#define __SME(RI, R, W) ({ \
    reg_map->regs[RI].read = R; \
    reg_map->regs[RI].write = W; \
})
    __SME(ARC_REG_STATUS, arc_aux_reg_read_status, NULL);
    __SME(ARC_REG_SEMAPHORE, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_LP_START, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_LP_END, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_IDENTITY, arc_aux_reg_read_identity, NULL);
    __SME(ARC_REG_DEBUG, arc_aux_reg_read_default, NULL);
    __SME(ARC_REG_PC32, arc_aux_reg_read_default, NULL);
    __SME(ARC_REG_STATUS32, arc_aux_reg_read_default, NULL);
    __SME(ARC_REG_STATUS32_L1, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_STATUS32_L2, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_IC_IVIC, NULL, arc_aux_reg_write_ic_ivic);
    __SME(ARC_REG_IC_CTRL, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MULHI, NULL, arc_aux_reg_write_default);
    __SME(ARC_REG_IC_LIL, NULL, arc_aux_reg_write_ic_lil);
    __SME(ARC_REG_IC_IVIL, NULL, arc_aux_reg_write_ic_ivil);
    __SME(ARC_REG_IC_RAM_ADDR, arc_aux_reg_read_default, arc_aux_reg_write_ic_ram_addr);
    __SME(ARC_REG_IC_TAG, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_IC_WP, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_IC_DATA, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_SRAM_SEQ, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_COUNT0, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_CONTROL0, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_LIMIT0, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_PCPORT, NULL, arc_aux_reg_write_default);
    __SME(ARC_REG_INT_VECTOR_BASE, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AUX_MACMODE, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AUX_LSP_NEWVAL, NULL, arc_aux_reg_write_default);
    __SME(ARC_REG_AUX_IRQ_LV12, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AUX_XMAC0, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AUX_XMAC1, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AUX_XMAC2, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_IVDC, NULL, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_CTRL, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_LDL, NULL, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_IVDL, NULL, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_FLSH, NULL, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_FLDL, NULL, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_RAM_ADDR, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_TAG, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_WP, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_DC_DATA, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_VBFDW_BUILD, arc_aux_reg_read_vbfdw_build, NULL);
    __SME(ARC_REG_EXT_ARITH_BUILD, arc_aux_reg_read_ext_arith_build, NULL);
    __SME(ARC_REG_DATASPACE, arc_aux_reg_read_dataspace, NULL);
    __SME(ARC_REG_MEMSUBSYS, arc_aux_reg_read_memsubsys, NULL);
    __SME(ARC_REG_VECBASE_AC_BUILD, arc_aux_reg_read_vecbase_ac_build, NULL);
    __SME(ARC_REG_P_BASE_ADDR, arc_aux_reg_read_p_base_addr, NULL);
    __SME(ARC_REG_D_CACHE_BUILD, arc_aux_reg_read_d_cache_build, NULL);
    __SME(ARC_REG_MADI_BUILD, arc_aux_reg_read_madi_build, NULL);
    __SME(ARC_REG_TIMER_BUILD, arc_aux_reg_read_timer_build, NULL);
    __SME(ARC_REG_AP_BUILD, arc_aux_reg_read_ap_build, NULL);
    __SME(ARC_REG_I_CACHE_BUILD, arc_aux_reg_read_default, NULL);
    __SME(ARC_REG_ADDSUB_BUILD, arc_aux_reg_read_i_cache_build, NULL);
    __SME(ARC_REG_DSPRAM_BUILD, arc_aux_reg_read_dspram_build, NULL);
    __SME(ARC_REG_MAC_BUILD, arc_aux_reg_read_mac_build, NULL);
    __SME(ARC_REG_MULTIPLY_BUILD, arc_aux_reg_read_multiply_build, NULL);
    __SME(ARC_REG_SWAP_BUILD, arc_aux_reg_read_swap_build, NULL);
    __SME(ARC_REG_NORM_BUILD, arc_aux_reg_read_norm_build, NULL);
    __SME(ARC_REG_MINMAX_BUILD, arc_aux_reg_read_minmax_build, NULL);
    __SME(ARC_REG_BARREL_BUILD, arc_aux_reg_read_barrel_build, NULL);
    __SME(ARC_REG_AX0, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AX1, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AX2, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AX3, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AY0, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AY1, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AY2, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AY3, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MX00, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MX01, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MX10, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MX11, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MX20, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MX21, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MX30, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MX31, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MY00, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MY01, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MY10, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MY11, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MY20, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MY21, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MY30, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_MY31, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_XYCONFIG, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_BURSTSYS, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_BURSTXYM, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_BURSTSZ, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_BURSTVAL, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_COUNT1, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_CONTROL1, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_LIMIT1, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AUX_IRQ_LEV, arc_aux_reg_read_default, arc_aux_reg_write_default);
    __SME(ARC_REG_AUX_IRQ_HINT, arc_aux_reg_read_default, arc_aux_reg_write_default);
#undef __SME
}
