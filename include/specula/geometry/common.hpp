#ifndef SPECULA_MATH_COMMON_HPP_
#define SPECULA_MATH_COMMON_HPP_

#include "vector2.hpp"
#include "vector3.hpp"

namespace specula {
template <typename T> inline SPECULA_CONSTEXPR T abs(const T &v) {
  return std::abs(v);
}
template <typename T> inline SPECULA_CONSTEXPR T ceil(const T &v) {
  return std::ceil(v);
}
template <typename T>
inline SPECULA_CONSTEXPR T clamp(const T &v, const T &min_val,
                                 const T &max_val) {
  return std::min(std::max(v, min_val), max_val);
}
template <typename T> inline SPECULA_CONSTEXPR T floor(const T &v) {
  return std::floor(v);
}
template <typename T> inline SPECULA_CONSTEXPR bool isinf(const T &v) {
  return std::isinf(v);
}
template <typename T> inline SPECULA_CONSTEXPR bool isnan(const T &v) {
  return std::isnan(v);
}
template <typename T> inline SPECULA_CONSTEXPR T max(const T &x, const T &y) {
  return std::max(x, y);
}
template <typename T> inline SPECULA_CONSTEXPR T min(const T &x, const T &y) {
  return std::min(x, y);
}
template <typename T, typename U>
inline SPECULA_CONSTEXPR T mix(const T &x, const T &y, const U &a) {
  return x * (1.0 - a) + y * a;
}
template <typename T, typename U>
inline SPECULA_CONSTEXPR T lerp(const T &x, const T &y, const U &a) {
  return x * (1.0 - a) + y * a;
}

template <typename T>
inline SPECULA_CONSTEXPR Vector2<T> abs(const Vector2<T> &v) {
  return Vector2<T>(std::abs(v.x), std::abs(v.y));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector2<T> ceil(const Vector2<T> &v) {
  return Vector2<T>(std::ceil(v.x), std::ceil(v.y));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector2<T> clamp(const Vector2<T> &v, const T &min_val,
                                          const T &max_val) {
  return Vector2<T>(clamp(v.x, min_val, max_val), clamp(v.y, min_val, max_val));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector2<T> floor(const Vector2<T> &v) {
  return Vector2<T>(std::floor(v.x), std::floor(v.y));
}
template <typename T>
inline SPECULA_CONSTEXPR bool hasinf(const Vector2<T> &v) {
  return std::isinf(v.x) || std::isinf(v.y);
}
template <typename T>
inline SPECULA_CONSTEXPR bool hasnan(const Vector2<T> &v) {
  return std::isnan(v.x) || std::isnan(v.y);
}
template <typename T>
inline SPECULA_CONSTEXPR Vector2<T> max(const Vector2<T> &v, T y) {
  return Vector2<T>(std::max(v.x, y), std::max(v.y, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector2<T> max(const Vector2<T> &v1,
                                        const Vector2<T> &v2) {
  return Vector2<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector2<T> min(const Vector2<T> &v, T y) {
  return Vector2<T>(std::min(v.x, y), std::min(v.y, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector2<T> min(const Vector2<T> &v1,
                                        const Vector2<T> &v2) {
  return Vector2<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
}
template <typename T> inline T min_component(const Vector2<T> &v) {
  return std::min(v.x, v.y);
}
template <typename T> inline T max_component(const Vector2<T> &v) {
  return std::max(v.x, v.y);
}
template <typename T>
inline typename Vector2<T>::size_type min_dimension(const Vector2<T> &v) {
  return (v.x < v.y) ? 0 : 1;
}
template <typename T>
inline typename Vector2<T>::size_type max_dimension(const Vector2<T> &v) {
  return (v.x > v.y) ? 0 : 1;
}

template <typename T>
inline SPECULA_CONSTEXPR Vector3<T> abs(const Vector3<T> &v) {
  return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector3<T> ceil(const Vector3<T> &v) {
  return Vector3<T>(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector3<T> clamp(const Vector3<T> &v, const T &min_val,
                                          const T &max_val) {
  return Vector3<T>(clamp(v.x, min_val, max_val), clamp(v.y, min_val, max_val),
                    clamp(v.z, min_val, max_val));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector3<T> floor(const Vector3<T> &v) {
  return Vector3<T>(std::floor(v.x), std::floor(v.y), std::floor(v.z));
}
template <typename T>
inline SPECULA_CONSTEXPR bool hasinf(const Vector3<T> &v) {
  return std::isinf(v.x) || std::isinf(v.y) || std::isinf(v.z);
}
template <typename T>
inline SPECULA_CONSTEXPR bool hasnan(const Vector3<T> &v) {
  return std::isnan(v.x) || std::isnan(v.y) || std::isnan(v.z);
}
template <typename T>
inline SPECULA_CONSTEXPR Vector3<T> max(const Vector3<T> &v, T y) {
  return Vector3<T>(std::max(v.x, y), std::max(v.y, y), std::max(v.z, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector3<T> max(const Vector3<T> &v1,
                                        const Vector3<T> &v2) {
  return Vector3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y),
                    std::max(v1.z, v2.z));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector3<T> min(const Vector3<T> &v, T y) {
  return Vector3<T>(std::min(v.x, y), std::min(v.y, y), std::min(v.z, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Vector3<T> min(const Vector3<T> &v1,
                                        const Vector3<T> &v2) {
  return Vector3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y),
                    std::min(v1.z, v2.z));
}
template <typename T> inline T min_component(const Vector3<T> &v) {
  return std::min(v.x, std::min(v.y, v.z));
}
template <typename T> inline T max_component(const Vector3<T> &v) {
  return std::max(v.x, std::max(v.y, v.z));
}
template <typename T>
inline typename Vector3<T>::size_type min_dimension(const Vector3<T> &v) {
  return (v.x < v.y) ? ((v.x < v.z) ? 0 : 2) : ((v.y < v.z) ? 1 : 2);
}
template <typename T>
inline typename Vector3<T>::size_type max_dimension(const Vector3<T> &v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

template <typename T>
inline SPECULA_CONSTEXPR Point2<T> abs(const Point2<T> &v) {
  return Point2<T>(std::abs(v.x), std::abs(v.y));
}
template <typename T>
inline SPECULA_CONSTEXPR Point2<T> ceil(const Point2<T> &v) {
  return Point2<T>(std::ceil(v.x), std::ceil(v.y));
}
template <typename T>
inline SPECULA_CONSTEXPR Point2<T> clamp(const Point2<T> &v, const T &min_val,
                                         const T &max_val) {
  return Point2<T>(clamp(v.x, min_val, max_val), clamp(v.y, min_val, max_val));
}
template <typename T>
inline SPECULA_CONSTEXPR Point2<T> floor(const Point2<T> &v) {
  return Point2<T>(std::floor(v.x), std::floor(v.y));
}
template <typename T> inline SPECULA_CONSTEXPR bool hasinf(const Point2<T> &v) {
  return std::isinf(v.x) || std::isinf(v.y);
}
template <typename T> inline SPECULA_CONSTEXPR bool hasnan(const Point2<T> &v) {
  return std::isnan(v.x) || std::isnan(v.y);
}
template <typename T>
inline SPECULA_CONSTEXPR Point2<T> max(const Point2<T> &v, T y) {
  return Point2<T>(std::max(v.x, y), std::max(v.y, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Point2<T> max(const Point2<T> &v1,
                                       const Point2<T> &v2) {
  return Point2<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
}
template <typename T>
inline SPECULA_CONSTEXPR Point2<T> min(const Point2<T> &v, T y) {
  return Point2<T>(std::min(v.x, y), std::min(v.y, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Point2<T> min(const Point2<T> &v1,
                                       const Point2<T> &v2) {
  return Point2<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
}
template <typename T> inline T min_component(const Point2<T> &v) {
  return std::min(v.x, v.y);
}
template <typename T> inline T max_component(const Point2<T> &v) {
  return std::max(v.x, v.y);
}
template <typename T>
inline typename Point2<T>::size_type min_dimension(const Point2<T> &v) {
  return (v.x < v.y) ? 0 : 1;
}
template <typename T>
inline typename Point2<T>::size_type max_dimension(const Point2<T> &v) {
  return (v.x > v.y) ? 0 : 1;
}

template <typename T>
inline SPECULA_CONSTEXPR Point3<T> abs(const Point3<T> &v) {
  return Point3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}
template <typename T>
inline SPECULA_CONSTEXPR Point3<T> ceil(const Point3<T> &v) {
  return Point3<T>(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z));
}
template <typename T>
inline SPECULA_CONSTEXPR Point3<T> clamp(const Point3<T> &v, const T &min_val,
                                         const T &max_val) {
  return Point3<T>(clamp(v.x, min_val, max_val), clamp(v.y, min_val, max_val),
                   clamp(v.z, min_val, max_val));
}
template <typename T>
inline SPECULA_CONSTEXPR Point3<T> floor(const Point3<T> &v) {
  return Point3<T>(std::floor(v.x), std::floor(v.y), std::floor(v.z));
}
template <typename T> inline SPECULA_CONSTEXPR bool hasinf(const Point3<T> &v) {
  return std::isinf(v.x) || std::isinf(v.y) || std::isinf(v.z);
}
template <typename T> inline SPECULA_CONSTEXPR bool hasnan(const Point3<T> &v) {
  return std::isnan(v.x) || std::isnan(v.y) || std::isnan(v.z);
}
template <typename T>
inline SPECULA_CONSTEXPR Point3<T> max(const Point3<T> &v, T y) {
  return Point3<T>(std::max(v.x, y), std::max(v.y, y), std::max(v.z, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Point3<T> max(const Point3<T> &v1,
                                       const Point3<T> &v2) {
  return Point3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y),
                   std::max(v1.z, v2.z));
}
template <typename T>
inline SPECULA_CONSTEXPR Point3<T> min(const Point3<T> &v, T y) {
  return Point3<T>(std::min(v.x, y), std::min(v.y, y), std::min(v.z, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Point3<T> min(const Point3<T> &v1,
                                       const Point3<T> &v2) {
  return Point3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y),
                   std::min(v1.z, v2.z));
}
template <typename T> inline T min_component(const Point3<T> &v) {
  return std::min(v.x, std::min(v.y, v.z));
}
template <typename T> inline T max_component(const Point3<T> &v) {
  return std::max(v.x, std::max(v.y, v.z));
}
template <typename T>
inline typename Point3<T>::size_type min_dimension(const Point3<T> &v) {
  return (v.x < v.y) ? ((v.x < v.z) ? 0 : 2) : ((v.y < v.z) ? 1 : 2);
}
template <typename T>
inline typename Point3<T>::size_type max_dimension(const Point3<T> &v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

template <typename T>
inline SPECULA_CONSTEXPR Normal3<T> abs(const Normal3<T> &v) {
  return Normal3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}
template <typename T>
inline SPECULA_CONSTEXPR Normal3<T> ceil(const Normal3<T> &v) {
  return Normal3<T>(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z));
}
template <typename T>
inline SPECULA_CONSTEXPR Normal3<T> clamp(const Normal3<T> &v, const T &min_val,
                                          const T &max_val) {
  return Normal3<T>(clamp(v.x, min_val, max_val), clamp(v.y, min_val, max_val),
                    clamp(v.z, min_val, max_val));
}
template <typename T>
inline SPECULA_CONSTEXPR Normal3<T> floor(const Normal3<T> &v) {
  return Normal3<T>(std::floor(v.x), std::floor(v.y), std::floor(v.z));
}
template <typename T>
inline SPECULA_CONSTEXPR bool hasinf(const Normal3<T> &v) {
  return std::isinf(v.x) || std::isinf(v.y) || std::isinf(v.z);
}
template <typename T>
inline SPECULA_CONSTEXPR bool hasnan(const Normal3<T> &v) {
  return std::isnan(v.x) || std::isnan(v.y) || std::isnan(v.z);
}
template <typename T>
inline SPECULA_CONSTEXPR Normal3<T> max(const Normal3<T> &v, T y) {
  return Normal3<T>(std::max(v.x, y), std::max(v.y, y), std::max(v.z, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Normal3<T> max(const Normal3<T> &v1,
                                        const Normal3<T> &v2) {
  return Normal3<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y),
                    std::max(v1.z, v2.z));
}
template <typename T>
inline SPECULA_CONSTEXPR Normal3<T> min(const Normal3<T> &v, T y) {
  return Normal3<T>(std::min(v.x, y), std::min(v.y, y), std::min(v.z, y));
}
template <typename T>
inline SPECULA_CONSTEXPR Normal3<T> min(const Normal3<T> &v1,
                                        const Normal3<T> &v2) {
  return Normal3<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y),
                    std::min(v1.z, v2.z));
}
template <typename T> inline T min_component(const Normal3<T> &v) {
  return std::min(v.x, std::min(v.y, v.z));
}
template <typename T> inline T max_component(const Normal3<T> &v) {
  return std::max(v.x, std::max(v.y, v.z));
}
template <typename T>
inline typename Normal3<T>::size_type min_dimension(const Normal3<T> &v) {
  return (v.x < v.y) ? ((v.x < v.z) ? 0 : 2) : ((v.y < v.z) ? 1 : 2);
}
template <typename T>
inline typename Normal3<T>::size_type max_dimension(const Normal3<T> &v) {
  return (v.x > v.y) ? ((v.x > v.z) ? 0 : 2) : ((v.y > v.z) ? 1 : 2);
}

} // namespace specula

#endif // SPECULA_MATH_COMMON_HPP_
