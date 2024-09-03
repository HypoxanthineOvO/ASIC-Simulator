#include <iostream>
#include "MLP.hpp"


int main() {
    puts("==================== Unit Test Of MLP ====================");
    using TestType = float;
    MLP mlp(4, 4);

    Matrix<TestType> Test_Params(4, 4);
    Test_Params <<
        -0.0037,  0.2682, -0.4115, -0.3680,
        -0.1926,  0.1341, -0.0099,  0.3964,
        -0.0444,  0.1323, -0.1511, -0.0983,
        -0.4777, -0.3311, -0.2061,  0.0185;
    Vector<TestType> Test_Bias(4);
    Test_Bias <<  0.1977,  0.3000, -0.3390, -0.2177;
    
    Vector<TestType> input(4);
    for (int i = 0; i < 4; i++) {
        input(i) = i;
    }
    printf("Input: ");
    for (int i = 0; i < 4; i++) {
        printf("%f ", input(i));
    }
    printf("\n");

    mlp.loadParameters(Test_Params, Test_Bias);
    Vector<TestType> output = mlp.forward(input);
    printf("Output: ");
    for (int i = 0; i < 4; i++) {
        printf("%f ", output(i));
    }
    printf("\n");
}