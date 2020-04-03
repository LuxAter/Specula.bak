/**
 * @file constants.hpp
 * @brief Defines common constants
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2020-03-30
 * @ingroup global global-constants
 */
#ifndef SPECULA_GLOBAL_CONSTANTS_HPP_
#define SPECULA_GLOBAL_CONSTANTS_HPP_

/**
 * @defgroup global-constants Global Constants
 * @ingroup global
 *
 * A collection of commonly used constant values.
 */

#include <limits>

#include "compiler.hpp"
#include "declarations.hpp"

namespace specula {

#if SPECULA_COMPILER_IS_MSVC == 1
/**
 * @brief Maximum floating point value.
 * @ingroup global-constants
 * @bug Specialization for MSVC.
 */
#define MAX_FLOAT std::numeric_limits<Float>::max()
/**
 * @brief Inifinity representation for floating point value.
 * @ingroup global-constants
 * @bug Specialization for MSVC.
 */
#define INFTY std::numeric_limits<Float>::infinity()
/**
 * @brief Machine epsilon for floating point type.
 * @ingroup global-constants
 * @bug Specialization for MSVC.
 */
#define MACHINE_EPSILON (std::numeric_limits<Float>::epsilon() * 0.5)
#else
/**
 * @brief Maximum floating point value.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float MAX_FLOAT = std::numeric_limits<Float>::max();
/**
 * @brief Inifinity representation for floating point value.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float INFTY = std::numeric_limits<Float>::infinity();
/**
 * @brief Machine epsilon for floating point type.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float MACHINE_EPSILON = std::numeric_limits<Float>::epsilon() * 0.5;
#endif

/**
 * @brief Offset for shadow rays.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float SHADOW_EPSILON = 0.0001f;
/**
 * @brief \f$\pi\f$.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float PI = 3.14159265358979323846;
/**
 * @brief \f$\pi^{-1}\f$.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float INV_PI = 0.31830988618379067154;
/**
 * @brief \f${(2\pi)}^{-1}\f$.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float INV_2PI = 0.15915494309189533577;
/**
 * @brief \f${(4\pi)}^{-1}\f$.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float INV_4PI = 0.07957747154594766788;
/**
 * @brief \f$\pi\mathbin{/}2\f$.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float PI_OVER2 = 1.57079632679489661923;
/**
 * @brief \f$\pi\mathbin{/}4\f$.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float PI_OVER4 = 0.78539816339744830961;
/**
 * @brief \f$\sqrt{2}\f$.
 * @ingroup global-constants
 */
static SPECULA_CONSTEXPR Float SQRT2 = 1.41421356237309504880;

} // namespace specula

#endif /* end of include guard: SPECULA_GLOBAL_CONSTANTS_HPP_ */
