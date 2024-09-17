#ifndef FLOATINGPOINT_HPP_
#define FLOATINGPOINT_HPP_

#include <cstdint>
template <uint64_t exponent, uint64_t mantissa>
class FloatingPoint {
/* Floating Point Value: Value = (-1)^{sign} * 2 ^ {e - } * 1.f*/

public:
    // Default: Initialize to Floating Point 0
    FloatingPoint();
private:
    bool sign;
    uint64_t exp_value;
    uint64_t mant_value;
};

#endif // FLOATINGPOINT_HPP_