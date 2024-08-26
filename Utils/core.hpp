#ifndef CORE_HPP_
#define CORE_HPP_

#include <Eigen/Core>
#include <Eigen/Dense>
#include <type.hpp>



/* Eigen Matrix Type Definition */
template <typename DATA_TYPE>
using Matrix = Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, Eigen::Dynamic>;
template <typename DATA_TYPE>
using Vector = Eigen::Matrix<DATA_TYPE, Eigen::Dynamic, 1>;

#endif // CORE_HPP_