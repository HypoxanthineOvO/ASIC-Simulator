#ifndef TYPE_HPP_
#define TYPE_HPP_
#include <cmath>
#include <iostream>

/* Fixed Point Datatype */
#include "FixedPoint.hpp"

/* Floating Point Datatype */
#include "FloatingPoint.hpp"

using Half = FloatingPoint<5, 10>;
using Float = FloatingPoint<8, 23>;
using Double = FloatingPoint<11, 52>;




#endif // TYPE_HPP_