#ifndef SPECULA_POINT_HPP_
#define SPECULA_POINT_HPP_

#include "point/point2.hpp"
#include "point/point3.hpp"
#include "point/point4.hpp"

/**
 * @defgroup Point
 * @ingroup Math
 * @brief Standard `Point` classes and operations
 *
 * This module implements three standard point classes and several operations
 * that act on these types. Specifically this module implements `Point2<T>`,
 * `Point3<T>`, and `Point4<T>`.
 *
 * Implementing points distinctly form the vector class, as points are treated
 * differently by transformations than vectors. For example points are effected
 * by the translational component of transformations, while vectors will not be.
 *
 */

#endif // SPECULA_POINT_HPP_