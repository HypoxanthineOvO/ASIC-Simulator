#ifndef TYPE_HPP_
#define TYPE_HPP_
#include <cstdint>
#include <cmath>
#include <iostream>

/* Fixed Point Datatype */
template <uint64_t integer, uint64_t fraction>
class FixedPoint {
public:
    // Default: Initialize to Fixed Point 0
    FixedPoint(): sign(false), int_value(0), frac_value(0), int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {}
    // Initialize with integer value
    FixedPoint(int val): sign(val < 0), int_value(std::abs(val)), frac_value(0), int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        int_value &= int_mask;
    }
    // Initialize with integer and fraction value
    FixedPoint(int int_val, int frac_val): sign(int_val < 0), int_value(std::abs(int_val)), frac_value(frac_val), int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        int_value &= int_mask;
        frac_value &= frac_mask;
    }
    // Initialize with integer and fraction value
    FixedPoint(bool sign, uint64_t int_val, uint64_t frac_val): sign(sign), int_value(int_val), frac_value(frac_val), int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        int_value &= int_mask;
        frac_value &= frac_mask;
    }
    // Initialize with floating point value
    FixedPoint(float val): int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        sign = (val < 0);
        float abs_val = std::abs(val);
        float val_int = std::floor(abs_val), val_frac = abs_val - val_int;
        printf("val_int: %f, val_frac: %f\n", val_int, val_frac);
        int_value = static_cast<uint64_t>(val_int);
        frac_value = static_cast<uint64_t>(
            std::round(val_frac * (1 << fraction))
        );
        int_value &= int_mask;
        frac_value &= frac_mask;
    };
    FixedPoint(double val): int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        sign = (val < 0);
        double abs_val = std::abs(val);
        double val_int = std::floor(abs_val), val_frac = abs_val - val_int;
        int_value = static_cast<uint64_t>(val_int);
        frac_value = static_cast<uint64_t>(
            std::round(val_frac * (1 << fraction))
        );
        printf("frac_value: %lu\n", frac_value);
        int_value &= int_mask;
        frac_value &= frac_mask;
    };
    // Copy Constructor
    FixedPoint(const FixedPoint& other): sign(other.sign), int_value(other.int_value), frac_value(other.frac_value), int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        int_value &= int_mask;
        frac_value &= frac_mask;
    }
    // Move Constructor
    FixedPoint(FixedPoint&& other): sign(other.sign), int_value(other.int_value), frac_value(other.frac_value), int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        int_value &= int_mask;
        frac_value &= frac_mask;
    }
    // Assignment Operator
    FixedPoint& operator=(const FixedPoint& other) {
        sign = other.sign;
        int_value = other.int_value & int_mask;
        frac_value = other.frac_value & frac_mask;
        return *this;
    }

    // Unary Operator
    FixedPoint operator-() const {
        return FixedPoint(!sign, int_value, frac_value);
    }
    // Friend Function
    friend FixedPoint abs(const FixedPoint& fp) {
        return FixedPoint(false, fp.int_value, fp.frac_value);
    }
    //friend FixedPoint sqrt(const FixedPoint& fp);
    //friend FixedPoint exp(const FixedPoint& fp);
    //friend FixedPoint log(const FixedPoint& fp);
    //friend FixedPoint sin(const FixedPoint& fp);
    //friend FixedPoint cos(const FixedPoint& fp);
    
    // Binary Operator
    FixedPoint operator+(const FixedPoint& other) const {
        if (sign == other.sign) {
            return FixedPoint(sign, (int_value + other.int_value) & int_mask, (frac_value + other.frac_value) & frac_mask);
        }
        else {
            if (int_value > other.int_value) {
                return FixedPoint(sign, (int_value - other.int_value) & int_mask, (frac_value - other.frac_value) & frac_mask);
            } else {
                return FixedPoint(!sign, (other.int_value - int_value) & int_mask, (other.frac_value - frac_value) & frac_mask);
            }
        }
    };
    FixedPoint operator-(const FixedPoint& other) const {
        return *this + (-other);
    };
    FixedPoint operator*(const FixedPoint& other) const {
        bool new_sign = sign ^ other.sign;
        uint64_t new_val1 = (int_value << fraction) + frac_value,
                 new_val2 = (other.int_value << fraction) + other.frac_value;
        uint64_t new_result = 0;
        for (int i = 0; i < fraction; i++) {
            if (new_val2 & 1) {
                new_result += new_val1;
            }
            new_val1 <<= 1;
            new_val2 >>= 1;
        }
        uint64_t new_int = new_result >> (fraction * 2),
                    new_frac = new_result & ((1 << fraction) - 1);
        return FixedPoint(new_sign, new_int, new_frac);
    };
    //FixedPoint operator/(const FixedPoint& other) const;

    // Comparison Operator
    bool operator==(const FixedPoint& other) const {
        return sign == other.sign && int_value == other.int_value && frac_value == other.frac_value;
    };
    bool operator!=(const FixedPoint& other) const {
        return !(*this == other);
    };
    bool operator<(const FixedPoint& other) const {
        if (sign != other.sign) {
            return sign;
        } else if (int_value != other.int_value) {
            return sign ? int_value > other.int_value : int_value < other.int_value;
        } else {
            return sign ? frac_value > other.frac_value : frac_value < other.frac_value;
        }
    };
    bool operator<=(const FixedPoint& other) const {
        return *this < other || *this == other;
    };
    bool operator>(const FixedPoint& other) const {
        return !(*this <= other);
    };
    bool operator>=(const FixedPoint& other) const {
        return !(*this < other);
    };

    // Getter
    bool get_sign() const { return sign; }
    uint64_t get_int_value() const { return int_value; }
    uint64_t get_frac_value() const { return frac_value; }
    // Setter
    void set_sign(bool sign) { this->sign = sign; }
    void set_int_value(uint64_t int_value) { this->int_value = int_value; }
    void set_frac_value(uint64_t frac_value) { this->frac_value = frac_value; }

    // For printing
    std::string to_string() const {
        std::string num_str = "";
        if (sign) {
            num_str += "-";
        }
        num_str += std::to_string(int_value) + ".";
        // Transform frac_value(Binary) to string(Decimal)
        // e.g. frac = 4 = 0100, length = 4 -> string: "2500"
        uint64_t frac = frac_value;
        for (int i = 0; i < fraction; i++) {
            frac *= 10;
            num_str += std::to_string(frac >> fraction);
            frac &= frac_mask;
        }
        return num_str;
    }
    const char* to_c_string() const {
        return to_string().c_str();
    }
    friend std::ostream& operator<<(std::ostream& os, const FixedPoint& fp) {
        os << (fp.sign ? "-" : "") << fp.int_value << "." << fp.frac_value;
        return os;
    }

private:
    bool sign;
    uint64_t int_value;
    uint64_t int_mask;
    uint64_t frac_value;
    uint64_t frac_mask;
};

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