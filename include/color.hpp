#ifndef SPECULA_COLOR_HPP_
#define SPECULA_COLOR_HPP_

namespace specula {
  struct Color {
    double r, g, b;
  };

  Color Mix(const Color& lhs,const double& mlhs, const Color& rhs, double mrhs=-1.0);
  Color operator+(const Color& lhs, const Color& rhs);
  Color operator-(const Color& lhs, const Color& rhs);
  Color operator*(const Color& lhs, const Color& rhs);
  Color operator/(const Color& lhs, const Color& rhs);
  Color operator+(const Color& lhs, const double& rhs);
  Color operator-(const Color& lhs, const double& rhs);
  Color operator*(const Color& lhs, const double& rhs);
  Color operator/(const Color& lhs, const double& rhs);
} // namespace specula

#endif  // SPECULA_COLOR_HPP_
