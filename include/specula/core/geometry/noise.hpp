#ifndef SPECULA_CORE_GEOMETRY_NOISE_HPP_
#define SPECULA_CORE_GEOMETRY_NOISE_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {
GLM_FUNC(perlin, x);
GLM_FUNC(perlin, x, rep);
GLM_FUNC(simplex, x);
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_NOISE_HPP_