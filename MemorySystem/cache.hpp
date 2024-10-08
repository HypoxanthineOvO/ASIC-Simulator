#ifndef CACHE_HPP_
#define CACHE_HPP_

#include "dram.hpp"

typedef enum EvictionPolicy {
    RANDOM,
    FIFO,
    LRU,
} EvictionPolicy;

class CacheEntry {
public:

private:
    // Data
    uint32_t cache_line_size;
    std::vector<uint8_t> data;

    // Metadata
    uint32_t tag;
    bool valid;
    bool dirty;

};

class Cache {
public:
    Cache(uint32_t cache_size, uint32_t num_associativity = -1, EvictionPolicy policy = RANDOM): size(cache_size) {
        if (num_associativity == -1) {
            // Fully associative
            num_associativity = size;
        }
        num_groups = size / num_associativity;
    }
private:
    // Addressing Function


    std::shared_ptr<DRAM> dram;
    EvictionPolicy policy;

    uint32_t size;
    uint32_t cacheline_size;
    std::vector<CacheEntry> cache;
    uint32_t num_associativity;
    uint32_t num_groups;
};


#endif // CACHE_HPP_