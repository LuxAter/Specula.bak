#include "color.hpp"

specula::Color specula::Mix(const Color& lhs,const double& mlhs, const Color& rhs, double mrhs){
  if(mrhs == -1){
    mrhs = 1.0 - mlhs;
  }
  return (lhs * mlhs) + (rhs * mrhs);
}


specula::Color specula::operator+(const Color& lhs, const Color& rhs) {
  return {(lhs.r + rhs.r), (lhs.g + rhs.g), (lhs.b + rhs.b)};
}
specula::Color specula::operator-(const Color& lhs, const Color& rhs) {
  return {(lhs.r - rhs.r), (lhs.g - rhs.g), (lhs.b - rhs.b)};
}
specula::Color specula::operator*(const Color& lhs, const Color& rhs) {
  return {(lhs.r * rhs.r), (lhs.g * rhs.g), (lhs.b * rhs.b)};
}
specula::Color specula::operator/(const Color& lhs, const Color& rhs) {
  return {(lhs.r / rhs.r), (lhs.g / rhs.g), (lhs.b / rhs.b)};
}
specula::Color specula::operator+(const Color& lhs, const double& rhs) {
  return {(lhs.r + rhs), (lhs.g + rhs), (lhs.b + rhs)};
}
specula::Color specula::operator-(const Color& lhs, const double& rhs) {
  return {(lhs.r - rhs), (lhs.g - rhs), (lhs.b - rhs)};
}
specula::Color specula::operator*(const Color& lhs, const double& rhs) {
  return {(lhs.r * rhs), (lhs.g * rhs), (lhs.b * rhs)};
}
specula::Color specula::operator/(const Color& lhs, const double& rhs) {
  return {(lhs.r / rhs), (lhs.g / rhs), (lhs.b / rhs)};
}
