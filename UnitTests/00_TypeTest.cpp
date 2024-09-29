#include "type.hpp"
#include <iostream>
#define PI 3.1415926535
int main() {
    puts("==================== Unit Test Of Types ====================");
    // Flush the buffer
    std::cout << std::flush;
    puts("1. Test Initialization of FixedPoint");
    FixedPoint<2, 4> fp1;
    printf("\tFP1: Default Initialization: %d %d %d -> %s\n", fp1.get_sign(), fp1.get_int_value(), fp1.get_frac_value(), fp1.to_string().c_str());
    FixedPoint<2, 4> fp2(1, 3, 2);
    printf("\tFP2: Custom Initialization: %d %d %d -> %s\n", fp2.get_sign(), fp2.get_int_value(), fp2.get_frac_value(), fp2.to_string().c_str());
    FixedPoint<2, 4> fp3(1, 4, 2); // Test for overflow
    printf("\tFP3: Overflow Initialization: %d %d %d -> %s\n", fp3.get_sign(), fp3.get_int_value(), fp3.get_frac_value(), fp3.to_string().c_str());
    FixedPoint<2, 4> fp4(1, 3, 4); // Test for overflow
    printf("\tFP4: Overflow Initialization: %d %d %d -> %s\n", fp4.get_sign(), fp4.get_int_value(), fp4.get_frac_value(), fp4.to_string().c_str());
    FixedPoint<2, 4> fp5(fp2); // Test for copy constructor
    FixedPoint<2, 4> fp6(3.25); // Test for float initialization
    printf("\tFP6: Double Initialization: %d %d %d -> %s\n", fp6.get_sign(), fp6.get_int_value(), fp6.get_frac_value(), fp6.to_string().c_str());
    FixedPoint<2, 4> fp7("0.1011", 2); // Test for string initialization
    printf("\tFP7: String Initialization: %d %d %d -> %s\n", fp7.get_sign(), fp7.get_int_value(), fp7.get_frac_value(), fp7.to_string().c_str());

    // TODO: Noticed that initialize from other FixedPoint maybe lose some information

    puts("2. Test Unary Operator of FixedPoint");
    FixedPoint<2, 4> fp_neg_1(0.25);
    printf("\tFP_Neg_1: %s\n", fp_neg_1.to_string().c_str());
    FixedPoint<2, 4> fp_neg_2 = -fp_neg_1;
    printf("\tFP_Neg_2 = - FP_Neg_1: %s\n", fp_neg_2.to_string().c_str());
    printf("\n");

    FixedPoint<2, 4> fp_abs_1(-0.25);
    printf("\tFP_Abs_1: %s\n", fp_abs_1.to_string().c_str());
    FixedPoint<2, 4> fp_abs_2 = fp_abs_1.abs();
    printf("\tFP_Abs_2 = abs(FP_Abs_1): %s\n", fp_abs_2.to_string().c_str());
    printf("\n");

    FixedPoint<8, 8> fp_exp_1(1.5);
    printf("\tFP_Exp_1: %s\n", fp_exp_1.to_string().c_str());
    FixedPoint<8, 8> fp_exp_2 = exp(fp_exp_1);
    printf("\tFP_Exp_2 = exp(FP_Exp_1): %s\n", fp_exp_2.to_string().c_str());
    FixedPoint<8, 8> fp_exp_3(-1.5);
    printf("\tFP_Exp_3: %s\n", fp_exp_3.to_string().c_str());
    FixedPoint<8, 8> fp_exp_4 = exp(fp_exp_3);
    printf("\tFP_Exp_4 = exp(FP_Exp_3): %s\n", fp_exp_4.to_string().c_str());
    FixedPoint<8, 8> fp_exp_5(0.5);
    printf("\tFP_Exp_5: %s\n", fp_exp_5.to_string().c_str());
    FixedPoint<8, 8> fp_exp_6 = exp(fp_exp_5);
    printf("\tFP_Exp_6 = exp(FP_Exp_5): %s\n", fp_exp_6.to_string().c_str());
    FixedPoint<8, 8> fp_exp_7(5);
    printf("\tFP_Exp_7: %s\n", fp_exp_7.to_string().c_str());
    FixedPoint<8, 8> fp_exp_8 = exp(fp_exp_7);
    printf("\tFP_Exp_8 = exp(FP_Exp_7): %s\n", fp_exp_8.to_string().c_str());
    printf("\n");


    FixedPoint<1, 6> fp_sigmoid_1(0.25);
    printf("\tFP_Sigmoid_1: %s\n", fp_sigmoid_1.to_string().c_str());
    FixedPoint<1, 6> fp_sigmoid_2 = sigmoid(fp_sigmoid_1);
    printf("\tFP_Sigmoid_2 = sigmoid(FP_Sigmoid_1): %s\n", fp_sigmoid_2.to_string().c_str());
    FixedPoint<1, 2> fp_sigmoid_3(0.25);
    printf("\tFP_Sigmoid_3: %s\n", fp_sigmoid_3.to_string().c_str());
    FixedPoint<1, 2> fp_sigmoid_4 = sigmoid(fp_sigmoid_3);
    printf("\tFP_Sigmoid_4 = sigmoid(FP_Sigmoid_3): %s\n", fp_sigmoid_4.to_string().c_str());
    FixedPoint<1, 4> fp_sigmoid_5(0.25);
    printf("\tFP_Sigmoid_5: %s\n", fp_sigmoid_5.to_string().c_str());
    FixedPoint<1, 4> fp_sigmoid_6 = sigmoid(fp_sigmoid_5);
    printf("\tFP_Sigmoid_6 = sigmoid(FP_Sigmoid_5): %s\n", fp_sigmoid_6.to_string().c_str());
    printf("\n");

    puts("3. Test Binary Operator of FixedPoint");
    FixedPoint<2, 4> fp_add_1(0.25);
    FixedPoint<2, 4> fp_add_2(0.75);
    printf("\tFP_Add_1: %s\n", fp_add_1.to_string().c_str());
    printf("\tFP_Add_2: %s\n", fp_add_2.to_string().c_str());
    FixedPoint<2, 4> fp_add_3 = fp_add_1.add(fp_add_2);
    printf("\tFP_Add_3 = FP_Add_1 + FP_Add_2: %s\n", fp_add_3.to_string().c_str());
    FixedPoint<2, 4> fp_add_4 = -fp_add_1;
    printf("\tFP_Add_4 = - FP_Add_1: %s\n", fp_add_4.to_string().c_str());
    FixedPoint<2, 4> fp_add_5 = fp_add_1 + (-fp_add_2);
    printf("\tFP_Add_5 = FP_Add_1 + (- FP_Add_2): %s\n", fp_add_5.to_string().c_str());
    printf("\n");

    FixedPoint<2, 4> fp_add_6(1.75);
    printf("\tFP_Add_6: %s\n", fp_add_6.to_string().c_str());
    FixedPoint<2, 4> fp_add_7(0.205);
    printf("\tFP_Add_7: %s\n", fp_add_7.to_string().c_str());
    FixedPoint<2, 4> fp_add_8 = fp_add_6 + fp_add_7;
    printf("\tFP_Add_8 = FP_Add_6 + FP_Add_7: %s\n", fp_add_8.to_string().c_str());
    // Test Overload "<<"
    std::cout << "\tFP_Add_6 + FP_Add_7: " << (fp_add_6 + fp_add_7) << std::endl << std::endl;

    FixedPoint<2, 4> fp_sub_1 = fp_add_1 - fp_add_2;
    printf("\tFP_Sub_1 = FP_Add_1 - FP_Add_2: %s\n", fp_sub_1.to_string().c_str());
    printf("\n");

    FixedPoint<2, 8> fp_mul_1("-0.1101");
    printf("\tFP_Mul_1: %s\n", fp_mul_1.to_string().c_str());
    FixedPoint<2, 8> fp_mul_2("0.1011");
    printf("\tFP_Mul_2: %s\n", fp_mul_2.to_string().c_str());
    FixedPoint<2, 8> fp_mul_3 = fp_mul_1 * fp_mul_2;
    printf("\tFP_Mul_3 = FP_Mul_1 * FP_Mul_2: %s\n", fp_mul_3.to_string().c_str());

    FixedPoint<2, 8> fp_div_1 = fp_mul_1 / fp_mul_2;
    printf("\tFP_Div_1 = FP_Mul_1 / FP_Mul_2: %s\n", fp_div_1.to_string().c_str());
    FixedPoint<2, 8> fp_div_2(0.75);
    printf("\tFP_Div_2: %s\n", fp_div_2.to_string().c_str());
    FixedPoint<2, 8> fp_div_3(0.25);
    printf("\tFP_Div_3: %s\n", fp_div_3.to_string().c_str());
    FixedPoint<2, 8> fp_div_4 = fp_div_2 / fp_div_3;
    printf("\tFP_Div_4 = FP_Div_2 / FP_Div_3: %s\n", fp_div_4.to_string().c_str());
    FixedPoint<2, 8> fp_div_5(1.5);
    printf("\tFP_Div_5: %s\n", fp_div_5.to_string().c_str());
    FixedPoint<2, 8> fp_div_6 = fp_div_5 / 1;
    printf("\tFP_Div_6 = FP_Div_5 / 1: %s\n", fp_div_6.to_string().c_str());
    printf("\n");

    std::cout << std::flush;
    puts("4. Test Comparison Operator of FixedPoint");

    std::cout << std::flush;
    puts("5. Test Conversion Operator of FixedPoint");

    std::cout << std::flush;
    puts("6. Test Sin Function of FixedPoint");
    FixedPoint<3, 30> fp_sin_1(1.5); 
    printf("\tFP_Sin_1:%s\n",fp_sin_1.to_string().c_str());
    FixedPoint<3, 30> fp_sin_2 = fp_sin_1.sin(); 
    printf("\tFP_Sin_2 = sin(FP_Sin_1) = %s\n",fp_sin_2.to_string().c_str());
    FixedPoint<3, 30> fp_sin_3(PI);
    printf("\tFP_Sin_3:%s\n", fp_sin_3.to_string().c_str());
    FixedPoint<3, 30> fp_sin_4 = fp_sin_3.sin();
    printf("\tFP_Sin_4 = sin(FP_Sin_3) = %s\n", fp_sin_4.to_string().c_str());
    FixedPoint<3, 30> fp_sin_5(-PI);
    printf("\tFP_Sin_5:%s\n", fp_sin_5.to_string().c_str());
    FixedPoint<3, 30> fp_sin_6 = fp_sin_5.sin();
    printf("\tFP_Sin_6 = sin(FP_Sin_5) = %s\n", fp_sin_6.to_string().c_str());
    FixedPoint<3, 30> fp_sin_7(0);
    printf("\tFP_Sin_7:%s\n", fp_sin_7.to_string().c_str());
    FixedPoint<3, 30> fp_sin_8 = fp_sin_7.sin();
    printf("\tFP_Sin_8 = sin(FP_Sin_7) = %s\n", fp_sin_8.to_string().c_str());
    FixedPoint<3, 30> fp_sin_9(1.5*PI);
    printf("\tFP_Sn_9:%s\n", fp_sin_9.to_string().c_str());
    FixedPoint<3, 30> fp_sin_10 = fp_sin_9.sin();
    printf("\tFP_Sin_10 = sin(FP_Sin_9) = %s\n", fp_sin_10.to_string().c_str());
    FixedPoint<3, 30> fp_sin_11(2.0);
    printf("\tFP_Sin_11:%s\n", fp_sin_11.to_string().c_str());
    FixedPoint<3, 30> fp_sin_12 = fp_sin_11.sin();
    printf("\tFP_Sin_20 = sin(FP_Sin_11) = %s\n", fp_sin_12.to_string().c_str());
    FixedPoint<3, 30> fp_sin_13(0.5);
    printf("\tFP_Sin_13:%s\n", fp_sin_13.to_string().c_str());
    FixedPoint<3, 30> fp_sin_14 = fp_sin_13.sin();
    printf("\tFP_Sin_14 = sin(FP_Sin_13) = %s\n", fp_sin_14.to_string().c_str());
    FixedPoint<3, 30> fp_sin_15(2*PI); // 2 * pi
    printf("\tFP_Sin_15:%s\n", fp_sin_15.to_string().c_str());
    FixedPoint<3, 30> fp_sin_16 = fp_sin_15.sin();
    printf("\tFP_Sin_16 = sin(FP_Sin_15) = %s\n", fp_sin_16.to_string().c_str());
    FixedPoint<3, 30> fp_sin_17(-1.0);
    printf("\tFP_Sin_17:%s\n", fp_sin_17.to_string().c_str());
    FixedPoint<3, 30> fp_sin_18 = fp_sin_17.sin();
    printf("\tFP_Sin_18 = sin(FP_Sin_17) = %s\n", fp_sin_18.to_string().c_str());
    FixedPoint<3, 30> fp_sin_19(7.0); 
    printf("\tFP_Sin_19:%s\n", fp_sin_19.to_string().c_str());
    FixedPoint<3, 30> fp_sin_20 = fp_sin_19.sin();
    printf("\tFP_Sin_20 = sin(FP_Sin_19) = %s\n", fp_sin_20.to_string().c_str());

    puts("7. Test Cos Function of FixedPoint");
    FixedPoint<3, 30> fp_cos_1(1.1); 
    printf("\tFP_Cos_1:%s\n",fp_cos_1.to_string().c_str());
    FixedPoint<3, 30> fp_cos_2 = fp_cos_1.cos(); 
    printf("\tFP_Cos_2 = cos(FP_Cos_1) = %s\n",fp_cos_2.to_string().c_str());

    FixedPoint<3, 30> fp_cos_3(PI);
    printf("\tFP_Cos_3:%s\n", fp_cos_3.to_string().c_str());
    FixedPoint<3, 30> fp_cos_4 = fp_cos_3.cos();
    printf("\tFP_Cos_4 = cos(FP_Cos_3) = %s\n", fp_cos_4.to_string().c_str());

    FixedPoint<3, 30> fp_cos_5(-PI);
    printf("\tFP_Cos_5:%s\n", fp_cos_5.to_string().c_str());
    FixedPoint<3, 30> fp_cos_6 = fp_cos_5.cos();
    printf("\tFP_Cos_6 = cos(FP_Cos_5) = %s\n", fp_cos_6.to_string().c_str());

    FixedPoint<3, 30> fp_cos_7(0);
    printf("\tFP_Cos_7:%s\n", fp_cos_7.to_string().c_str());
    FixedPoint<3, 30> fp_cos_8 = fp_cos_7.cos();
    printf("\tFP_Cos_8 = cos(FP_Cos_7) = %s\n", fp_cos_8.to_string().c_str());

    FixedPoint<3, 30> fp_cos_9(1.5*PI);
    printf("\tFP_Cos_9:%s\n", fp_cos_9.to_string().c_str());
    FixedPoint<3, 30> fp_cos_10 = fp_cos_9.cos();
    printf("\tFP_Cos_10 = cos(FP_Cos_9) = %s\n", fp_cos_10.to_string().c_str());

    FixedPoint<3, 30> fp_cos_11(2.0);
    printf("\tFP_Cos_11:%s\n", fp_cos_11.to_string().c_str());
    FixedPoint<3, 30> fp_cos_12 = fp_cos_11.cos();
    printf("\tFP_Cos_12 = cos(FP_Cos_11) = %s\n", fp_cos_12.to_string().c_str());

    FixedPoint<3, 30> fp_cos_13(0.5);
    printf("\tFP_Cos_13:%s\n", fp_cos_13.to_string().c_str());
    FixedPoint<3, 30> fp_cos_14 = fp_cos_13.cos();
    printf("\tFP_Cos_14 = cos(FP_Cos_13) = %s\n", fp_cos_14.to_string().c_str());

    FixedPoint<3, 30> fp_cos_15(2*PI); // 2 * pi
    printf("\tFP_Cos_15:%s\n", fp_cos_15.to_string().c_str());
    FixedPoint<3, 30> fp_cos_16 = fp_cos_15.cos();
    printf("\tFP_Cos_16 = cos(FP_Cos_15) = %s\n", fp_cos_16.to_string().c_str());

    FixedPoint<3, 30> fp_cos_17(-1.0);
    printf("\tFP_Cos_17:%s\n", fp_cos_17.to_string().c_str());
    FixedPoint<3, 30> fp_cos_18 = fp_cos_17.cos();
    printf("\tFP_Cos_18 = cos(FP_Cos_17) = %s\n", fp_cos_18.to_string().c_str());

    FixedPoint<3, 30> fp_cos_19(7.0); 
    printf("\tFP_Cos_19:%s\n", fp_cos_19.to_string().c_str());
    FixedPoint<3, 30> fp_cos_20 = fp_cos_19.cos();
    printf("\tFP_Cos_20 = cos(FP_Cos_19) = %s\n", fp_cos_20.to_string().c_str());
}