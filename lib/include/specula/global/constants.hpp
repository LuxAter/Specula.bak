#ifndef SPECULA_GLOBAL_CONSTANTS_HPP_
#define SPECULA_GLOBAL_CONSTANTS_HPP_

#include <limits>

#include "compiler.hpp"

namespace specula {
typedef float Float;

#if SPECULA_COMPILER_IS_MSVC == 1
#define MAX_FLOAT std::numeric_limits<Float>::max()
#define INFTY std::numeric_limits<Float>::infinity()
#define MACHINE_EPSILON (std::numeric_limits<Float>::epsilon() * 0.5)
#else
static SPECULA_CONSTEXPR Float MAX_FLOAT = std::numeric_limits<Float>::max();
static SPECULA_CONSTEXPR Float INFTY = std::numeric_limits<Float>::infinity();
static SPECULA_CONSTEXPR Float MACHINE_EPSILON =
    std::numeric_limits<Float>::epsilon() * 0.5;
#endif

static SPECULA_CONSTEXPR Float SHADOW_EPSILON = 0.0001f;
static SPECULA_CONSTEXPR Float PI = 3.14159265358979323846;
static SPECULA_CONSTEXPR Float INV_PI = 0.31830988618379067154;
static SPECULA_CONSTEXPR Float INV_2PI = 0.15915494309189533577;
static SPECULA_CONSTEXPR Float INV_4PI = 0.07957747154594766788;
static SPECULA_CONSTEXPR Float PI_OVER2 = 1.57079632679489661923;
static SPECULA_CONSTEXPR Float PI_OVER4 = 0.78539816339744830961;
static SPECULA_CONSTEXPR Float SQRT2 = 1.41421356237309504880;

} // namespace specula

#endif /* end of include guard: SPECULA_GLOBAL_CONSTANTS_HPP_ */
