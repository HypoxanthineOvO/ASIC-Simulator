#ifndef TYPE_HPP_
#define TYPE_HPP_
#include <cmath>
#include <iostream>

/* Fixed Point Datatype */
#include "FixedPoint.hpp"

/* Floating Point Datatype */
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

using Half = FloatingPoint<5, 10>;
using Float = FloatingPoint<8, 23>;
using Double = FloatingPoint<11, 52>;






#endif // TYPE_HPP_