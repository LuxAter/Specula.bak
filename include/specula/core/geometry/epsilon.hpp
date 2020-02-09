#ifndef SPECULA_CORE_GEOMETRY_EPSILON_HPP_
#define SPECULA_CORE_GEOMETRY_EPSILON_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {
GLM_FUNC_NAME(epsilon_equal, epsilonEqual, x, y, epsilon);
GLM_FUNC_NAME(epsilon_not_equal, epsilonNotEqual, x, y, epsilon);
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_EPSILON_HPP_