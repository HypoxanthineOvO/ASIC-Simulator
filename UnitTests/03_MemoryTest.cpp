#include "dram.hpp"
#include <random>

int main() {
    const int max_addr = 128;

    std::shared_ptr<DRAM> dram = std::make_shared<DRAM>(max_addr); // 1KB DRAM
    for (int i = 0; i < max_addr; i++) {
        uint8_t data = dram->read_(i);
        printf("Read data at address %d: %x\n", i, data);
    }
    // Random write 100 data
    for (int i = 0; i < 10; i++) {
        uint32_t addr = rand() % max_addr;
        uint8_t data = rand() % 256;
        dram->write_(addr, data);
        printf("Write data %x at address %d\n", data, addr);
    }
    for (int i = 0; i < max_addr; i++) {
        uint8_t data = dram->read_(i);
        printf("Read data at address %d: %x\n", i, data);
    }
}