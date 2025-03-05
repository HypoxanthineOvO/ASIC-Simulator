#ifndef FLOATINGPOINT_HPP_
#define FLOATINGPOINT_HPP_

#include <cstdint>


template <uint64_t exponent, uint64_t mantissa>
class FloatingPoint {
private:
    bool sign;
    uint64_t exponent_value;
    uint64_t exponent_length;

    uint64_t mantissa_value;
    uint64_t mantissa_length;

public:
    // Default: Initialize to Floating Point 0
    FloatingPoint();

    typedef enum STATE {
        NORMAL,
        SUBNORMAL,
        ZERO,
        INF,
        NAN,
    } State;
};

#endif // FLOATINGPOINT_HPP_