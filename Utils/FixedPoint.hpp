#ifndef FIXEDPOINT_HPP_
#define FIXEDPOINT_HPP_

#define SIN_PI_X 0
#define COS_PI_X -1
#define PI 3.1415926535
#define Kn 0.607252935
#include <cstdint>
template <uint64_t integer, uint64_t fraction>
class FixedPoint {
public:
    /* Constructors */
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
        //printf("val_int: %f, val_frac: %f\n", val_int, val_frac);
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
    // Initialize with string
    FixedPoint(std::string val_str, int base = 2):
            int_length(integer), frac_length(fraction),
            int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        if (base != 2) {
            puts("Only support binary string initialization now.");
            exit(1);
        }
        // Sign
        sign = (val_str[0] == '-');
        if (sign) {
            val_str = val_str.substr(1);
        }
        // Integer and Fraction
        int_value = 0;
        frac_value = 0;
        int end = val_str.find('.');
        if (end == std::string::npos) {
            int_value = std::stoull(val_str, nullptr, base);
        } else {
            int_value = std::stoull(val_str.substr(0, end), nullptr, base);
            frac_value = std::stoull(val_str.substr(end + 1, frac_length), nullptr, base);
        }
        int_value &= int_mask;
        // Move the fraction part to the right position
        // Show the binary value of self_val and other_val
        int frac_str_length = val_str.length() - end - 1;
        if (frac_str_length > fraction) {
            frac_value >>= (frac_str_length - fraction);
        }
        else if (frac_str_length < fraction) {
            frac_value <<= (fraction - frac_str_length);
        }
        frac_value &= frac_mask;
    }
    
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
    FixedPoint& operator=(FixedPoint&& other) {
        sign = other.sign;
        int_value = other.int_value & int_mask;
        frac_value = other.frac_value & frac_mask;
        return *this;
    }
    FixedPoint& operator=(int val) {
        *this = FixedPoint(val);
        return *this;
    }
    FixedPoint& operator=(float val) {
        *this = FixedPoint(val);
        return *this;
    }
    FixedPoint& operator=(double val) {
        *this = FixedPoint(val);
        return *this;
    }
    FixedPoint& operator=(std::string val_str) {
        *this = FixedPoint(val_str);
        return *this;
    }


    /* Unary Operator */
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
    FixedPoint exp() const {
        int rorate = int_length;
        uint64_t frac_x = frac_value, int_x = int_value;

        uint64_t exp_frac_pos[32], exp_frac_neg[32];
        for (int i = 0; i < 32; i++) {
            exp_frac_pos[i] = std::round(std::exp(1.0 / (1 << (i + 1))) * (1 << frac_length));
            exp_frac_neg[i] = std::round(std::exp(-1.0 / (1 << (i + 1))) * (1 << frac_length));
        }
        uint64_t exp_int_pos[32], exp_int_neg[32];
        for (int i = 0; i < int_length; i++) {
            exp_int_pos[i] = std::round(std::exp(1 << i) * (1 << frac_length));
            exp_int_neg[i] = std::round(std::exp(-1 << i) * (1 << frac_length));
        }
        uint64_t expx_int = 1 << frac_length, expx_frac = 1 << frac_length;
        for (int i = 0; i < frac_length; i++) {
            if (frac_x >> (frac_length - i - 1) & 1) {
                if (sign) {
                    expx_frac *= exp_frac_neg[i];
                    expx_frac = expx_frac >> frac_length;
                } else {
                    expx_frac *= exp_frac_pos[i];
                    expx_frac = expx_frac >> frac_length;
                }
            }
        }

        if (int_x == 0) {
            expx_int = 1 << frac_length;
        }
        else {
            for (int i = 0; i < int_length; i++) {
                if (int_x & (1 << i)) {
                    if (sign) {
                        expx_int *= exp_int_neg[i];
                        expx_int = expx_int >> frac_length;
                    } else {
                        expx_int *= exp_int_pos[i];
                        expx_int = expx_int >> frac_length;
                    }
                }
            }
        }
        uint64_t expx_res = (expx_int * expx_frac) >> frac_length;

        uint64_t expx_res_int = expx_res >> frac_length,
                 expx_res_frac = expx_res & frac_mask;

        FixedPoint expx(false, expx_res_int, expx_res_frac);
        return expx;
    }
    friend FixedPoint exp(const FixedPoint& fp) {
        return fp.exp();
    };
    FixedPoint sigmoid() const {
        FixedPoint x(std::move(*this));
        FixedPoint result(0);
        if (frac_length < 3) {
            printf("CNM, 小数部分就只给 %d 位，你 Sigmoid 个锤子啊！\n", frac_length);
            return FixedPoint(0.5);
        }
        if (frac_length < 5) {
            // frac_length < 5
            if (int_length >= 2 && x.abs() >= FixedPoint(4.0))  result = FixedPoint(1.0);
            else if (x.abs() >= FixedPoint(1.0))                result = FixedPoint(0.125) * x.abs() + FixedPoint(0.625);
            else                                                result = FixedPoint(0.25) * x.abs() + FixedPoint(0.5);
        }
        else {
            // frac_length >= 5
            if (int_length >= 3 && x.abs() >= FixedPoint(5.0))          result = FixedPoint(1.0);
            else if (int_length >= 2 && x.abs() >= FixedPoint(2.375))   result = FixedPoint(0.03125) * x.abs() + FixedPoint(0.84375);
            else if (int_length >= 1 && x.abs() >= FixedPoint(1.0))     result = FixedPoint(0.125) * x.abs() + FixedPoint(0.625);
            else                                                        result = FixedPoint(0.25) * x.abs() + FixedPoint(0.5);
        }
        // For negative value, sigmoid(-x) = 1 - sigmoid(x)
        if (sign) result = FixedPoint(1.0) - result;
        
        return result;
    }
    friend FixedPoint sigmoid(const FixedPoint& fp) {
        return fp.sigmoid();
    }
    FixedPoint relu() const{
        if (sign) {
            return FixedPoint(0);
        }
        return FixedPoint(std::move(*this));
    }
    friend FixedPoint relu(const FixedPoint& fp) {
        return fp.relu();
    }
    // friend FixedPoint log(const FixedPoint& fp);
    FixedPoint sin() const{
        float LookUpTableF[16] = {
            45,             26.56505118,    14.03624347,    7.125016349,    3.576333475,    1.789910608,
            0.89517371,     0.447614171,    0.2238105,      0.111905677,    0.055952892,    0.027976453,
            0.013988227,    0.006994114,    0.003497057,    0.001748528
        };
        uint64_t LookUpTableI[16];
        for (int i = 0; i < 16;i++){
            float angle = (LookUpTableF[i] * PI) / 180;
            float ang_int = std::floor(angle), ang_frac = angle - ang_int; 
            uint64_t int_value = static_cast<uint64_t>(ang_int);
            uint64_t frac_value = static_cast<uint64_t>(std::round(ang_frac * (1 << fraction)));
            LookUpTableI[i] = (int_value << frac_length) | frac_value;
        }
        // for(int i =0;i<16;i++){
        //     std::cout << "|" << LookUpTableI[i] << "|";
        // } 
        bool sign_outside = sign;
        float x_f = Kn;
        float x_int = std::floor(x_f), x_frac = x_f - x_int; 
        uint64_t x_int_value = static_cast<uint64_t>(x_int);
        uint64_t x_frac_value = static_cast<uint64_t>(std::round(x_frac * (1 << fraction)));
        uint64_t x_value = (x_int_value << fraction) | x_frac_value;
        uint64_t y_value = 0;

        FixedPoint<integer,fraction> self_abs = FixedPoint(false, int_value, frac_value);
        while (self_abs > (2*PI))
        {
            self_abs -= (2*PI);

        }
        if (self_abs > 0.5f*PI){
            if(self_abs <= PI){
                self_abs = (PI - self_abs);
            }
            else if(self_abs <= 1.5f*PI){
                sign_outside = !sign_outside;
                self_abs = self_abs - PI;
            }
            else{
                sign_outside = !sign_outside;
                self_abs = 2*PI - self_abs;
            }
        }
        uint64_t target = (self_abs.int_value << self_abs.frac_length) | self_abs.frac_value;
        int x_value_next, y_value_next;
        int z = 0,d = 1;
        for (int i = 0; i < 16;i++){
            if (d == 1){
                x_value_next = x_value + ~(y_value >> i) + 1;
                y_value_next = y_value + (x_value >> i);
                z = z + LookUpTableI[i];
            }
            else{
                x_value_next = x_value + (y_value >> i);
                y_value_next = y_value + ~(x_value >> i) + 1;
                z = z - LookUpTableI[i];
            }
            d = (z < static_cast<int>(target)) ? 1 : -1;
            x_value = x_value_next;
            y_value = y_value_next;
        }
        if (y_value_next <0){
            y_value_next = 0;
            sign_outside = false;
        } 
        uint64_t new_int = (y_value_next >> frac_length) & int_mask,
                 new_frac = y_value_next & frac_mask;
        return FixedPoint(sign_outside, new_int, new_frac);
    }
    friend FixedPoint sin(const FixedPoint& fp) {
        return fp.sin();
    }
    FixedPoint cos()const {
        float LookUpTableF[16] = {
            45,             26.56505118,    14.03624347,    7.125016349,    3.576333475,    1.789910608,
            0.89517371,     0.447614171,    0.2238105,      0.111905677,    0.055952892,    0.027976453,
            0.013988227,    0.006994114,    0.003497057,    0.001748528
        };
        uint64_t LookUpTableI[16];
        for (int i = 0; i < 16;i++){
            float angle = (LookUpTableF[i] * PI) / 180;
            float ang_int = std::floor(angle), ang_frac = angle - ang_int; 
            uint64_t int_value = static_cast<uint64_t>(ang_int);
            uint64_t frac_value = static_cast<uint64_t>(std::round(ang_frac * (1 << fraction)));
            LookUpTableI[i] = (int_value << frac_length) | frac_value;
        }
       /*  for(int i =0;i<16;i++){
            std::cout << "|" << LookUpTableI[i] << "|";
        } */
        bool sign_outside = false;
        float x_f = Kn;
        float x_int = std::floor(x_f), x_frac = x_f - x_int; 
        uint64_t x_int_value = static_cast<uint64_t>(x_int);
        uint64_t x_frac_value = static_cast<uint64_t>(std::round(x_frac * (1 << fraction)));
        uint64_t x_value = (x_int_value << fraction) | x_frac_value;
        uint64_t y_value = 0;

        FixedPoint<integer,fraction> self_abs = FixedPoint(false, int_value, frac_value);
        while (self_abs > (2 * PI))
        {
            self_abs -= (2 * PI);

        }
        if (self_abs > 0.5f * PI){
            if(self_abs <= PI){
                self_abs = (PI - self_abs);
                sign_outside = !sign_outside;
            }
            else if(self_abs <= 1.5f * PI){
                sign_outside = !sign_outside;
                self_abs = self_abs - PI;
            }
            else{
                self_abs = 2 * PI - self_abs;
            }
        }
        uint64_t target = (self_abs.int_value << self_abs.frac_length) | self_abs.frac_value;
        int x_value_next, y_value_next;
        int z = 0,d = 1;
        for (int i = 0; i < 16;i++){
            if (d == 1){
                x_value_next = x_value + ~(y_value >> i) + 1;
                y_value_next = y_value + (x_value >> i);
                z = z + LookUpTableI[i];
            }
            else{
                x_value_next = x_value + (y_value >> i);
                y_value_next = y_value + ~(x_value >> i) + 1;
                z = z - LookUpTableI[i];
            }
            d = (z < static_cast<int>(target)) ? 1 : -1;
            x_value = x_value_next;
            y_value = y_value_next;
        }

        uint64_t new_int = (x_value_next >> frac_length) & int_mask,
                 new_frac = x_value_next & frac_mask;
        return FixedPoint(sign_outside, new_int, new_frac);
    }
    friend FixedPoint cos(const FixedPoint& fp) {
        return fp.cos();
    }
    
    /* Binary Operator */
    // Addition
    FixedPoint add(const FixedPoint& other) const {
        uint64_t self_sign = sign, other_sign = other.sign;
        uint64_t self_val = (int_value << frac_length) | frac_value,
                 other_val =  (other.int_value << frac_length) | other.frac_value;
        if (sign) {
            self_val = ~self_val + 1;
        }
        if (other_sign) {
            other_val = ~other_val + 1;
        }
        self_val |= (self_sign << (int_length + frac_length));
        other_val |= (other_sign << (int_length + frac_length));

        
        // Show the binary value of self_val and other_val
        uint64_t new_val = self_val + other_val;

        bool new_sign = (new_val >> (int_length + frac_length)) & 1;
        if (new_sign) {
            new_val = ~new_val + 1;
        }
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
    friend FixedPoint operator+(int val, const FixedPoint& fp) {
        return FixedPoint(val) + fp;
    }
    friend FixedPoint operator+(const FixedPoint& fp, int val) {
        return fp + FixedPoint(val);
    }
    friend FixedPoint operator+(double val, const FixedPoint& fp) {
        return FixedPoint(val) + fp;
    }
    friend FixedPoint operator+(const FixedPoint& fp, double val) {
        return fp + FixedPoint(val);
    }
    FixedPoint operator+=(const FixedPoint& other) {
        *this = add(other);
        return *this;
    }
    FixedPoint operator+=(int val) {
        *this = add(FixedPoint(val));
        return *this;
    }
    FixedPoint operator+=(double val) {
        *this = add(FixedPoint(val));
        return *this;
    }


    // Subtraction
    FixedPoint sub(const FixedPoint& other) const {
        return add(other.neg());
    }
    friend FixedPoint sub(const FixedPoint& fp1, const FixedPoint& fp2) {
        return fp1.sub(fp2);
    }
    FixedPoint operator-(const FixedPoint& other) const {
        return sub(other);
    };
    friend FixedPoint operator-(int val, const FixedPoint& fp) {
        return FixedPoint(val) - fp;
    }
    friend FixedPoint operator-(const FixedPoint& fp, int val) {
        return fp - FixedPoint(val);
    }
    friend FixedPoint operator-(double val, const FixedPoint& fp) {
        return FixedPoint(val) - fp;
    }
    friend FixedPoint operator-(const FixedPoint& fp, double val) {
        return fp - FixedPoint(val);
    }
    FixedPoint operator-=(const FixedPoint& other) {
        *this = sub(other);
        return *this;
    }
    FixedPoint operator-=(int val) {
        *this = sub(FixedPoint(val));
        return *this;
    }
    FixedPoint operator-=(double val) {
        *this = sub(FixedPoint(val));
        return *this;
    }

    // Multiplication
    FixedPoint mul(const FixedPoint& other) const {
        // Get the sign of the result
        bool new_sign = sign ^ other.sign;

        uint64_t self_val = (int_value << frac_length) | frac_value,
                 other_val =  (other.int_value << frac_length) | other.frac_value;
        
        __uint128_t self_val_128 = self_val, other_val_128 = other_val;
        __uint128_t new_val = self_val_128 * other_val_128;
        uint64_t new_int = new_val >> (frac_length * 2),
                 new_frac = (new_val >> frac_length) & frac_mask;

        return FixedPoint(new_sign, new_int, new_frac);
    }
    FixedPoint mul(int other_val) const {
        uint64_t self_val = (int_value << frac_length) | frac_value;
        __uint128_t self_val_128 = self_val;
        __uint128_t new_val = self_val_128 * (other_val << frac_length);
        uint64_t new_int = new_val >> frac_length,
                 new_frac = new_val & frac_mask;
        return FixedPoint(sign, new_int, new_frac);
    }
    friend FixedPoint mul(const FixedPoint& fp1, const FixedPoint& fp2) {
        return fp1.mul(fp2);
    }
    FixedPoint operator*(const FixedPoint& other) const {
        return mul(other);
    };
    FixedPoint operator*(int other_val) const {
        return mul(other_val);
    };
    friend FixedPoint operator*(int val, const FixedPoint& fp) {
        return FixedPoint(val) * fp;
    }
    friend FixedPoint operator*(double val, const FixedPoint& fp) {
        return FixedPoint(val) * fp;
    }
    friend FixedPoint operator*(const FixedPoint& fp, double val) {
        return fp * FixedPoint(val);
    }
    friend FixedPoint operator*(const FixedPoint& fp, int val) {
        return fp * FixedPoint(val);
    }
    FixedPoint operator*=(const FixedPoint& other) {
        *this = mul(other);
        return *this;
    }
    FixedPoint operator*=(int val) {
        *this = mul(val);
        return *this;
    }
    FixedPoint operator*=(double val) {
        *this = mul(val);
        return *this;
    }


    // Division
    FixedPoint div(const FixedPoint& other) const {
        // Get the sign of the result
        bool new_sign = sign ^ other.sign;

        uint64_t self_val = (int_value << frac_length) | frac_value,
                 other_val =  (other.int_value << frac_length) | other.frac_value;
        
        __uint128_t self_val_128 = self_val, other_val_128 = other_val;
        __uint128_t new_val = (self_val_128 << frac_length) / other_val_128; // Get more precision
        uint64_t new_int = (new_val >> frac_length) & int_mask,
                 new_frac = new_val & frac_mask;

        return FixedPoint(new_sign, new_int, new_frac);
    }
    FixedPoint div(int other_val) const {
        uint64_t self_val = (int_value << frac_length) | frac_value;
        __uint128_t self_val_128 = (self_val << frac_length);
        __uint128_t new_val = self_val_128 / (other_val << frac_length);
        uint64_t new_int = (new_val >> frac_length) & int_mask,
                 new_frac = new_val & frac_mask;
        return FixedPoint(sign, new_int, new_frac);
    }
    friend FixedPoint div(const FixedPoint& fp1, const FixedPoint& fp2) {
        return fp1.div(fp2);
    }
    FixedPoint operator/(const FixedPoint& other) const {
        return div(other);
    };
    FixedPoint operator/(int other_val) const {
        return div(other_val);
    };
    friend FixedPoint operator/(int val, const FixedPoint& fp) {
        return FixedPoint(val) / fp;
    }
    friend FixedPoint operator/(const FixedPoint& fp, int val) {
        return fp / FixedPoint(val);
    }
    friend FixedPoint operator/(double val, const FixedPoint& fp) {
        return FixedPoint(val) / fp;
    }
    friend FixedPoint operator/(const FixedPoint& fp, double val) {
        return fp / FixedPoint(val);
    }
    FixedPoint operator/=(const FixedPoint& other) {
        *this = div(other);
        return *this;
    }
    FixedPoint operator/=(int val) {
        *this = div(val);
        return *this;
    }
    FixedPoint operator/=(double val) {
        *this = div(val);
        return *this;
    }

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
        uint64_t frac = frac_value;
        for (int i = 0; i < fraction; i++) {
            frac *= 10;
            num_str += std::to_string(frac >> fraction);
            frac &= frac_mask;
        }
        // Remove the possible trailing zeros
        while (num_str.back() == '0') {
            // If the last character is '.', save it and add a zero to the end
            if (num_str[num_str.length() - 2] == '.' && num_str.back() == '0') {
                break;
            }
            num_str.pop_back();
        }
        return num_str;
    }
    friend std::string to_string(const FixedPoint& fp) {
        return fp.to_string();
    }
    const char* to_c_string() const {
        const std::string& str = to_string();
        const char* c_str = str.c_str();
        return c_str;
    }
    friend std::ostream& operator<<(std::ostream& os, const FixedPoint& fp) {
        os << fp.to_string();
        return os;
    }
    friend std::istream& operator>>(std::istream& is, FixedPoint& fp) {
        float num_float;
        is >> num_float;
        fp = FixedPoint(num_float);
        return is;
    }

    float to_float() const {
        // Translate the FixedPoint to float value
        float val = static_cast<float>(int_value);
        float frac = static_cast<float>(frac_value) / (1 << frac_length);
        return sign ? -(val + frac) : val + frac;
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