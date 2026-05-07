#ifndef LEAPEMU_LEAPSTER_H
#define LEAPEMU_LEAPSTER_H

#include "cpu/cpu.h"

typedef struct {
    arc_cpu_t cpu;
    uint8_t ram[0x1000000];
} leapster_t;

#endif