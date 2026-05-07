#ifndef LEAPEMU_CPU_CPU_H
#define LEAPEMU_CPU_CPU_H

#include <stdint.h>

typedef struct {
    uint32_t regs[64];
    uint32_t aux_regs[516];
    uint8_t d_cache[0x8000];
    uint8_t i_cache[0x8000];
    uint8_t x_mem[0x800];
    uint8_t y_mem[0x800];
} arc_cpu_t;

#endif
