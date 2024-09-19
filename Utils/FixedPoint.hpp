当然！我将为每一部分代码添加更加详细的注释，以便于理解。

```cpp
#ifndef FIXEDPOINT_HPP_
#define FIXEDPOINT_HPP_

#include <cstdint>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>

// 定义一个固定点数类模板，参数为整数部分和小数部分的位数
template <uint64_t integer, uint64_t fraction>
class FixedPoint {
public:
    /* 构造函数 */
    // 默认构造函数: 初始化为 0
    FixedPoint() : sign(false), int_value(0), frac_value(0),
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {}

    // 使用整数值初始化
    FixedPoint(int val) : sign(val < 0), int_value(std::abs(val)), frac_value(0), 
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        // 确保整数不会超过位掩码
        int_value &= int_mask;
    }

    // 使用整数和小数部分的具体值初始化
    FixedPoint(bool sign, uint64_t int_val, uint64_t frac_val) : 
        sign(sign), int_value(int_val), frac_value(frac_val), 
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        // 确保整数和小数部分不会超过位掩码
        int_value &= int_mask;
        frac_value &= frac_mask;
    }

    // 使用浮点数初始化
    FixedPoint(float val) : 
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        // 处理符号位
        sign = (val < 0);
        float abs_val = std::abs(val);
        float val_int = std::floor(abs_val), val_frac = abs_val - val_int;
        // 将整数和小数部分拆分并转换为固定点数表示
        int_value = static_cast<uint64_t>(val_int);
        frac_value = static_cast<uint64_t>(
            std::round(val_frac * (1 << fraction))
        );
        int_value &= int_mask;
        frac_value &= frac_mask;
    };

    // 使用双精度浮点数初始化
    FixedPoint(double val) : 
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

    // 使用字符串初始化，默认以二进制表示（base=2）
    FixedPoint(std::string val_str, int base = 2) :
            int_length(integer), frac_length(fraction),
            int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        if (base != 2) {
            puts("Only support binary string initialization now.");
            exit(1);
        }
        
        // 处理符号位
        sign = (val_str[0] == '-');
        if (sign) {
            val_str = val_str.substr(1);
        }

        // 处理整数和小数部分
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
        
        // 调整小数部分位置
        int frac_str_length = val_str.length() - end - 1;
        if (frac_str_length > fraction) {
            frac_value >>= (frac_str_length - fraction);
        } else if (frac_str_length < fraction) {
            frac_value <<= (fraction - frac_str_length);
        }
        frac_value &= frac_mask;
    }
    
    // 拷贝构造函数
    FixedPoint(const FixedPoint& other) : sign(other.sign), 
        int_length(integer), frac_length(fraction),
        int_mask((1 << integer) - 1), frac_mask((1 << fraction) - 1) {
        int_value = other.int_value & int_mask;
        frac_value = other.frac_value & frac_mask;
    }

    // 移动构造函数
    FixedPoint(FixedPoint&& other) : sign(other.sign), int_value(other.int_value), 
        frac_value(other.frac_value), int_mask((1 << integer) - 1), 
        frac_mask((1 << fraction) - 1) {
        int_value &= int_mask;
        frac_value &= frac_mask;
    }

    // 赋值运算符
    FixedPoint& operator=(const FixedPoint& other) {
        sign = other.sign;
        int_value = other.int_value & int_mask;
        frac_value = other.frac_value & frac_mask;
        return *this;
    }

    /* 一元运算符 */
    // 取反运算符（返回符号相反的值）
    FixedPoint neg() const {
        return FixedPoint(!sign, int_value, frac_value);
    }
    FixedPoint operator-() const {
        return neg();
    }
    friend FixedPoint neg(const FixedPoint& fp) {
        return fp.neg();
    }

    // 绝对值运算符（返回正值）
    FixedPoint abs() const {
        return FixedPoint(false, int_value, frac_value);
    }
    friend FixedPoint abs(const FixedPoint& fp) {
        return fp.abs();
    }

    // 计算指数函数（近似）
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

        uint64_t expx_int = 1, expx_frac = 1;
        for (int i = 0; i < frac_length; i++) {
            if (frac_x >> (frac_length - i - 1) & 1) {
                if (sign) {
                    expx_frac *= exp_frac_neg[i];
                } else {
                    expx_frac *= exp_frac_pos[i];
                }
            }
        }

        if (int_x == 0) {
            expx_int = 1 << frac_length;
        } else {
            for (int i = 0; i < int_length; i++) {
                if (int_x & (1 << i)) {
                    if (sign) {
                        expx_int *= exp_int_neg[i];
                    } else {
                        expx_int *= exp_int_pos[i];
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
    }

    // 计算 Sigmoid 函数（近似）
    FixedPoint sigmoid() const {
        FixedPoint x(std::move(*this));
        FixedPoint result(0);
        if (frac_length < 3) {
            printf("CNM, 小数部分就只给 %d 位，你 Sigmoid 个锤子啊！\n", frac_length);
            return FixedPoint(0.5);
        }
        if (frac_length < 5) {
            if (int_length >= 2 && x.abs() >= FixedPoint(4.0))  result = FixedPoint(1.0);
            else if (x.abs() >= FixedPoint(1.0))                result = FixedPoint(0.125) * x + FixedPoint(0.625);
            else                                                result = FixedPoint(0.25) * x + FixedPoint(0.5);
        } else {
            if (int_length >= 3 && x.abs() >= FixedPoint(5.0))          result = FixedPoint(1.0);
            else if (int_length >= 2 && x.abs() >= FixedPoint(2.375))   result = FixedPoint(0.03125) * x + FixedPoint(0.84375);
            else if (int_length >= 1 && x.abs() >= FixedPoint(1.0))     result = FixedPoint(0.125) * x + FixedPoint(0.625);
            else                                                        result = FixedPoint(0.25) * x + FixedPoint(0.5);
        }
        if (sign) result = FixedPoint(1.0) - result;
        
        return result;
    }
    friend FixedPoint sigmoid(const FixedPoint& fp) {
        return fp.sigmoid();
    }

    /* 二元运算符 */
    // 加法运算符
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

    // 减法运算符
    FixedPoint sub(const FixedPoint& other) const {
        return add(other.neg());
    }
    friend FixedPoint sub(const FixedPoint& fp1, const FixedPoint& fp2) {
        return fp1.sub(fp2);
    }
    FixedPoint operator-(const FixedPoint& other) const {
        return sub(other);
    };

    // 乘法运算符
    FixedPoint mul(const FixedPoint& other) const {
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

    // 除法运算符
    FixedPoint div(const FixedPoint& other) const {
        bool new_sign = sign ^ other.sign;

        uint64_t self_val = (int_value << frac_length) | frac_value,
                 other_val =  (other.int_value << frac_length) | other.frac_value;
        
        __uint128_t self_val_128 = self_val, other_val_128 = other_val;
        __uint128_t new_val = (self_val_128 << frac_length) / other_val_128;
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

    // 比较运算符
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

    // 获取器方法
    bool get_sign() const { return sign; }
    uint64_t get_int_value() const { return int_value; }
    uint64_t get_frac_value() const { return frac_value; }
    
    // 设置器方法
    void set_sign(bool sign) { this->sign = sign; }
    void set_int_value(uint64_t int_value) { this->int_value = int_value; }
    void set_frac_value(uint64_t frac_value) { this->frac_value = frac_value; }

    // 将固定点数转为字符串
    std::string to_string() const {
        std::string num_str = "";
        if (sign) {
            num_str += "-";
        }
        num_str += std::to_string(int_value) + ".";
        // 转换 frac_value（二进制）为字符串（十进制）
        uint64_t frac = frac_value;
        int transfer_length = 0, tmp = 1;
        while(true) {
            transfer_length++;
            if ((frac / tmp) == 0) {
                break;
            }
            tmp *= 10;
        }
        for (int i = 0; i < transfer_length; i++) {
            frac *= 10;
            num_str += std::to_string(frac >> fraction);
            frac &= frac_mask;
        }
        return num_str;
    }
    const char* to_c_string() const {
        const std::string& str = to_string();
        const char* c_str = str.c_str();
        return c_str;
    }

    // 重载 << 操作符，用于输出
    friend std::ostream& operator<<(std::ostream& os, const FixedPoint& fp) {
        os << (fp.sign ? "-" : "") << fp.int_value << "." << fp.frac_value;
        return os;
    }

private:
    bool sign;        // 符号位，表示正负
    uint64_t int_value;     // 整数部分的值
    uint64_t int_length;    // 整数部分的位数
    uint64_t int_mask;      // 整数部分的掩码，用于确保整数位数不超过指定长度
    uint64_t frac_value;    // 小数部分的值
    uint64_t frac_length;   // 小数部分的位数
    uint64_t frac_mask;     // 小数部分的