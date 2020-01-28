#ifndef SPECULA_NORMAL_HPP_
#define SPECULA_NORMAL_HPP_

#include "normal/normal2.hpp"
#include "normal/normal3.hpp"
#include "normal/normal4.hpp"

/**
 * @defgroup Normal
 * @ingroup Math
 * @brief Standard `Normal` classes and operations
 *
 * This module implements three standard normal classes and several operations
 * that act on these types. Specifically this module implements `Normal2<T>`,
 * `Normal3<T>`, and `Normal4<T>`.
 *
 * A *surface normal* is a vector that is perpendicular to a surface at a
 * particular position. It can be defined as the cross product of any two
 * non-parallel vectors that are tangent to the surface at a point. Although
 * normals are similar to vectors, it is important to distinguish between the
 * two of them, because normals are defined in terms of their relationship to a
 * particular surface, they behave differently than vectors in some situations,
 * particularly when applying transformations.
 *
 * The implementation of a normal is very similar to the implementation of
 * `Vector`, the main difference is that a normal cannot be added to a point,
 * and it is not possible to take the cross product of two normals.
 *
 * @note Due to unfortunate terminology normals are not necessarily normalized.
 *
 */

#endif // SPECULA_NORMAL_HPP_
