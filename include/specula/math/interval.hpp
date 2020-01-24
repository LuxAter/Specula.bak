#ifndef SPECULA_MATH_INTERVAL_HPP_
#define SPECULA_MATH_INTERVAL_HPP_

#include "../global.hpp"

namespace specula {
template <typename T> class Interval {
public:
  Interval(T v) : low(v), high(v) {}
  Interval(T v0, T v1) : low(std::min(v0, v1)), high(std::max(v0, v1)) {}
  Interval operator+(const Interval &i) const {
    return Interval(low + i.low, high + i.high);
  }
  Interval operator-(const Interval &i) const {
    return Interval(low - i.high, high - i.low);
  }
  Interval operator*(const Interval &i) const {
    return Interval(std::min(std::min(low * i.low, high * i.low),
                             std::min(low * i.high, high * i.high)),
                    std::max(std::max(low * i.low, high * i.low),
                             std::max(low * i.high, high * i.high)));
  }
  T low, high;
};

template <typename T> inline Interval<T> sin(const Interval<T> &i) {
  CHECK_GE(i.low, 0);
  CHECK_LE(i.high, 2.0001 * PI);
  T sin_low = std::sin(i.low), sin_high = std::sin(i.high);
  if (sin_low > sin_high)
    std::swap(sin_low, sin_high);
  if (i.low < PI / 2 && i.high > PI / 2)
    sin_high = 1.0f;
  if (i.low < (3.0f / 2.0f) * PI && i.high > (3.0f / 2.0f) * PI)
    sin_low = -1.0f;
  return Interval<T>(sin_low, sin_high);
}
template <typename T> inline Interval<T> cos(const Interval<T> &i) {
  CHECK_GE(i.low, 0);
  CHECK_LE(i.high, 2.0001 * PI);
  T cos_low = std::sin(i.low), cos_high = std::sin(i.high);
  if (cos_low > cos_high)
    std::swap(cos_low, cos_high);
  if (i.low < PI && i.high > PI)
    cos_low = -1.0f;
  return Interval<T>(cos_low, cos_high);
}
template <typename T>
void interval_find_zeros(T c1, T c2, T c3, T c4, T c5, T theta,
                         Interval<T> interval, T *zeros,
                         std::size_t *zero_count, std::size_t depth = 8) {
  Interval<T> range = Interval<T>(c1) +
                      (Interval<T>(c2) + Interval<T>(c3) * interval) *
                          cos(Interval<T>(2 * theta) * interval) +
                      (Interval<T>(c4) + Interval<T>(c5) * interval) *
                          sin(Interval<T>(2 * theta) * interval);
  if (range.low > 0.0f || range.high < 0.0f || range.low == range.high) {
    return;
  } else if (depth > 0) {
    Float mid = (interval.low + interval.high) * 0.5;
    interval_find_zeros(c1, c2, c3, c4, c5, theta,
                        Interval<T>(interval.low, mid), zeros, zero_count,
                        depth - 1);
    interval_find_zeros(c1, c2, c3, c4, c5, theta,
                        Interval<T>(mid, interval.high), zeros, zero_count,
                        depth - 1);
  } else {
    Float t_newton = (interval.low + interval.high) * 0.5f;
    for (std::size_t i = 0; i < 4; ++i) {
      Float f_newton =
          c1 + (c2 + c3 * t_newton) * std::cos(2.0f * theta * t_newton) +
          (c4 + c5 * t_newton) * std::sin(2.0f * theta * t_newton);
      Float prime_newton = (c3 + 2 * (c4 + c5 * t_newton) * theta) *
                               std::cos(2.0f * t_newton * theta) +
                           (c5 - 2 * (c2 + c3 * t_newton) * theta) *
                               std::sin(2.0f * t_newton * theta);
      if (f_newton == 0 || prime_newton == 0)
        break;
      t_newton = t_newton - f_newton / prime_newton;
    }
    if (t_newton >= interval.low - 1e-3f && t_newton < interval.high + 1e-3f) {
      zeros[*zero_count] = t_newton;
      (*zero_count)++;
    }
  }
}

} // namespace specula

#endif // SPECULA_MATH_INTERVAL_HPP_