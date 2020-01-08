#ifndef SPECULA_MATH_GEOMETRIC_HPP_
#define SPECULA_MATH_GEOMETRIC_HPP_

#include "vector2.hpp"
#include "vector3.hpp"

namespace specula {
template <typename T>
inline Vector2<T> dot(const Vector2<T> &v1, const Vector2<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}
template <typename T> inline Vector2<T> normalize(const Vector2<T> &v) {
  return v / v.length();
}
template <typename T>
Vector2<T> permute(const Vector2<T> &v, typename Vector2<T>::size_type x,
                   typename Vector2<T>::size_type y) {
  return Vector2<T>(v[x], v[y]);
}

template <typename T>
inline Vector3<T> dot(const Vector3<T> &v1, const Vector3<T> &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
template <typename T>
inline Vector3<T> cross(const Vector3<T> &v1, const Vector3<T> &v2) {
  double v1x = v1.x, v1y = v1.y, v1z = v1.z;
  double v2x = v2.x, v2y = v2.y, v2z = v2.z;
  return Vector3<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}
template <typename T> inline Vector3<T> normalize(const Vector3<T> &v) {
  return v / v.length();
}
template <typename T>
inline std::array<Vector3<T>, 3> coordinate_system(const Vector3<T> &v1) {
  Vector3<T> v2, v3;
  if (std::abs(v1.x) > std::abs(v1.y))
    v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
  else
    v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
  v3 = Cross(v1, v2);
  return std::array<Vector3<T>, 3>{v1, v2, v3};
}
template <typename T>
inline void coordinate_system(const Vector3<T> &v1, Vector3<T> &v2,
                              Vector3<T> &v3) {
  if (std::abs(v1.x) > std::abs(v1.y))
    v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
  else
    v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
  v3 = Cross(v1, v2);
}
template <typename T>
inline void coordinate_system(const Vector3<T> &v1, Vector3<T> *v2,
                              Vector3<T> *v3) {
  if (std::abs(v1.x) > std::abs(v1.y))
    *v2 = Vector3<T>(-v1.z, 0, v1.x) / std::sqrt(v1.x * v1.x + v1.z * v1.z);
  else
    *v2 = Vector3<T>(0, v1.z, -v1.y) / std::sqrt(v1.y * v1.y + v1.z * v1.z);
  *v3 = Cross(v1, *v2);
}
template <typename T>
Vector3<T> permute(const Vector3<T> &v, typename Vector3<T>::size_type x,
                   typename Vector3<T>::size_type y,
                   typename Vector3<T>::size_type z) {
  return Vector3<T>(v[x], v[y], v[z]);
}
} // namespace specula

#endif // SPECULA_MATH_GEOMETRIC_HPP_
