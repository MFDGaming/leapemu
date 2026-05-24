#ifndef LEAPEMU_CPU_CPU_H
#define LEAPEMU_CPU_CPU_H

#include <stdint.h>

#include "aux_registers.h"
#include "cache.h"
#include "memory.h"

typedef struct {
    uint32_t regs[_ARC_REG_MAX];
    arc_aux_reg_t aux_regs[_ARC_AUX_REG_MAX];
    arc_cache_t d_cache;
    arc_cache_t i_cache;
    uint8_t x_mem[0x800];
    uint8_t y_mem[0x800];
    arc_memory_map_t memory_map;
} arc_cpu_t;

#endif
