#ifndef SPECULA_CORE_GEOMETRY_RANDOM_HPP_
#define SPECULA_CORE_GEOMETRY_RANDOM_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {
GLM_FUNC_NAME(ball_rand, ballRand, radius);
GLM_FUNC_NAME(circular_rand, circularRand, radius);
GLM_FUNC_NAME(disk_rand, diskRand, radius);
GLM_FUNC_NAME(gauss_rand, gaussRand, mean, deviation);
GLM_FUNC_NAME(linear_rand, linearRand, min_val, max_val);
GLM_FUNC_NAME(spherical_rand, sphericalRand, radius);
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_RANDOM_HPP_