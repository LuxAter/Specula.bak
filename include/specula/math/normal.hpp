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
 * These classes are distinct from the vector class, as there are some key
 * differences between a normal and a vector. Consider the case with a surface
 * \f$ S\f$, and a normal \f$\mathbf{n}\f$. Uppon the application of a
 * transformation \f$ T\f$, if one would treat the normal as if it were a
 * vector, then the transformed normal is not gaurrentted to still be normal,
 * thus the normal class must be treated differently by transformation.
 *
 */

#endif // SPECULA_NORMAL_HPP_