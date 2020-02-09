#ifndef SPECULA_CORE_GEOMETRY_TRIGONOMETRY_HPP_
#define SPECULA_CORE_GEOMETRY_TRIGONOMETRY_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {
GLM_FUNC(acos, x);
GLM_FUNC(acosh, x);
GLM_FUNC(asin, x);
GLM_FUNC(asinh, x);
GLM_FUNC(atan, y, x);
GLM_FUNC(atan, y_over_x);
GLM_FUNC(atanh, x);
GLM_FUNC(cos, angle);
GLM_FUNC(cosh, angle);
GLM_FUNC(degrees, radians);
GLM_FUNC(radians, degrees);
GLM_FUNC(sin, angle);
GLM_FUNC(sinh, angle);
GLM_FUNC(tan, angle);
GLM_FUNC(tanh, angle);

GLM_FUNC(acot, x);
GLM_FUNC(acoth, x);
GLM_FUNC(acsc, x);
GLM_FUNC(acsch, x);
GLM_FUNC(asec, x);
GLM_FUNC(asech, x);
GLM_FUNC(cot, angle);
GLM_FUNC(coth, angle);
GLM_FUNC(csc, angle);
GLM_FUNC(csch, angle);
GLM_FUNC(sec, angle);
GLM_FUNC(sech, angle);
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_TRIGONOMETRY_HPP_