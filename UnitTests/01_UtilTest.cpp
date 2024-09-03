#include <iostream>
#include "core.hpp"

int main() {
    puts("==================== Unit Test Of Utils ====================");
    using TestType = float;
    /* Test Matmul */

    /* Test Activation Functions */
    Vector<TestType> test_vector(5);
    for (int i = 0; i < 5; i++) {
        test_vector(i) = i - 2;
    }
    printf("Vec: ");
    for (int i = 0; i < 5; i++) {
        printf("%f ", test_vector(i));
    }
    printf("\n");
    // None
    Vector<TestType> none_res = Do_Activation(test_vector, Activation::NONE);
    printf("None: ");
    for (int i = 0; i < 5; i++) {
        printf("%f ", none_res(i));
    }
    printf("\n");
    // Sigmoid
    Vector<TestType> sigmoid_res = Do_Activation(test_vector, Activation::SIGMOID);
    printf("Sigmoid: ");
    for (int i = 0; i < 5; i++) {
        printf("%f ", sigmoid_res(i));
    }
    printf("\n");
    // ReLU
    Vector<TestType> relu_res = Do_Activation(test_vector, Activation::RELU);
    printf("ReLU: ");
    for (int i = 0; i < 5; i++) {
        printf("%f ", relu_res(i));
    }
    printf("\n");
    // Leaky ReLU
    Vector<TestType> leaky_relu_res = Do_Activation(test_vector, Activation::LEAKY_RELU);
    printf("Leaky ReLU: ");
    for (int i = 0; i < 5; i++) {
        printf("%f ", leaky_relu_res(i));
    }
    printf("\n");

}