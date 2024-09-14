#ifndef FIXEDPOINT_HPP_
#define FIXEDPOINT_HPP_

#include <cstdint>
template <uint64_t integer, uint64_t fraction>
class FixedPoint {
public:
    // Default: Initialize to Fixed Point 0
    FixedPoint(): sign(false), int_value(0), frac_value(0),
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {}
    // Initialize with integer value
    FixedPoint(int val): sign(val < 0), int_value(std::abs(val)), frac_value(0), 
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        int_value &= int_mask;
    }
    // Initialize with integer and fraction value
    FixedPoint(bool sign, uint64_t int_val, uint64_t frac_val): sign(sign), int_value(int_val), frac_value(frac_val), 
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        int_value &= int_mask;
        frac_value &= frac_mask;
    }
    // Initialize with floating point value
    FixedPoint(float val): 
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
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
    FixedPoint(double val): 
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        sign = (val < 0);
        double abs_val = std::abs(val);
        double val_int = std::floor(abs_val), val_frac = abs_val - val_int;
        int_value = static_cast<uint64_t>(val_int);
        frac_value = static_cast<uint64_t>(
            std::round(val_frac * (1 << fraction))
        );
        int_value &= int_mask;
        frac_value &= frac_mask;
    };
    // Copy Constructor
    FixedPoint(const FixedPoint& other): sign(other.sign), 
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        int_value = other.int_value & int_mask;
        frac_value = other.frac_value & frac_mask;
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
    FixedPoint neg() const {
        return FixedPoint(!sign, int_value, frac_value);
    }
    FixedPoint operator-() const {
        return neg();
    }
    friend FixedPoint neg(const FixedPoint& fp) {
        return fp.neg();
    }
    // Friend Function
    FixedPoint abs() const {
        return FixedPoint(false, int_value, frac_value);
    }
    friend FixedPoint abs(const FixedPoint& fp) {
        return fp.abs();
    }
    // TODO: Implement these unary operators
    // friend FixedPoint sqrt(const FixedPoint& fp);
    // friend FixedPoint exp(const FixedPoint& fp);
    // friend FixedPoint log(const FixedPoint& fp);
    // friend FixedPoint sin(const FixedPoint& fp);
    // friend FixedPoint cos(const FixedPoint& fp);
    
    // Binary Operator
    FixedPoint add(const FixedPoint& other) const {
        uint64_t self_sign = sign, other_sign = other.sign;
        printf("self_sign: %d, other_sign: %d\n", self_sign, other_sign);
        uint64_t self_val = (int_value << frac_length) | frac_value,
                 other_val =  (other.int_value << frac_length) | other.frac_value;
        
        if (sign) {
            self_val = ~self_val + 1;
        }
        if (other.sign) {
            other_val = ~other_val + 1;
        }
        self_val |= (self_sign << (int_length + frac_length));
        other_val |= (other_sign << (int_length + frac_length));
        
        // Show the binary value of self_val and other_val
        uint64_t new_val = self_val + other_val;


        bool new_sign = (new_val >> (int_length + frac_length)) & 1;
        uint64_t new_int = (new_val >> frac_length) & int_mask,
                    new_frac = new_val & frac_mask;

        FixedPoint result(new_sign, new_int, new_frac);
        return result;
    }
    friend FixedPoint add(const FixedPoint& fp1, const FixedPoint& fp2) {
        return fp1.add(fp2);
    }
    FixedPoint operator+(const FixedPoint& other) const {
        return add(other);
    };
    FixedPoint sub(const FixedPoint& other) const {
        return add(other.neg());
    }
    friend FixedPoint sub(const FixedPoint& fp1, const FixedPoint& fp2) {
        return fp1.sub(fp2);
    }
    FixedPoint operator-(const FixedPoint& other) const {
        return sub(other);
    };
    FixedPoint operator*(const FixedPoint& other) const {

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
    uint64_t int_length;
    uint64_t int_mask;
    uint64_t frac_value;
    uint64_t frac_length;
    uint64_t frac_mask;
};

#endif // FIXEDPOINT_HPP_