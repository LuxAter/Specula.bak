#ifndef SPECULA_CORE_GEOMETRY_COMMON_HPP_
#define SPECULA_CORE_GEOMETRY_COMMON_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {

GLM_FUNC(abs, x);
GLM_FUNC(ceil, x);
GLM_FUNC(clamp, x, min_val, max_val);
GLM_FUNC_NAME(float_bits_to_int, floatBitsToInt, value);
GLM_FUNC_NAME(float_bits_to_uint, floatBitsToUint, value);
GLM_FUNC(floor, x);
GLM_FUNC(fma, a, b, c);
GLM_FUNC(fract, x);
GLM_FUNC(frexp, x, exp);
GLM_FUNC_NAME(int_bits_to_float, intBitsToFloat, value);
GLM_FUNC(isinf, x);
GLM_FUNC(isnan, x);
GLM_FUNC(ldexp, x, exp);
GLM_FUNC(max, x, y);
GLM_FUNC(min, x, y);
GLM_FUNC(mix, x, y, a);
GLM_FUNC(mod, x, y);
GLM_FUNC(modf, x, i);
GLM_FUNC(round, x);
GLM_FUNC_NAME(round_even, roundEven, x);
GLM_FUNC(sign, x);
GLM_FUNC(smoothstep, edge0, edge1, x);
GLM_FUNC(step, edge, x);
GLM_FUNC(trunc, x);
GLM_FUNC_NAME(uint_bits_to_float, uintBitsToFloat, value);

GLM_FUNC_NAME(component_add, compAdd, v);
GLM_FUNC_NAME(component_max, compMax, v);
GLM_FUNC_NAME(component_min, compMin, v);
GLM_FUNC_NAME(component_mul, compMul, v);
GLM_FUNC_NAME(component_normalize, compNormalize, v);
GLM_FUNC_NAME(component_scale, compScale, v);

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_COMMON_HPP_
