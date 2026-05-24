#include <stdlib.h>
#include <string.h>

#include "memory.h"

void arc_memory_map_init(arc_memory_map_t *memory_map) {
    memory_map->entries[ARC_MEMORY_MAP_MAIN].data = memory_map->main;
    memory_map->entries[ARC_MEMORY_MAP_MAIN].len = sizeof(memory_map->main);
    memory_map->entries[ARC_MEMORY_MAP_MAIN].addr = 0x3c000000;
    memory_map->entries[ARC_MEMORY_MAP_MAIN].read_callback = NULL;
    memory_map->entries[ARC_MEMORY_MAP_MAIN].write_callback = NULL;
}

uint32_t arc_memory_map_check(arc_memory_map_t *memory_map, uint32_t addr, uint32_t len) {
    int i;
    if (len) {
        for (i = 0; i < ARC_MEMORY_MAP_ENTRY_COUNT; ++i) {
            arc_memory_map_entry_t *entry = &memory_map->entries[i];

            if (len <= entry->len && addr >= entry->addr && (addr + len) <= (entry->addr + entry->len)) {
                return ARC_MEMORY_MAP_STATUS_SUCCESS;
            }
        }
    }
    return ARC_MEMORY_MAP_STATUS_FAILED;
}

uint32_t arc_memory_map_read(arc_memory_map_t *memory_map, uint32_t addr, uint8_t *val, uint32_t val_size) {
    int i;
    for (i = 0; i < ARC_MEMORY_MAP_ENTRY_COUNT; ++i) {
        arc_memory_map_entry_t *entry = &memory_map->entries[i];

        if (val_size > entry->len || addr < entry->addr || (addr + val_size) > (entry->addr + entry->len)) {
            continue;
        }

        if (entry->read_callback) {
            return entry->read_callback(entry, addr, val, val_size);
        }
        if (!entry->data) {
            ARC_MEMORY_MAP_STATUS_FAILED;
        }
        memcpy(val, &entry->data[addr - entry->addr], val_size);
        return ARC_MEMORY_MAP_STATUS_SUCCESS;
    }
    return ARC_MEMORY_MAP_STATUS_FAILED;
}

uint32_t arc_memory_map_write(arc_memory_map_t *memory_map, uint32_t addr, uint8_t *val, uint32_t val_size) {
    int i;
    for (i = 0; i < ARC_MEMORY_MAP_ENTRY_COUNT; ++i) {
        arc_memory_map_entry_t *entry = &memory_map->entries[i];

        if (val_size > entry->len || addr < entry->addr || (addr + val_size) > (entry->addr + entry->len)) {
            continue;
        }

        if (entry->write_callback) {
            return entry->write_callback(entry, addr, val, val_size);
        }

        if (!entry->data) {
            ARC_MEMORY_MAP_STATUS_FAILED;
        }
        memcpy(&entry->data[addr - entry->addr], val, val_size);
        return ARC_MEMORY_MAP_STATUS_SUCCESS;
    }
    return ARC_MEMORY_MAP_STATUS_FAILED;
}
