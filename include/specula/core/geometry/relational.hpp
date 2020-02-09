#ifndef SPECULA_CORE_GEOMETRY_RELATIONAL_HPP_
#define SPECULA_CORE_GEOMETRY_RELATIONAL_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {

GLM_FUNC(all, v);
GLM_FUNC(any, v);
GLM_FUNC(equal, x, y);
GLM_FUNC_NAME(greater_than, greaterThan, x, y);
GLM_FUNC_NAME(greater_than_equal, greaterThanEqual, x, y);
GLM_FUNC_NAME(less_than, lessThan, x, y);
GLM_FUNC_NAME(less_than_equal, lessThanEqual, x, y);
GLM_FUNC(not_, v);
GLM_FUNC_NAME(not_equal, notEqual, x, y);

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_RELATIONAL_HPP_