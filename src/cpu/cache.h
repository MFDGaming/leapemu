#ifndef LEAPEMU_CPU_CACHE_H
#define LEAPEMU_CPU_CACHE_H

#include <math.h>
#include <stdint.h>

enum {
    ARC_CACHE_STATUS_HIT,
    ARC_CACHE_STATUS_MISS,
    ARC_CACHE_STATUS_BYPASS,
    ARC_CACHE_STATUS_ERROR
};

#define ARC_CACHE_SIZE 0x8000
#define ARC_CACHE_LINE_SIZE 16
#define ARC_CACHE_WAYS 4
#define ARC_CACHE_SETS ((ARC_CACHE_SIZE / ARC_CACHE_LINE_SIZE) / ARC_CACHE_WAYS)

#define ARC_ADDR_TAG_WAY 13 /* ((uint32_t)(log(ARC_CACHE_SIZE / ARC_CACHE_WAYS) / log(2))) */
#define ARC_ADDR_IDX 4 /* ((uint32_t)(log(ARC_CACHE_LINE_SIZE) / log(2))) */

typedef struct {
    uint8_t data[ARC_CACHE_LINE_SIZE];
    uint32_t tag;
    uint32_t lru;
    uint8_t valid;
    uint8_t dirty;
    uint8_t locked;
} arc_cache_line_t;

typedef struct {
    arc_cache_line_t lines[ARC_CACHE_SETS][ARC_CACHE_WAYS];
} arc_cache_t;

uint32_t arc_cache_read(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint8_t *val, uint32_t val_size);

uint32_t arc_cache_write(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint8_t *val, uint32_t val_size);

uint32_t arc_cache_invalidate_line(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint32_t do_flush);

void arc_cache_invalidate(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint32_t do_flush);

uint32_t arc_cache_lock(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint8_t do_flush);

#endif
