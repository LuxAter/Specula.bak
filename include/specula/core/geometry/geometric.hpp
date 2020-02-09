#ifndef SPECULA_CORE_GEOMETRY_GEOMETRIC_HPP_
#define SPECULA_CORE_GEOMETRY_GEOMETRIC_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {
GLM_FUNC(cross, x, y);
GLM_FUNC(distance, p0, p1);
GLM_FUNC(dot, x, y)
GLM_FUNC(faceforward, n, i, n_ref);
GLM_FUNC(length, x);
GLM_FUNC(normalize, x);
GLM_FUNC(reflect, i, n);
GLM_FUNC(refract, i, n, eta);

GLM_FUNC(determinant, m);
GLM_FUNC(inverse, m);
GLM_FUNC_NAME(affine_inverse, affineInverse, m);
GLM_FUNC_NAME(inverse_transpose, inverseTranspose, m);
GLM_FUNC_NAME(matrix_comp_mult, matrixCompMult, x, y);
GLM_FUNC_NAME(outer_product, outerProduct, c, r);
GLM_FUNC(transpose, x);
GLM_FUNC_NAME(look_at, lookAt, eye, center, up);
GLM_FUNC_NAME(look_at_lh, lookAtLH, eye, center, up);
GLM_FUNC_NAME(look_at_rh, lookAtRH, eye, center, up);
GLM_FUNC(rotate, m, angle, axis);
GLM_FUNC(scale, m, v);
GLM_FUNC(translate, m, v);

GLM_FUNC(conjugate, q);
GLM_FUNC_NAME(euler_angles, eulerAngles, x);
GLM_FUNC(pitch, x);
GLM_FUNC_NAME(quat_look_at, quatLookAt, direction, up);
GLM_FUNC_NAME(quat_look_at_lh, quatLookAtLH, direction, up);
GLM_FUNC_NAME(quat_look_at_rh, quatLookAtRH, direction, up);
GLM_FUNC(roll, x);
GLM_FUNC(yaw, x);
GLM_FUNC(lerp, x, y, a);
GLM_FUNC(slerp, x, y, a);

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_GEOMETRIC_HPP_