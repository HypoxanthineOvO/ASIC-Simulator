#include "type.hpp"
#include <iostream>

int main() {
    puts("==================== Unit Test Of Types ====================");
    // Flush the buffer
    std::cout << std::flush;
    puts("1. Test Initialization of FixedPoint");
    FixedPoint<2, 4> fp1;
    printf("\tFP1: Default Initialization: %d %d %d -> %s\n", fp1.get_sign(), fp1.get_int_value(), fp1.get_frac_value(), fp1.to_string().c_str());
    FixedPoint<2, 4> fp2(1, 3, 2);
    printf("\tFP2: Custom Initialization: %d %d %d -> %s\n", fp2.get_sign(), fp2.get_int_value(), fp2.get_frac_value(), fp2.to_c_string());
    FixedPoint<2, 4> fp3(1, 4, 2); // Test for overflow
    printf("\tFP3: Overflow Initialization: %d %d %d -> %s\n", fp3.get_sign(), fp3.get_int_value(), fp3.get_frac_value(), fp3.to_c_string());
    FixedPoint<2, 4> fp4(1, 3, 4); // Test for overflow
    printf("\tFP4: Overflow Initialization: %d %d %d -> %s\n", fp4.get_sign(), fp4.get_int_value(), fp4.get_frac_value(), fp4.to_c_string());
    FixedPoint<2, 4> fp5(fp2); // Test for copy constructor
    FixedPoint<2, 4> fp6(3.25); // Test for float initialization
    printf("\tFP6: Double Initialization: %d %d %d -> %s\n", fp6.get_sign(), fp6.get_int_value(), fp6.get_frac_value(), fp6.to_c_string());
    FixedPoint<2, 4> fp7("0.1011", 2); // Test for string initialization
    printf("\tFP7: String Initialization: %d %d %d -> %s\n", fp7.get_sign(), fp7.get_int_value(), fp7.get_frac_value(), fp7.to_c_string());

    // TODO: Noticed that initialize from other FixedPoint maybe lose some information

    puts("2. Test Unary Operator of FixedPoint");
    FixedPoint<2, 4> fp_add_1(0.25);
    FixedPoint<2, 4> fp_add_2(0.75);
    printf("\tFP_Add_1: %s\n", fp_add_1.to_c_string());
    printf("\tFP_Add_2: %s\n", fp_add_2.to_c_string());
    FixedPoint<2, 4> fp_add_3 = fp_add_1.add(fp_add_2);
    printf("\tFP_Add_3 = FP_Add_1 + FP_Add_2: %s\n", fp_add_3.to_c_string());
    FixedPoint<2, 4> fp_add_4 = -fp_add_1;
    printf("\tFP_Add_4 = - FP_Add_1: %s\n", fp_add_4.to_c_string());
    FixedPoint<2, 4> fp_add_5 = fp_add_1 + (-fp_add_2);
    printf("\tFP_Add_5 = FP_Add_1 + (- FP_Add_2): %s\n", fp_add_5.to_c_string());
    printf("\n");

    FixedPoint<2, 4> fp_sub_1 = fp_add_1 - fp_add_2;
    printf("\tFP_Sub_1 = FP_Add_1 - FP_Add_2: %s\n", fp_sub_1.to_c_string());
    printf("\n");

    FixedPoint<2, 8> fp_mul_1("-0.1101");
    printf("\tFP_Mul_1: %s\n", fp_mul_1.to_string().c_str());
    FixedPoint<2, 8> fp_mul_2("0.1011");
    printf("\tFP_Mul_2: %s\n", fp_mul_2.to_c_string());
    FixedPoint<2, 8> fp_mul_3 = fp_mul_1 * fp_mul_2;
    printf("\tFP_Mul_3 = FP_Mul_1 * FP_Mul_2: %s\n", fp_mul_3.to_c_string());

    FixedPoint<2, 8> fp_div_1 = fp_mul_1 / fp_mul_2;
    printf("\tFP_Div_1 = FP_Mul_1 / FP_Mul_2: %s\n", fp_div_1.to_c_string());
    FixedPoint<2, 8> fp_div_2(0.75);
    printf("\tFP_Div_2: %s\n", fp_div_2.to_c_string());
    FixedPoint<2, 8> fp_div_3(0.25);
    printf("\tFP_Div_3: %s\n", fp_div_3.to_c_string());
    FixedPoint<2, 8> fp_div_4 = fp_div_2 / fp_div_3;
    printf("\tFP_Div_4 = FP_Div_2 / FP_Div_3: %s\n", fp_div_4.to_c_string());

    puts("3. Test Binary Operator of FixedPoint");

    puts("4. Test Comparison Operator of FixedPoint");

    puts("5. Test Conversion Operator of FixedPoint");
}