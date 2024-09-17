#ifndef CORE_HPP_
#define CORE_HPP_

#include <Eigen/Core>
#include <Eigen/Dense>
#include <type.hpp>

/* Hardware Simulation */
using SystolicArraySize = std::pair<uint32_t, uint32_t>;


/* Eigen Matrix Type Definition */
template <typename DATA_TYPE>
using Matrix = Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic>;
template <typename DATA_TYPE>
using Vector = Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, 1>;

/* Activation Functions */
typedef enum {
    NONE,
    SIGMOID,
    RELU,
    LEAKY_RELU
} Activation;

// Operation on single element
template <typename DATA_TYPE>
DATA_TYPE sigmoid(DATA_TYPE x) {
    return 1 / (1 + exp(-x));
}
template <typename DATA_TYPE>
DATA_TYPE relu(DATA_TYPE x) {
    return x > 0 ? x : 0;
}
template <typename DATA_TYPE>
DATA_TYPE leaky_relu(DATA_TYPE x, DATA_TYPE alpha = 0.01) {
    return x > 0 ? x : alpha * x;
}
// Operation on Eigen Vector, using operation on single element
template <typename DATA_TYPE>
Vector<DATA_TYPE> sigmoid(const Vector<DATA_TYPE>& x) {
    Vector<DATA_TYPE> res(x.size());
    for (int i = 0; i < x.size(); i++) {
        res(i) = sigmoid(x(i));
    }
    return res;
}
template <typename DATA_TYPE>
Vector<DATA_TYPE> relu(const Vector<DATA_TYPE>& x) {
    Vector<DATA_TYPE> res(x.size());
    for (int i = 0; i < x.size(); i++) {
        res(i) = relu(x(i));
    }
    return res;
}
template <typename DATA_TYPE>
Vector<DATA_TYPE> leaky_relu(const Vector<DATA_TYPE>& x, DATA_TYPE alpha = 0.1) {
    Vector<DATA_TYPE> res(x.size());
    for (int i = 0; i < x.size(); i++) {
        res(i) = leaky_relu(x(i), alpha);
    }
    return res;
}
// Activation Function Selector
template <typename DATA_TYPE>
Vector<DATA_TYPE> Do_Activation(const Vector<DATA_TYPE>& x, Activation act) {
    switch (act) {
        case NONE:
            return x;
        case SIGMOID:
            return sigmoid(x);
        case RELU:
            return relu(x);
        case LEAKY_RELU:
            return leaky_relu(x);
        default:
            return Vector<DATA_TYPE>::Zero(x.size());
    }
}

#endif // CORE_HPP_