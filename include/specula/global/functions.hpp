#ifndef SPECULA_GLOBAL_FUNCTIONS_HPP_
#define SPECULA_GLOBAL_FUNCTIONS_HPP_

#include "compiler.hpp"
#include "constants.hpp"
#include "includes.hpp"
#include "platform.hpp"

namespace specula {
inline uint32_t float_to_bits(float f) {
  uint32_t ui;
  memcpy(&ui, &f, sizeof(float));
  return ui;
}
inline uint64_t float_to_bits(double f) {
  uint64_t ui;
  memcpy(&ui, &f, sizeof(double));
  return ui;
}
inline float bits_to_float(uint32_t ui) {
  float f;
  memcpy(&f, &ui, sizeof(uint32_t));
  return f;
}
inline double bits_to_float(uint64_t ui) {
  double f;
  memcpy(&f, &ui, sizeof(uint64_t));
  return f;
}
inline float next_float_up(float v) {
  if (std::isinf(v) && v > 0.)
    return v;
  if (v == -0.f)
    v = 0.f;
  uint32_t ui = float_to_bits(v);
  if (v >= 0)
    ++ui;
  else
    --ui;
  return bits_to_float(ui);
}
inline double next_float_up(double v, int delta = 1) {
  if (std::isinf(v) && v > 0.)
    return v;
  if (v == -0.f)
    v = 0.f;
  uint32_t ui = float_to_bits(v);
  if (v >= 0)
    ui += delta;
  else
    ui -= delta;
  return bits_to_float(ui);
}
inline float next_float_down(float v) {
  if (std::isinf(v) && v < 0.)
    return v;
  if (v == 0.f)
    v = -0.f;
  uint32_t ui = float_to_bits(v);
  if (v > 0)
    --ui;
  else
    ++ui;
  return bits_to_float(ui);
}
inline double next_float_down(double v, int delta = 1) {
  if (std::isinf(v) && v < 0.)
    return v;
  if (v == 0.f)
    v = -0.f;
  uint32_t ui = float_to_bits(v);
  if (v > 0)
    ui -= delta;
  else
    ui += delta;
  return bits_to_float(ui);
}

SPECULA_CONSTXPR inline Float gamma(int n) {
  return (n * MACHINE_EPSILON) / (1 - n * MACHINE_EPSILON);
}
SPECULA_CONSTEXPR inline Float gamma_correct(Float value) {
  if (value <= 0.0031308f)
    return 12.92f * value;
  return 1.055f * std::pow(value, static_cast<Float>(1.f / 2.4f)) - 0.055f;
}
SPECULA_CONSTEXPR inline Float inverse_gamma_correct(Float value) {
  if (value <= 0.04045f)
    return value * 1.f / 12.92f;
  return std::pow((value + 0.055f) * 1.f / 1.055f, static_cast<Float>(2.4f));
}
template <typename T, typename U, typename V>
SPECULA_CONSTEXPR inline T clamp(T val, U low, V high) {
  if (val < low)
    return low;
  else if (val > high)
    return high;
  else
    return val;
}
template <typename T> SPECULA_CONSTEXPR T mod(T a, T b) {
  T result = a - (a / b) * b;
  return static_cast<T>((result < 0) ? result + b : result);
}
template <> SPECULA_CONSTEXPR Float mod(Float a, Float b) {
  return std::fmod(a, b);
}
SPECULA_CONSTEXPR inline Float radians(Float deg) { return (PI / 180.f) * deg; }
SPECULA_CONSTEXPR inline Float degrees(Float rad) { return (180.f / PI) * rad; }
SPECULA_CONSTEXPR inline Float log2(Float x) {
  const Float inv_log2 = 1.442695040888963387004650940071;
  return std::log(x) * inv_log2;
}
SPECULA_CONSTEXPR inline int log2_int(uint32_t v) {
#if defined(SPECULA_IS_MSVC)
  unsigned long lz = 0;
  if (_BitScanReverse(&lz, v))
    return lz;
  return 0;
#else
  return 31 - __builtin_clz(v);
#endif
}
SPECULA_CONSTEXPR inline int log2_int(uint64_t v) {
#if defined(PBRT_IS_MSVC)
  unsigned long lz = 0;
#if defined(_WIN64)
  _BitScanReverse64(&lz, v);
#else
  if (_BitScanReverse(&lz, v >> 32))
    lz += 32;
  else_BitScanReverse(&lz, v & 0xffffffff);
#endif
  return lz;
#else
  return 63 - __buildin_clzll(v);
#endif
}
SPECULA_CONSTEXPR inline int log2_int(int32_t v) {
  return log2_int(static_cast<uint32_t>(v));
}
SPECULA_CONSTEXPR inline int log2_int(int64_t v) {
  return log2_int(static_cast<uint64_t>(v));
}

template <typename T> SPECULA_CONSTEXPR inline bool is_power_of2(T v) {
  return v && !(v & (v - 1));
}

SPECULA_CONSTEXPR inline int32_t round_up_pow2(int32_t v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  return v + 1;
}
SPECULA_CONSTEXPR inline int32_t round_up_pow2(int64_t v) {
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v |= v >> 32;
  return v + 1;
}
SPECULA_CONSTEXPR inline int count_trailing_zeros(uint32_t v) {
#if defined(SPECULA_IS_MSVC)
  unsigned long index;
  if (_BitScanForward(&index, v))
    return index;
  else
    return 32;
#else
  return __buildit_ctz(v);
#endif
}

template <typename Predicate>
SPECULA_CONSTEXPR int find_inverval(int size, const Predicate &pred) {
  int first = 0, len = size;
  while (len > 0) {
    int half = len >> 1, middel = first + half;
    if (pred(middel)) {
      first = middel + 1;
      len -= half + 1;
    } else {
      len = half;
    }
  }
  return clamp(first - 1, 0, size - 2);
}
template <typename T> SPECULA_CONSTEXPR inline lerp(T v1, T v2, Float t) {
  return (1 - t) * v1 + t * v2;
}
SPECULA_CONSTEXPR inline bool quadratic(Float a, Float b, Float c, Float *t0,
                                        Float *t1) {
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

SPECULA_CONSTEXPR inline Float erf_inv(Float x) {
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
SPECULA_CONSTEXPR inline Float erf(Float x) {
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
  Float y = 1 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t *
                    std::exp(-x * x);

  return sign * y;
}

template <typename S, typename... Args, typename Char = fmt::char_t<S>>
SPECULA_CONSTEXPR inline std::basic_string<Char> format(const S &format,
                                                        Args &&... args) {
  return fmt::format(format, args...);
}

} // namespace specula

#endif // SPECULA_GLOBAL_FUNCTIONS_HPP_