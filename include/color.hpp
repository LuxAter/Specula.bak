#ifndef SPECULA_COLOR_HPP_
#define SPECULA_COLOR_HPP_

#include "math/common.hpp"

namespace specula {
class Color {
 public:
  Color() : r(0.0), g(0.0), b(0.0) {}
  explicit Color(double v) : r(v), g(v), b(v) {}
  Color(double red, double green, double blue) : r(red), g(green), b(blue) {}
  explicit Color(unsigned short v)
      : r(static_cast<double>(v) / 255.0),
        g(static_cast<double>(v) / 255.0),
        b(static_cast<double>(v) / 255.0) {}
  Color(unsigned short red, unsigned short green, unsigned short blue)
      : r(static_cast<double>(red) / 255.0),
        g(static_cast<double>(green) / 255.0),
        b(static_cast<double>(blue) / 255.0) {}
  explicit Color(unsigned rgb)
      : r(static_cast<double>((rgb >> 16) & 0xFF) / 255.0),
        g(static_cast<double>((rgb >> 8) & 0xFF) / 255.0),
        b(static_cast<double>(rgb & 0xFF) / 255.0) {}

  inline double dr() const noexcept { return r; }
  inline double dg() const noexcept { return g; }
  inline double db() const noexcept { return b; }
  inline unsigned short ir() const noexcept {
    return static_cast<unsigned short>(r * 255.0);
  }
  inline unsigned short ig() const noexcept {
    return static_cast<unsigned short>(g * 255.0);
  }
  inline unsigned short ib() const noexcept {
    return static_cast<unsigned short>(b * 255.0);
  }
  inline unsigned rgb() const noexcept {
    return (static_cast<unsigned>(r * 255.0) << 16) |
           (static_cast<unsigned>(g * 255.0) << 8) |
           (static_cast<unsigned>(b * 255.0));
  }

  template <typename _U>
  inline Color& operator+=(const _U& rhs) {
    *this = *this + rhs;
    return *this;
  }
  template <typename _U>
  inline Color& operator-=(const _U& rhs) {
    *this = *this - rhs;
    return *this;
  }
  template <typename _U>
  inline Color& operator*=(const _U& rhs) {
    *this = *this * rhs;
    return *this;
  }
  template <typename _U>
  inline Color& operator/=(const _U& rhs) {
    *this = *this / rhs;
    return *this;
  }

  double r, g, b;
};

inline Color operator+(const Color& lhs, const double& rhs) {
  return Color{math::clamp(lhs.r + rhs, 0.0, 1.0),
               math::clamp(lhs.g + rhs, 0.0, 1.0),
               math::clamp(lhs.b + rhs, 0.0, 1.0)};
}
inline Color operator+(const Color& lhs, const Color& rhs) {
  return Color{math::clamp(lhs.r + rhs.r, 0.0, 1.0),
               math::clamp(lhs.g + rhs.g, 0.0, 1.0),
               math::clamp(lhs.b + rhs.b, 0.0, 1.0)};
}
inline Color operator-(const Color& lhs, const double& rhs) {
  return Color{math::clamp(lhs.r - rhs, 0.0, 1.0),
               math::clamp(lhs.g - rhs, 0.0, 1.0),
               math::clamp(lhs.b - rhs, 0.0, 1.0)};
}
inline Color operator-(const Color& lhs, const Color& rhs) {
  return Color{math::clamp(lhs.r - rhs.r, 0.0, 1.0),
               math::clamp(lhs.g - rhs.g, 0.0, 1.0),
               math::clamp(lhs.b - rhs.b, 0.0, 1.0)};
}
inline Color operator*(const Color& lhs, const double& rhs) {
  return Color{math::clamp(lhs.r * rhs, 0.0, 1.0),
               math::clamp(lhs.g * rhs, 0.0, 1.0),
               math::clamp(lhs.b * rhs, 0.0, 1.0)};
}
inline Color operator*(const Color& lhs, const Color& rhs) {
  return Color{math::clamp(lhs.r * rhs.r, 0.0, 1.0),
               math::clamp(lhs.g * rhs.g, 0.0, 1.0),
               math::clamp(lhs.b * rhs.b, 0.0, 1.0)};
}
inline Color operator/(const Color& lhs, const double& rhs) {
  return Color{math::clamp(lhs.r / rhs, 0.0, 1.0),
               math::clamp(lhs.g / rhs, 0.0, 1.0),
               math::clamp(lhs.b / rhs, 0.0, 1.0)};
}
inline Color operator/(const Color& lhs, const Color& rhs) {
  return Color{math::clamp(lhs.r / rhs.r, 0.0, 1.0),
               math::clamp(lhs.g / rhs.g, 0.0, 1.0),
               math::clamp(lhs.b / rhs.b, 0.0, 1.0)};
}

}  // namespace specula

#endif  // SPECULA_COLOR_HPP_
