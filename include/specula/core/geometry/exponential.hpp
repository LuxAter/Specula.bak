#ifndef SPECULA_CORE_GEOMETRY_EXPONENTIAL_HPP_
#define SPECULA_CORE_GEOMETRY_EXPONENTIAL_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {
GLM_FUNC(exp, x);
GLM_FUNC(exp2, x);
GLM_FUNC(inversesqrt, x);
GLM_FUNC(log, x);
GLM_FUNC(log2, x);
GLM_FUNC(pow, x, y);
GLM_FUNC(sqrt, x);
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_EXPONENTIAL_HPP_