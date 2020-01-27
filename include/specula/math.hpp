#ifndef SPECULA_MATH_HPP_
#define SPECULA_MATH_HPP_

#include "math/bounds.hpp"
#include "math/common.hpp"
#include "math/geometric.hpp"
#include "math/matrix.hpp"
#include "math/normal.hpp"
#include "math/point.hpp"
#include "math/ray.hpp"
#include "math/ray_differential.hpp"
#include "math/vector.hpp"

/**
 * @defgroup Math
 * @brief General mathematical functions and classes
 *
 * This module contains common mathematical functions, classes and operations
 * that are used across the Specula renderer, and are available for any external
 * programs to use. The functions and classes contained within this module are
 * specialized for the useage in the renderer, and thus have been optimized for
 * their use.
 *
 * @note This module does not provide generic mathematical classes, such as an
 * \f$ N\times M \f$ Matrix. Instead specialized and optimized classes are
 * available such as a specific \f$ 2\times 2\f$ Matrix.
 */

#endif // SPECULA_MATH_HPP_