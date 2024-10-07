#ifndef DRAM_HPP_
#define DRAM_HPP_


#include <memory> // Include the header for std::shared_ptr
#include <cstdint>
#include <vector>
#include <stdexcept>

class DRAM {
public:
    DRAM(uint32_t max_addr): max_addr(max_addr), memory(std::vector<uint8_t>(max_addr, 0)),
    read_count(std::vector<uint64_t>(max_addr, 0)), write_count(std::vector<uint64_t>(max_addr, 0)) {}

    // Basic read and write operations
    uint8_t read_(uint32_t addr) {
        if (addr >= max_addr) {
            throw std::out_of_range("DRAM read out of range");
        }
        // Update statistics
        read_count[addr]++;
        return memory[addr];
    }
    void write_(uint32_t addr, uint8_t data) {
        if (addr >= max_addr) {
            throw std::out_of_range("DRAM write out of range");
        }
        // Update statistics
        write_count[addr]++;
        memory[addr] = data;
    }
    // Overload: operate 4 bytes at a time
    uint32_t read(uint32_t addr) {
        if (addr >= max_addr) {
            throw std::out_of_range("DRAM read out of range");
        }
        uint32_t base_addr = addr & 0xFFFFFFFC;
        uint32_t data = 0;
        for (int i = 0; i < 4; i++) {
            uint32_t tmp_addr = base_addr + i;
            data |= read_(tmp_addr) << (i << 3);
        }
        return data;
    }
    void write(uint32_t addr, uint32_t data) {
        if (addr >= max_addr) {
            throw std::out_of_range("DRAM write out of range");
        }
        uint32_t base_addr = addr & 0xFFFFFFFC;
        for (int i = 0; i < 4; i++) {
            uint32_t tmp_addr = base_addr + i;
            write_(tmp_addr, (data >> (i << 3)) & 0xFF);
        }
    }

private:
    /* Simulation Utils */
    uint32_t max_addr;
    std::vector<uint8_t> memory;
    /* Statistics */
    std::vector<uint64_t> read_count;
    std::vector<uint64_t> write_count;
};

#endif // DRAM_HPP_