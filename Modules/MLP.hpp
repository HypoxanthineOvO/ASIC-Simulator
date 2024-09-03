#ifndef MLP_HPP_
#define MLP_HPP_

#include "core.hpp"
#include <vector>

class MLP {
/* A Layer of MLP, which be implemented as a systolic array. */
public:
    using Data_Type = float;
    using Feature = Vector<Data_Type>;

    MLP() = delete;
    MLP(uint32_t input_size, uint32_t output_size, 
        Activation activation_function = Activation::NONE, 
        SystolicArraySize systolic_array_size = {32, 32}
    ): input_size(input_size), output_size(output_size), activation_function(activation_function), systolic_array_size(systolic_array_size) {
        weight = Matrix<Data_Type>(output_size, input_size);
        bias = Vector<Data_Type>(output_size);
    };

    void loadParameters(const Matrix<Data_Type>& weight, const Vector<Data_Type>& bias) {
        this->weight = weight;
        this->bias = bias;
    };

    Feature forward(const Feature& input) {
        Vector<Data_Type> raw = weight * input + bias;
        Vector<Data_Type> result = Do_Activation(raw, activation_function);
        return result;
    };

    uint32_t getCycle() {
        /* Compute Cycle of systolic array */
        // TODO: Design the cycle simulation
        return 0;
    }
private:
    /* Hyper Parameters */
    uint32_t input_size;
    uint32_t output_size;
    Activation activation_function;

    /* Parameters */
    Matrix<Data_Type> weight;
    Vector<Data_Type> bias;

    /* Hardware Simulation */
    SystolicArraySize systolic_array_size;
};

#endif // MLP_HPP_