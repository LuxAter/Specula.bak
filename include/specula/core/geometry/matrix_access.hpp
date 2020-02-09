#ifndef SPECULA_CORE_GEOMETRY_MATRIX_ACCESS_HPP_
#define SPECULA_CORE_GEOMETRY_MATRIX_ACCESS_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {
GLM_FUNC(column, m, index);
GLM_FUNC(column, m, index, x);
GLM_FUNC(row, m, index);
GLM_FUNC(row, m, index, x);
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_MATRIX_ACCESS_HPP_