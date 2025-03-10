#include "type.hpp"
#include <iostream>

int main() {
    puts("==================== Unit Test Of Types ====================");
    // Flush the buffer
    std::cout << std::flush;
    puts("1. Test Initialization of FixedPoint");
    uint64_t val = 0x40000038da100000;
    CA25 fp1(val);
    fp1.print_state();
}