#include <string.h>

#include "cache.h"
#include "memory.h"

uint32_t arc_cache_read(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint8_t *val, uint32_t val_size) {
    uint32_t tag, idx, off, i, lru, svi;

    if (!val || !cache || !memory_map || val_size > 4 || val_size == 3 || val_size == 0) {
        return ARC_CACHE_STATUS_ERROR;
    }

    addr &= ~(val_size - 1);

    if (arc_memory_map_check(memory_map, addr, val_size) == ARC_MEMORY_MAP_STATUS_FAILED) {
        return ARC_CACHE_STATUS_ERROR;
    }
    
    tag = addr >> ARC_ADDR_TAG_WAY;
    idx = (addr >> ARC_ADDR_IDX) & (ARC_CACHE_SETS - 1);
    off = addr & (ARC_CACHE_LINE_SIZE - 1);

    for (i = 0; i < ARC_CACHE_WAYS; ++i) {
        if (cache->lines[idx][i].tag == tag && cache->lines[idx][i].valid) {
            ++cache->lines[idx][i].lru;
            memcpy(val, &cache->lines[idx][i].data[off], val_size);
            return ARC_CACHE_STATUS_HIT;
        }
    }

    lru = ~0;
    svi = ARC_CACHE_WAYS;
    for (i = 0; i < ARC_CACHE_WAYS; ++i) {
        if (cache->lines[idx][i].locked) {
            continue;
        }
        if (!cache->lines[idx][i].valid) {
            svi = i;
            break;
        }
        if (cache->lines[idx][i].lru <= lru) {
            svi = i;
            lru = cache->lines[idx][i].lru;
        }
    }

    if (svi == ARC_CACHE_WAYS) {
        arc_memory_map_read(memory_map, addr, val, val_size);
        return ARC_CACHE_STATUS_BYPASS;
    }

    if (cache->lines[idx][svi].valid && cache->lines[idx][svi].dirty) {
        uint32_t evict_addr = (cache->lines[idx][svi].tag << ARC_ADDR_TAG_WAY) | (idx << ARC_ADDR_IDX);
        arc_memory_map_write(memory_map, evict_addr, cache->lines[idx][svi].data, ARC_CACHE_LINE_SIZE);
    }

    arc_memory_map_read(memory_map, addr - off, cache->lines[idx][svi].data, ARC_CACHE_LINE_SIZE);
    cache->lines[idx][svi].tag = tag;
    cache->lines[idx][svi].valid = 1;
    cache->lines[idx][svi].locked = 0;
    cache->lines[idx][svi].lru = 1;
    cache->lines[idx][svi].dirty = 0;
    memcpy(val, &cache->lines[idx][svi].data[off], val_size);
    return ARC_CACHE_STATUS_MISS;
}

uint32_t arc_cache_write(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint8_t *val, uint32_t val_size) {
    uint32_t tag, idx, off, i, lru, svi;

    if (!val || !cache || !memory_map || val_size > 4 || val_size == 3 || val_size == 0) {
        return ARC_CACHE_STATUS_ERROR;
    }

    addr &= ~(val_size - 1);

    if (arc_memory_map_check(memory_map, addr, val_size) == ARC_MEMORY_MAP_STATUS_FAILED) {
        return ARC_CACHE_STATUS_ERROR;
    }
    
    tag = addr >> ARC_ADDR_TAG_WAY;
    idx = (addr >> ARC_ADDR_IDX) & (ARC_CACHE_SETS - 1);
    off = addr & (ARC_CACHE_LINE_SIZE - 1);

    for (i = 0; i < ARC_CACHE_WAYS; ++i) {
        if (cache->lines[idx][i].tag == tag && cache->lines[idx][i].valid) {
            ++cache->lines[idx][i].lru;
            cache->lines[idx][i].dirty = 1;
            memcpy(&cache->lines[idx][i].data[off], val, val_size);
            return ARC_CACHE_STATUS_HIT;
        }
    }

    lru = ~0;
    svi = ARC_CACHE_WAYS;
    for (i = 0; i < ARC_CACHE_WAYS; ++i) {
        if (cache->lines[idx][i].locked) {
            continue;
        }
        if (!cache->lines[idx][i].valid) {
            svi = i;
            break;
        }
        if (cache->lines[idx][i].lru <= lru) {
            svi = i;
            lru = cache->lines[idx][i].lru;
        }
    }

    if (svi == ARC_CACHE_WAYS) {
        arc_memory_map_write(memory_map, addr, val, val_size);
        return ARC_CACHE_STATUS_BYPASS;
    }

    if (cache->lines[idx][svi].valid && cache->lines[idx][svi].dirty) {
        uint32_t evict_addr = (cache->lines[idx][svi].tag << ARC_ADDR_TAG_WAY) | (idx << ARC_ADDR_IDX);
        arc_memory_map_write(memory_map, evict_addr, cache->lines[idx][svi].data, ARC_CACHE_LINE_SIZE);
    }

    arc_memory_map_read(memory_map, addr - off, cache->lines[idx][svi].data, ARC_CACHE_LINE_SIZE);
    cache->lines[idx][svi].tag = tag;
    cache->lines[idx][svi].valid = 1;
    cache->lines[idx][svi].locked = 0;
    cache->lines[idx][svi].lru = 1;
    cache->lines[idx][svi].dirty = 1;
    memcpy(&cache->lines[idx][svi].data[off], val, val_size);
    return ARC_CACHE_STATUS_MISS;
}

uint32_t arc_cache_invalidate_line(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint32_t do_flush) {
    uint32_t tag, idx, i;
    
    tag = addr >> ARC_ADDR_TAG_WAY;
    idx = (addr >> ARC_ADDR_IDX) & (ARC_CACHE_SETS - 1);

    for (i = 0; i < ARC_CACHE_WAYS; ++i) {
        if (cache->lines[idx][i].tag == tag && cache->lines[idx][i].valid) {
            if (do_flush && cache->lines[idx][i].dirty) {
                uint32_t evict_addr = (cache->lines[idx][i].tag << ARC_ADDR_TAG_WAY) | (idx << ARC_ADDR_IDX);
                arc_memory_map_write(memory_map, evict_addr, cache->lines[idx][i].data, ARC_CACHE_LINE_SIZE);
                cache->lines[idx][i].dirty = 0;
            }
            cache->lines[idx][i].valid = 0;
            cache->lines[idx][i].locked = 0;
            return ARC_CACHE_STATUS_HIT;
        }
    }
    return ARC_CACHE_STATUS_MISS;
}

void arc_cache_invalidate(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint32_t do_flush) {
    uint32_t tag, idx, i;
    
    tag = addr >> ARC_ADDR_TAG_WAY;
    idx = (addr >> ARC_ADDR_IDX) & (ARC_CACHE_SETS - 1);

    for (i = 0; i < ARC_CACHE_WAYS; ++i) {
        if (cache->lines[idx][i].tag == tag && cache->lines[idx][i].valid) {
            if (do_flush && cache->lines[idx][i].dirty) {
                uint32_t evict_addr = (cache->lines[idx][i].tag << ARC_ADDR_TAG_WAY) | (idx << ARC_ADDR_IDX);
                arc_memory_map_write(memory_map, evict_addr, cache->lines[idx][i].data, ARC_CACHE_LINE_SIZE);
                cache->lines[idx][i].dirty = 0;
            }
            cache->lines[idx][i].valid = 0;
            cache->lines[idx][i].locked = 0;
        }
    }
}

uint32_t arc_cache_lock(arc_cache_t *cache, arc_memory_map_t *memory_map, uint32_t addr, uint8_t do_flush) {
    uint32_t tag, idx, i, lru, svi;

    addr &= ~(ARC_CACHE_LINE_SIZE - 1);
    
    tag = addr >> ARC_ADDR_TAG_WAY;
    idx = (addr >> ARC_ADDR_IDX) & (ARC_CACHE_SETS - 1);

    for (i = 0; i < ARC_CACHE_WAYS; ++i) {
        if (cache->lines[idx][i].tag == tag && cache->lines[idx][i].valid) {
            if (cache->lines[idx][i].dirty) {
                if (do_flush) {
                    uint32_t evict_addr = (cache->lines[idx][i].tag << ARC_ADDR_TAG_WAY) | (idx << ARC_ADDR_IDX);
                    arc_memory_map_write(memory_map, evict_addr, cache->lines[idx][i].data, ARC_CACHE_LINE_SIZE);
                    cache->lines[idx][i].dirty = 0;
                }
            } else {
                arc_memory_map_read(memory_map, addr, cache->lines[idx][i].data, ARC_CACHE_LINE_SIZE);
            }
            cache->lines[idx][i].locked = 1;
            ++cache->lines[idx][i].lru;
            return ARC_CACHE_STATUS_HIT;
        }
    }

    lru = ~0;
    svi = ARC_CACHE_WAYS;
    for (i = 0; i < ARC_CACHE_WAYS; ++i) {
        if (cache->lines[idx][i].locked) {
            continue;
        }
        if (!cache->lines[idx][i].valid) {
            svi = i;
            break;
        }
        if (cache->lines[idx][i].lru <= lru) {
            svi = i;
            lru = cache->lines[idx][i].lru;
        }
    }

    if (svi == ARC_CACHE_WAYS) {
        return ARC_CACHE_STATUS_ERROR;
    }

    arc_memory_map_read(memory_map, addr, cache->lines[idx][svi].data, ARC_CACHE_LINE_SIZE);
    cache->lines[idx][svi].tag = tag;
    cache->lines[idx][svi].valid = 1;
    cache->lines[idx][svi].locked = 1;
    cache->lines[idx][svi].lru = 1;
    cache->lines[idx][svi].dirty = 0;
    return ARC_CACHE_STATUS_MISS;
}
