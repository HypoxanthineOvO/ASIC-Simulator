#include "type.hpp"
#include <iostream>

int main() {
    puts("==================== Unit Test Of Types ====================");
    puts("1. Test Initialization of FixedPoint");
    using FP_Test = FixedPoint<2, 4>;
    FP_Test fp1;
    printf("\tFP1: Default Initialization: %d %d %d -> %s\n", fp1.get_sign(), fp1.get_int_value(), fp1.get_frac_value(), fp1.to_c_string());
    FP_Test fp2(1, 3, 2);
    printf("\tFP2: Custom Initialization: %d %d %d -> %s\n", fp2.get_sign(), fp2.get_int_value(), fp2.get_frac_value(), fp2.to_c_string());
    FP_Test fp3(1, 4, 2); // Test for overflow
    printf("\tFP3: Overflow Initialization: %d %d %d -> %s\n", fp3.get_sign(), fp3.get_int_value(), fp3.get_frac_value(), fp3.to_c_string());
    FP_Test fp4(1, 3, 4); // Test for overflow
    printf("\tFP4: Overflow Initialization: %d %d %d -> %s\n", fp4.get_sign(), fp4.get_int_value(), fp4.get_frac_value(), fp4.to_c_string());
    FP_Test fp5(fp2); // Test for copy constructor
    printf("\tFP5: Copy Constructor: %d %d %d -> %s\n", fp5.get_sign(), fp5.get_int_value(), fp5.get_frac_value(), fp5.to_c_string());
    FP_Test fp6(std::move(fp2)); // Test for move constructor
    printf("\tFP6: Move Constructor: %d %d %d -> %s\n", fp6.get_sign(), fp6.get_int_value(), fp6.get_frac_value(), fp6.to_c_string());
    FP_Test fp7 = fp5; // Test for assignment operator
    printf("\tFP7: Assignment Operator: %d %d %d -> %s\n", fp7.get_sign(), fp7.get_int_value(), fp7.get_frac_value(), fp7.to_c_string());
    FP_Test fp8(3.25); // Test for float initialization
    printf("\tFP8: Float Initialization: %d %d %d -> %s\n", fp8.get_sign(), fp8.get_int_value(), fp8.get_frac_value(), fp8.to_c_string());

    puts("2. Test Unary Operator of FixedPoint");
    FP_Test fp9 = -fp7;
    printf("\tFP9: %d %d %d -> %s\n", fp9.get_sign(), fp9.get_int_value(), fp9.get_frac_value(), fp9.to_c_string());

    puts("3. Test Binary Operator of FixedPoint");
    FP_Test fp10 = fp7 + fp9;
    printf("\tFP10: %d %d %d -> %s\n", fp10.get_sign(), fp10.get_int_value(), fp10.get_frac_value(), fp10.to_c_string());
    FP_Test fp11 = fp8 + fp8;
    printf("\tFP11: %d %d %d -> %s\n", fp11.get_sign(), fp11.get_int_value(), fp11.get_frac_value(), fp11.to_c_string());
    FP_Test fp12 = fp3 - fp2;
    printf("\tFP12: %d %d %d -> %s\n", fp12.get_sign(), fp12.get_int_value(), fp12.get_frac_value(), fp12.to_c_string());

    puts("4. Test Comparison Operator of FixedPoint");

    puts("5. Test Conversion Operator of FixedPoint");
}