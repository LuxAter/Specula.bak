/**
 * @file functions.hpp
 * @brief Global inline functions
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2020-03-30
 * @ingroup global global-functions
 */
#ifndef SPECULA_GLOBAL_FUNCTIONS_HPP_
#define SPECULA_GLOBAL_FUNCTIONS_HPP_

/**
 * @defgroup global-functions Global Functions
 * @ingroup global
 *
 * A collection of commonly used functions.
 */

#include "compiler.hpp"
#include "constants.hpp"
#include "include.hpp"
#include <type_traits>

namespace specula {
/**
 * @brief Converts floating pint to binary representation
 * @ingroup global-functions
 *
 * @param f Floating point value to convert
 *
 * @return Bit representation of the floating point value
 */
inline std::uint32_t float_to_bits(float f) {
  std::uint32_t ui;
  std::memcpy(&ui, &f, sizeof(float));
  return ui;
}
/**
 * @brief Converts floating pint to binary representation
 * @ingroup global-functions
 *
 * @param f Floating point value to convert
 *
 * @return Bit representation of the floating point value
 */
inline std::uint64_t float_to_bits(double f) {
  std::uint64_t ui;
  std::memcpy(&ui, &f, sizeof(double));
  return ui;
}
/**
 * @brief Converts binary value to floating point representation
 * @ingroup global-functions
 *
 * @param ui Binary representation of a floating point value
 *
 * @return The floating point value represented by ``ui``
 */
inline float bits_to_float(std::uint32_t ui) {
  float f;
  memcpy(&f, &ui, sizeof(std::uint32_t));
  return f;
}
/**
 * @brief Converts binary value to floating point representation
 * @ingroup global-functions
 *
 * @param ui Binary representation of a floating point value
 *
 * @return The floating point value represented by ``ui``
 */
inline double bits_to_float(std::uint64_t ui) {
  double f;
  memcpy(&f, &ui, sizeof(std::uint64_t));
  return f;
}

/**
 * @brief Computes the next possible representation of a ``float``
 * @ingroup global-functions
 *
 * @param v Current floating point value
 *
 * @return Next higher representable floating point value
 */
inline float next_float_up(float v) {
  if (std::isinf(v) && v > 0.0f)
    return v;
  if (v == -0.0f)
    v = 0.0f;
  std::uint32_t ui = float_to_bits(v);
  if (v >= 0)
    ++ui;
  else
    --ui;
  return bits_to_float(ui);
}
/**
 * @brief Computes the next possible representation of a ``double``
 * @ingroup global-functions
 *
 * @param v Current floating point value
 *
 * @return Next higher representable floating point value
 */
inline double next_float_up(double v) {
  if (std::isinf(v) && v > 0.0f)
    return v;
  if (v == -0.0f)
    v = 0.0f;
  std::uint64_t ui = float_to_bits(v);
  if (v >= 0)
    ++ui;
  else
    --ui;
  return bits_to_float(ui);
}
/**
 * @brief Computes the previouse possible representation of a ``float``
 * @ingroup global-functions
 *
 * @param v Current floating point value
 *
 * @return Next lower representable floating point value
 */
inline float next_float_down(float v) {
  if (std::isinf(v) && v < 0.0f)
    return v;
  if (v == 0.0f)
    v = -0.0f;
  std::uint32_t ui = float_to_bits(v);
  if (v > 0)
    --ui;
  else
    ++ui;
  return bits_to_float(ui);
}
/**
 * @brief Computes the previouse possible representation of a ``double``
 * @ingroup global-functions
 *
 * @param v Current floating point value
 *
 * @return Next lower representable floating point value
 */
inline double next_float_down(double v) {
  if (std::isinf(v) && v < 0.0f)
    return v;
  if (v == 0.0f)
    v = -0.0f;
  std::uint64_t ui = float_to_bits(v);
  if (v > 0)
    --ui;
  else
    ++ui;
  return bits_to_float(ui);
}

SPECULA_CONSTEXPR inline Float gamma(int n) {
  return (n * MACHINE_EPSILON) / (1 - n * MACHINE_EPSILON);
}
/**
 * @brief Provides gamma correction
 * @ingroup global-functions
 *
 * Gamma correction allows for the transformation between linear intensity and
 * linear encoding. Linear encoding is characterised, by every increase in
 * value will result in a roughly constant increase in perceived brightness,
 * while linear intensity does not follow this rule.
 *
 * This can be explained as an image might have one part that appears to be
 * twice as bright as another. However, the pixels values won't have a
 * \f$2:1\f$ relationship. Thus this function maps from the \f$2:1\f$
 * pixel values to appropriate pixel values that will have a \f$2:1\f$
 * relationship of their apperent brightness.
 *
 * @param value Value to apply gamma correction to.
 *
 * @return ``value`` after gamma correction.
 */
inline Float gamma_correct(Float value) {
  if (value <= 0.0031308f)
    return 12.92 * value;
  return 1.055f * std::pow(value, static_cast<Float>(1.f / 2.4f)) - 0.055f;
}
/**
 * @brief Provides inverse gamma correction
 * @ingroup global-functions
 *
 * Gamma correction allows for the transformation between linear intensity and
 * linear encoding. Linear encoding is characterised, by every increase in
 * value will result in a roughly constant increase in perceived brightness,
 * while linear intensity does not follow this rule.
 *
 * This can be explained as an image might have one part that appears to be
 * twice as bright as another. However, the pixels values won't have a
 * \f$2:1\f$ relationship. Thus this function maps from the \f$2:1\f$
 * brightness to appropriate brightness that will have a \f$2:1\f$ relationship
 * of their pixel values.
 *
 * @param value Value to apply the inverse gamma correction to.
 *
 * @return ``value`` before gamma correction.
 */
inline Float inverse_gamma_correct(Float value) {
  if (value <= 0.04045f)
    return value * 1.0f / 12.92f;
  return std::pow((value + 0.055f) * 1.0f / 1.055f, static_cast<Float>(2.4f));
}

/**
 * @brief Clamps a value between bounds
 * @ingroup global-functions
 *
 * This is equivalent to
 * ```{cpp}
 * std::max(std::min(val, high), low);
 * ```
 *
 * @tparam T Type for the clamped value.
 * @tparam U Type for the minimum value.
 * @tparam V Type for the maximum value.
 * @param val Value to clamp between `low` and `high`.
 * @param low Value to clamp ``val`` above.
 * @param high Value to clamp ``val`` below.
 *
 * @return ``val`` clamped between ``low`` and ``high``.
 */
template <typename T, typename U, typename V>
inline T clamp(T val, U low, V high) {
  if (val < low)
    return low;
  else if (val > high)
    return high;
  return val;
}

template <typename T, typename U, typename V>
inline T smooth_step(T val, U low, V high) {
  T v = clamp((val - low) / (high - low), T(0), T(1));
  return v * v * (-2 * v + 3);
}
/**
 * @brief Computes the remainder of ``a/b``.
 * @ingroup global-functions
 *
 * This is overloaded inorder to ensure that the modulus of a negative number is
 * always positive.
 *
 * @tparam T Value type
 * @param a
 * @param b
 *
 * @return remainder of ``a/b``.
 */
template <typename T> inline T mod(T a, T b) {
  const T result = a - (a / b) * b;
  return static_cast<T>((result < 0) ? result + b : result);
}
/**
 * @brief Computes the remainder of ``a/b``
 * @ingroup global-functions
 *
 * This is overloaded inorder to ensure that the modulus of a negative number
 * is always positive. This is a specialization for floating point numbers.
 * This is equivalent to:
 * ```{cpp}
 * std::fmod(a, b);
 * ```
 *
 * @param a
 * @param b
 *
 * @return remainder of ``a/b``.
 */
template <> inline Float mod(Float a, Float b) { return std::fmod(a, b); }

/**
 * @brief Converts degrees to radians
 * @ingroup global-functions
 *
 * This is equivalent to:
 * \f[
 * \frac{\pi}{180}deg
 * \f]
 *
 * @param deg
 *
 * @return radian representation of ``deg``.
 */
SPECULA_CONSTEXPR inline Float radians(Float deg) {
  return (PI / 180.0f) * deg;
}
/**
 * @brief Converts radians to degrees
 * @ingroup global-functions
 *
 * This is equivalent to:
 * \f[
 * \frac{180}{\pi}rad
 * \f]
 *
 * @param rad
 *
 * @return degree representation of ``rad``.
 */
SPECULA_CONSTEXPR inline Float degrees(Float rad) {
  return (180.0f / PI) * rad;
}

/**
 * @brief Logarithm base-2
 * @ingroup global-functions
 *
 * This is computed using the identity
 * \f[
 * \log_2(x)=\frac{\log x}{\log 2}.
 * \f]
 *
 * @param x Value to take the logarithm of.
 *
 * @return The logarithm base-2 of ``x``.
 */
inline Float log2(Float x) {
  const Float inv_log2 = 1.442695040888963387004650940071;
  return std::log(x) * inv_log2;
}
/**
 * @brief Logarithm base-2 for integers
 * @ingroup global-functions
 *
 * An optimized implementation of base-2 logarithm for integers.
 *
 * @param v Value to take the logarithm of.
 *
 * @return The logarithm base-2 of ``v``.
 */
inline int log2(std::uint32_t v) {
#if SPECULA_COMPILER_IS_MSVC == 1
  unsigned long lz = 0;
  if (_BitScanReverse(&lz, v))
    return lz;
  return 0;
#else
  return 31 - __builtin_clz(v);
#endif
}
/**
 * @brief Logarithm base-2 for integers
 * @ingroup global-functions
 *
 * An optimized implementation of base-2 logarithm for integers.
 *
 * @param v Value to take the logarithm of.
 *
 * @return The logarithm base-2 of ``v``.
 */
inline int log2(std::uint64_t v) {
#if SPECULA_COMPILER_IS_MSVC == 1
  unsigned long int lz = 0;
#if defined(_WIN64)
  _BitScanReverse64(&lz, v);
#else
  if (_BitScanReverse(&lz, v >> 32))
    lz += 32;
  else
    _BitScanReverse(&lz, v & 0xffffffff);
#endif // _WIN64
  return lz;
#else
  return 63 - __builtin_clzll(v);
#endif
}
/**
 * @brief Logarithm base-2 for integers
 * @ingroup global-functions
 *
 * An optimized implementation of base-2 logarithm for integers.
 *
 * @param v Value to take the logarithm of.
 *
 * @return The logarithm base-2 of ``v``.
 */
inline int log2(std::int32_t v) { return log2(static_cast<std::uint32_t>(v)); }
/**
 * @brief Logarithm base-2 for integers
 * @ingroup global-functions
 *
 * An optimized implementation of base-2 logarithm for integers.
 *
 * @param v Value to take the logarithm of.
 *
 * @return The logarithm base-2 of ``v``.
 */
inline int log2(std::int64_t v) { return log2(static_cast<std::uint64_t>(v)); }

/**
 * @brief Checks of an integer is a power of 2.
 * @ingroup global-functions
 *
 * @tparam T Value type
 * @param v Value to test
 *
 * @return ``true`` if ``v`` is some power of 2, ``false`` otherwise.
 */
template <typename T> SPECULA_CONSTEXPR inline bool is_power_of_2(T v) {
  return v && !(v & (v - 1));
}
/**
 * @brief Rounds to the next power of 2
 * @ingroup global-functions
 *
 * @param v Value to round
 *
 * @return The next power of 2 greater than ``v``.
 */
inline std::int32_t round_up_pow2(std::int32_t v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  return v + 1;
}
/**
 * @brief Rounds to the next power of 2
 * @ingroup global-functions
 *
 * @param v Value to round
 *
 * @return The next power of 2 greater than ``v``.
 */
inline std::int64_t round_up_pow2(std::int64_t v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v |= v >> 32;
  return v + 1;
}
/**
 * @brief Counts the number of trailing zeros.
 * @ingroup global-functions
 *
 * This function counts the number of trailing zeros in the binary
 * representation of a value.
 *
 * @param v Value to count the zeros of.
 *
 * @return The number of trailing zeros in the binary representation of ``v``.
 */
inline int count_trailing_zeros(std::uint32_t v) {
#if SPECULA_COMPILER_IS_MSVC == 1
  unsigned long index;
  if (_BitScanForward(&index, v))
    return index;
  else
    return 32;
#else
  return __builtin_ctz(v);
#endif
}

/**
 * @brief Finds the first element that ``pred`` evaluates to true.
 * @ingroup global-functions
 *
 * Executes a bisection search for the first value for which ``pred`` evaluates
 * to true for. This is simmilar to ``std::upper_bound()`` but removes the
 * necessity for access to an array. By using a function ``Predicate`` it is
 * possible to preform the search on procedurally generated arrays.
 *
 * @tparam Predicate Function that takes an index and evaluates to a boolean.
 * @param size Total length of the interval to search.
 * @param pred Function that is used to evaluate the search.
 *
 * @return The index for the first value where ``pred`` evaluates to ``true``.
 *
 * @todo Could ``Predicate`` be changed to ``std::function<bool(int)>`` or
 * something of that form, to imporve readablity.
 */
template <typename Predicate>
int find_interval(int size, const Predicate &pred) {
  int first = 0, len = size;
  while (len > 0) {
    int half = len >> 1, middle = first + half;
    if (pred(middle)) {
      first = middle + 1;
      len -= half + 1;
    } else {
      len = half;
    }
  }
  return clamp(first - 1, 0, size - 2);
}

/**
 * @brief General linear interpolation.
 * @ingroup global-functions
 *
 * This function provides a general linear interpolation. It simply evaluates as
 * \f[
 * (1-t)a+tb,
 * \f]
 * where \f(t\in[0,1]\f).
 *
 * @tparam T Value type to interpolate between
 * @param t Floating point defining the position on the interpolation between
 * ``v1`` and ``v2``, this should be in the interval \f([0,1]\f).
 * @param v1 Begining value to interpolate between.
 * @param v2 Ending value to interpolate between.
 *
 * @return Linear interpolation between ``v1`` and ``v2`` controled by ``t``.
 */
template <typename T> inline T lerp(Float t, const T &v1, const T &v2) {
  return (1 - t) * v1 + t * v2;
}

template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type
isnan(const T &v) {
  return std::isnan(v);
}
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type
isnan(const T &) {
  return false;
}
/**
 * @brief Finds solution of quadratic equations.
 * @ingroup global-functions
 *
 * Solves the quadratic equation with the form:
 * \f[
 * at^2+bt+c=0.
 * \f]
 *
 * This implementation allways uses double-precision floating-point values
 * to reduce floating-point error.
 *
 * @param a First coefficient of quadratic equation.
 * @param b Second coefficient of quadratic equation.
 * @param c Third coefficient of quadratic equation.
 * @param t0 First solution of the equation, if there are any.
 * @param t1 Second solution of the equation, if it exists.
 *
 * @return ``true`` if solutions were found, ``false`` otherwise.
 *
 * @todo Possibly convert this to return some structure, instead of having
 * return values as parameters. Although this may effect preformance. This
 * should be tested more.
 */
inline bool quadratic(Float a, Float b, Float c, Float *t0, Float *t1) {
  double discrim = static_cast<double>(b) * static_cast<double>(b) -
                   4 * static_cast<double>(a) * static_cast<double>(c);
  if (discrim < 0)
    return false;
  double root_discrim = std::sqrt(discrim);

  double q;
  if (b < 0)
    q = -0.5 * (b - root_discrim);
  else
    q = -0.5 * (b + root_discrim);
  *t0 = q / a;
  *t1 = c / q;
  if (*t0 > *t1)
    std::swap(*t0, *t1);
  return true;
}

/**
 * @todo Document this function.
 * @ingroup global-functions
 */
inline Float erf_inv(Float x) {
  Float w, p;
  x = clamp(x, -0.99999f, 0.99999f);
  w = -std::log((1 - x) * (1 + x));
  if (w < 5) {
    w = w - 2.5f;
    p = 2.81022636e-08f;
    p = 3.43273939e-07f + p * w;
    p = -3.5233877e-06f + p * w;
    p = -4.39150654e-06f + p * w;
    p = 0.00021858087f + p * w;
    p = -0.00125372503f + p * w;
    p = -0.00417768164f + p * w;
    p = 0.246640727f + p * w;
    p = 1.50140941f + p * w;
  } else {
    w = std::sqrt(w) - 3;
    p = -0.000200214257f;
    p = 0.000100950558f + p * w;
    p = 0.00134934322f + p * w;
    p = -0.00367342844f + p * w;
    p = 0.00573950773f + p * w;
    p = -0.0076224613f + p * w;
    p = 0.00943887047f + p * w;
    p = 1.00167406f + p * w;
    p = 2.83297682f + p * w;
  }
  return p * x;
}
/**
 * @todo Document this function.
 * @ingroup global-functions
 */
inline Float erf(Float x) {
  Float a1 = 0.254829592f;
  Float a2 = -0.284496736f;
  Float a3 = 1.421413741f;
  Float a4 = -1.453152027f;
  Float a5 = 1.061405429f;
  Float p = 0.3275911f;
  int sign = 1;
  if (x < 0)
    sign = -1;
  x = std::abs(x);
  Float t = 1 / (1 + p * x);
  Float y =
      1 - ((((a5 * t + a4) * t + a3) * t + a2) * t + a1) * t * std::exp(-x * x);
  return sign * y;
}
} // namespace specula

#endif /* end of include guard: SPECULA_GLOBAL_FUNCTIONS_HPP_ */
