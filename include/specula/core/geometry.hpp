#ifndef SPECULA_GEOMETRY_HPP_
#define SPECULA_GEOMETRY_HPP_

/**
 * @defgroup Geometry
 * @ingroup Core
 * @brief General geometric functions and classes
 *
 * This module contains common mathematical function, classes and operations
 * that are used across the Specula renderer, and are available for any external
 * programs to use. The functions and classes contained within this module are
 * specialized for the usage in the renderer, and thus have been optimized for
 * their use.
 *
 * @note This modules not not provide generic mathematical classes, such as \f$
 * N\times M \f$ Matrix. Instead specialized and optimized classes are available
 * such as a specific \f$ 2\times 2\f$ Matrix.
 *
 */

#include "geometry/bounds.hpp"
#include "geometry/common.hpp"
#include "geometry/normal.hpp"
#include "geometry/point.hpp"
#include "geometry/ray.hpp"
#include "geometry/vector.hpp"

#endif // SPECULA_GEOMETRY_HPP_