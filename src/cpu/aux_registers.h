#ifndef LEAPEMU_CPU_AUX_REGISTERS_H
#define LEAPEMU_CPU_AUX_REGISTERS_H

#include <stdint.h>
#include "registers.h"

typedef struct arc_cpu_t;

typedef uint32_t (*arc_aux_reg_read_t)(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id);

typedef void (*arc_aux_reg_write_t)(arc_cpu_t *cpu, arc_aux_reg_map_t *reg_map, uint32_t reg_id, uint32_t reg_val);

typedef struct {
    uint32_t val;
    arc_aux_reg_read_t read;
    arc_aux_reg_write_t write;
} arc_aux_reg_t;

typedef struct {
    arc_aux_reg_t regs[_ARC_AUX_REG_MAX];
} arc_aux_reg_map_t;

void arc_aux_reg_map_init(arc_aux_reg_map_t *reg_map);

#endif