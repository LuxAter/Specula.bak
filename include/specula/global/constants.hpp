#ifndef SPECULA_GLOBAL_CONSTANTS_HPP_
#define SPECULA_GLOBAL_CONSTANTS_HPP_

#include "compiler.hpp"
#include "includes.hpp"
#include "types.hpp"

namespace specula {
#ifdef _MSC_VER
#define MAX_FLOAT std::numeric_limits<Float>::max();
#define INFINITY std::numeric_limits<Float>::infinity();
#else
static SPECULA_CONSTEXPR Float MAX_FLOAT = std::numeric_limits<Float>::max();
static SPECULA_CONSTEXPR Float INFTY = std::numeric_limits<Float>::infinity();
#endif
#ifdef _MSC_VER
#define MACHINE_EPSILON (std::numeric_limits<Float>::epsilon() * 0.5)
#else
static SPECULA_CONSTEXPR Float MACHINE_EPSILON =
    std::numeric_limits<Float>::epsilon() * 0.5;
#endif
static SPECULA_CONSTEXPR Float SHADOW_EPSILON = 0.0001f;
static SPECULA_CONSTEXPR Float PI = 3.14159265358979323846;
static SPECULA_CONSTEXPR Float InvPi = 0.31830988618379067154;
static SPECULA_CONSTEXPR Float Inv2Pi = 0.15915494309189533577;
static SPECULA_CONSTEXPR Float Inv4Pi = 0.07957747154594766788;
static SPECULA_CONSTEXPR Float PiOver2 = 1.57079632679489661923;
static SPECULA_CONSTEXPR Float PiOver4 = 0.78539816339744830961;
static SPECULA_CONSTEXPR Float Sqrt2 = 1.41421356237309504880;

} // namespace specula

#endif // SPECULA_GLOBAL_CONSTANTS_HPP_