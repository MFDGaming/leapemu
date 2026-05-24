#ifndef LEAPEMU_CPU_MEMORY_H
#define LEAPEMU_CPU_MEMORY_H

#include <stdint.h>

enum {
    ARC_MEMORY_MAP_MAIN,
    ARC_MEMORY_MAP_ENTRY_COUNT
};

enum {
    ARC_MEMORY_MAP_STATUS_FAILED,
    ARC_MEMORY_MAP_STATUS_SUCCESS
};

struct _arc_memory_map_entry_t;

typedef uint32_t (*arc_memory_map_entry_callback_t)(struct _arc_memory_map_entry_t *entry, uint32_t addr, uint8_t *val, uint32_t val_size);

typedef struct _arc_memory_map_entry_t {
    uint32_t addr;
    uint32_t len;
    uint8_t *data;
    arc_memory_map_entry_callback_t read_callback;
    arc_memory_map_entry_callback_t write_callback;
} arc_memory_map_entry_t;

typedef struct {
    arc_memory_map_entry_t entries[ARC_MEMORY_MAP_ENTRY_COUNT];
    uint8_t main[0x1000000];
} arc_memory_map_t;

uint32_t arc_memory_map_check(arc_memory_map_t *memory_map, uint32_t addr, uint32_t len);

uint32_t arc_memory_map_read(arc_memory_map_t *memory_map, uint32_t addr, uint8_t *val, uint32_t val_size);

uint32_t arc_memory_map_write(arc_memory_map_t *memory_map, uint32_t addr, uint8_t *val, uint32_t val_size);

#endif