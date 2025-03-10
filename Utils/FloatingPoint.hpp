#ifndef FLOATINGPOINT_HPP_
#define FLOATINGPOINT_HPP_

#include <cstdint>
#include <string>

template <uint64_t exponent, uint64_t mantissa>
class FloatingPoint {
public:
    // Default: Initialize to Floating Point 0
    FloatingPoint();

    // Initialize with integer value
    FloatingPoint(const uint64_t val_binary):
        exponent_length(exponent), mantissa_length(mantissa) {
        sign = (val_binary >> (exponent + mantissa)) & 1;
        exponent_value = (val_binary >> mantissa) & ((1 << exponent) - 1);
        mantissa_value = val_binary & ((1 << mantissa) - 1);
        update_state();
    }


    void print_state() {

    }
    typedef enum STATE {
        Normal,
        Subnormal,
        Zero,
        Inf,
        Nan
    } State;
private:
    bool sign;
    uint64_t exponent_value;
    uint64_t exponent_length;

    uint64_t mantissa_value;
    uint64_t mantissa_length;

    State state;

    void update_state() {
        if (exponent_value == 0 && mantissa_value == 0) {
            state = Zero;
        } else if (exponent_value == 0 && mantissa_value != 0) {
            state = Subnormal;
        } else if (exponent_value == 0xFFFFFFFF && mantissa_value == 0) {
            state = Inf;
        } else if (exponent_value == 0xFFFFFFFF && mantissa_value != 0) {
            state = Nan;
        } else {
            state = Normal;
        }
    }

};

#endif // FLOATINGPOINT_HPP_