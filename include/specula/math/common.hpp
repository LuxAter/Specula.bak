#ifndef SPECULA_MATH_COMMON_HPP_
#define SPECULA_MATH_COMMON_HPP_

#include "../global.hpp"

#include "bounds.hpp"
#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace specula {
template <typename T> inline T abs(const T &s) { return std::abs(s); }
template <typename T> inline Vector2<T> abs(const Vector2<T> &v) {
  return Vector2<T>(abs(v.x), abs(v.y));
}
template <typename T> inline Vector3<T> abs(const Vector3<T> &v) {
  return Vector3<T>(abs(v.x), abs(v.y), abs(v.z));
}
template <typename T> inline Vector4<T> abs(const Vector4<T> &v) {
  return Vector4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}
template <typename T> inline Point2<T> abs(const Point2<T> &v) {
  return Point2<T>(abs(v.x), abs(v.y));
}
template <typename T> inline Point3<T> abs(const Point3<T> &v) {
  return Point3<T>(abs(v.x), abs(v.y), abs(v.z));
}
template <typename T> inline Point4<T> abs(const Point4<T> &v) {
  return Point4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}
template <typename T> inline Normal2<T> abs(const Normal2<T> &v) {
  return Normal2<T>(abs(v.x), abs(v.y));
}
template <typename T> inline Normal3<T> abs(const Normal3<T> &v) {
  return Normal3<T>(abs(v.x), abs(v.y), abs(v.z));
}
template <typename T> inline Normal4<T> abs(const Normal4<T> &v) {
  return Normal4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}
template <typename T> inline Matrix2x2<T> abs(const Matrix2x2<T> &m) {
  return Matrix2x2<T>(abs(m[0][0]), abs(m[0][1]), abs(m[1][0]), abs(m[1][1]));
}
template <typename T> inline Matrix3x3<T> abs(const Matrix3x3<T> &m) {
  return Matrix3x3<T>(abs(m[0][0]), abs(m[0][1]), abs(m[0][2]), abs(m[1][0]),
                      abs(m[1][1]), abs(m[1][2]), abs(m[2][0]), abs(m[2][1]),
                      abs(m[2][2]));
}
template <typename T> inline Matrix4x4<T> abs(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(abs(m[0][0]), abs(m[0][1]), abs(m[0][2]), abs(m[0][3]),
                      abs(m[1][0]), abs(m[1][1]), abs(m[1][2]), abs(m[1][3]),
                      abs(m[2][0]), abs(m[2][1]), abs(m[2][2]), abs(m[2][3]),
                      abs(m[3][0]), abs(m[3][1]), abs(m[3][2]), abs(m[3][3]));
}

template <typename T> inline T ceil(const T &s) { return std::ceil(s); }
template <typename T> inline Vector2<T> ceil(const Vector2<T> &v) {
  return Vector2<T>(ceil(v.x), ceil(v.y));
}
template <typename T> inline Vector3<T> ceil(const Vector3<T> &v) {
  return Vector3<T>(ceil(v.x), ceil(v.y), ceil(v.z));
}
template <typename T> inline Vector4<T> ceil(const Vector4<T> &v) {
  return Vector4<T>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
}
template <typename T> inline Point2<T> ceil(const Point2<T> &v) {
  return Point2<T>(ceil(v.x), ceil(v.y));
}
template <typename T> inline Point3<T> ceil(const Point3<T> &v) {
  return Point3<T>(ceil(v.x), ceil(v.y), ceil(v.z));
}
template <typename T> inline Point4<T> ceil(const Point4<T> &v) {
  return Point4<T>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
}
template <typename T> inline Normal2<T> ceil(const Normal2<T> &v) {
  return Normal2<T>(ceil(v.x), ceil(v.y));
}
template <typename T> inline Normal3<T> ceil(const Normal3<T> &v) {
  return Normal3<T>(ceil(v.x), ceil(v.y), ceil(v.z));
}
template <typename T> inline Normal4<T> ceil(const Normal4<T> &v) {
  return Normal4<T>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
}
template <typename T> inline Matrix2x2<T> ceil(const Matrix2x2<T> &m) {
  return Matrix2x2<T>(ceil(m[0][0]), ceil(m[0][1]), ceil(m[1][0]),
                      ceil(m[1][1]));
}
template <typename T> inline Matrix3x3<T> ceil(const Matrix3x3<T> &m) {
  return Matrix3x3<T>(ceil(m[0][0]), ceil(m[0][1]), ceil(m[0][2]),
                      ceil(m[1][0]), ceil(m[1][1]), ceil(m[1][2]),
                      ceil(m[2][0]), ceil(m[2][1]), ceil(m[2][2]));
}
template <typename T> inline Matrix4x4<T> ceil(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(
      ceil(m[0][0]), ceil(m[0][1]), ceil(m[0][2]), ceil(m[0][3]), ceil(m[1][0]),
      ceil(m[1][1]), ceil(m[1][2]), ceil(m[1][3]), ceil(m[2][0]), ceil(m[2][1]),
      ceil(m[2][2]), ceil(m[2][3]), ceil(m[3][0]), ceil(m[3][1]), ceil(m[3][2]),
      ceil(m[3][3]));
}

template <typename T> inline T floor(const T &s) { return std::floor(s); }
template <typename T> inline Vector2<T> floor(const Vector2<T> &v) {
  return Vector2<T>(floor(v.x), floor(v.y));
}
template <typename T> inline Vector3<T> floor(const Vector3<T> &v) {
  return Vector3<T>(floor(v.x), floor(v.y), floor(v.z));
}
template <typename T> inline Vector4<T> floor(const Vector4<T> &v) {
  return Vector4<T>(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
}
template <typename T> inline Point2<T> floor(const Point2<T> &v) {
  return Point2<T>(floor(v.x), floor(v.y));
}
template <typename T> inline Point3<T> floor(const Point3<T> &v) {
  return Point3<T>(floor(v.x), floor(v.y), floor(v.z));
}
template <typename T> inline Point4<T> floor(const Point4<T> &v) {
  return Point4<T>(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
}
template <typename T> inline Normal2<T> floor(const Normal2<T> &v) {
  return Normal2<T>(floor(v.x), floor(v.y));
}
template <typename T> inline Normal3<T> floor(const Normal3<T> &v) {
  return Normal3<T>(floor(v.x), floor(v.y), floor(v.z));
}
template <typename T> inline Normal4<T> floor(const Normal4<T> &v) {
  return Normal4<T>(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
}
template <typename T> inline Matrix2x2<T> floor(const Matrix2x2<T> &m) {
  return Matrix2x2<T>(floor(m[0][0]), floor(m[0][1]), floor(m[1][0]),
                      floor(m[1][1]));
}
template <typename T> inline Matrix3x3<T> floor(const Matrix3x3<T> &m) {
  return Matrix3x3<T>(floor(m[0][0]), floor(m[0][1]), floor(m[0][2]),
                      floor(m[1][0]), floor(m[1][1]), floor(m[1][2]),
                      floor(m[2][0]), floor(m[2][1]), floor(m[2][2]));
}
template <typename T> inline Matrix4x4<T> floor(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(
      floor(m[0][0]), floor(m[0][1]), floor(m[0][2]), floor(m[0][3]),
      floor(m[1][0]), floor(m[1][1]), floor(m[1][2]), floor(m[1][3]),
      floor(m[2][0]), floor(m[2][1]), floor(m[2][2]), floor(m[2][3]),
      floor(m[3][0]), floor(m[3][1]), floor(m[3][2]), floor(m[3][3]));
}

template <typename T> inline T isinf(const T &s) { return std::isinf(s); }
template <typename T> inline Vector2<T> isinf(const Vector2<T> &v) {
  return Vector2<T>(isinf(v.x), isinf(v.y));
}
template <typename T> inline Vector3<T> isinf(const Vector3<T> &v) {
  return Vector3<T>(isinf(v.x), isinf(v.y), isinf(v.z));
}
template <typename T> inline Vector4<T> isinf(const Vector4<T> &v) {
  return Vector4<T>(isinf(v.x), isinf(v.y), isinf(v.z), isinf(v.w));
}
template <typename T> inline Point2<T> isinf(const Point2<T> &v) {
  return Point2<T>(isinf(v.x), isinf(v.y));
}
template <typename T> inline Point3<T> isinf(const Point3<T> &v) {
  return Point3<T>(isinf(v.x), isinf(v.y), isinf(v.z));
}
template <typename T> inline Point4<T> isinf(const Point4<T> &v) {
  return Point4<T>(isinf(v.x), isinf(v.y), isinf(v.z), isinf(v.w));
}
template <typename T> inline Normal2<T> isinf(const Normal2<T> &v) {
  return Normal2<T>(isinf(v.x), isinf(v.y));
}
template <typename T> inline Normal3<T> isinf(const Normal3<T> &v) {
  return Normal3<T>(isinf(v.x), isinf(v.y), isinf(v.z));
}
template <typename T> inline Normal4<T> isinf(const Normal4<T> &v) {
  return Normal4<T>(isinf(v.x), isinf(v.y), isinf(v.z), isinf(v.w));
}
template <typename T> inline Matrix2x2<T> isinf(const Matrix2x2<T> &m) {
  return Matrix2x2<T>(isinf(m[0][0]), isinf(m[0][1]), isinf(m[1][0]),
                      isinf(m[1][1]));
}
template <typename T> inline Matrix3x3<T> isinf(const Matrix3x3<T> &m) {
  return Matrix3x3<T>(isinf(m[0][0]), isinf(m[0][1]), isinf(m[0][2]),
                      isinf(m[1][0]), isinf(m[1][1]), isinf(m[1][2]),
                      isinf(m[2][0]), isinf(m[2][1]), isinf(m[2][2]));
}
template <typename T> inline Matrix4x4<T> isinf(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(
      isinf(m[0][0]), isinf(m[0][1]), isinf(m[0][2]), isinf(m[0][3]),
      isinf(m[1][0]), isinf(m[1][1]), isinf(m[1][2]), isinf(m[1][3]),
      isinf(m[2][0]), isinf(m[2][1]), isinf(m[2][2]), isinf(m[2][3]),
      isinf(m[3][0]), isinf(m[3][1]), isinf(m[3][2]), isinf(m[3][3]));
}

template <typename T> inline T isnan(const T &s) { return std::isnan(s); }
template <typename T> inline Vector2<T> isnan(const Vector2<T> &v) {
  return Vector2<T>(isnan(v.x), isnan(v.y));
}
template <typename T> inline Vector3<T> isnan(const Vector3<T> &v) {
  return Vector3<T>(isnan(v.x), isnan(v.y), isnan(v.z));
}
template <typename T> inline Vector4<T> isnan(const Vector4<T> &v) {
  return Vector4<T>(isnan(v.x), isnan(v.y), isnan(v.z), isnan(v.w));
}
template <typename T> inline Point2<T> isnan(const Point2<T> &v) {
  return Point2<T>(isnan(v.x), isnan(v.y));
}
template <typename T> inline Point3<T> isnan(const Point3<T> &v) {
  return Point3<T>(isnan(v.x), isnan(v.y), isnan(v.z));
}
template <typename T> inline Point4<T> isnan(const Point4<T> &v) {
  return Point4<T>(isnan(v.x), isnan(v.y), isnan(v.z), isnan(v.w));
}
template <typename T> inline Normal2<T> isnan(const Normal2<T> &v) {
  return Normal2<T>(isnan(v.x), isnan(v.y));
}
template <typename T> inline Normal3<T> isnan(const Normal3<T> &v) {
  return Normal3<T>(isnan(v.x), isnan(v.y), isnan(v.z));
}
template <typename T> inline Normal4<T> isnan(const Normal4<T> &v) {
  return Normal4<T>(isnan(v.x), isnan(v.y), isnan(v.z), isnan(v.w));
}
template <typename T> inline Matrix2x2<T> isnan(const Matrix2x2<T> &m) {
  return Matrix2x2<T>(isnan(m[0][0]), isnan(m[0][1]), isnan(m[1][0]),
                      isnan(m[1][1]));
}
template <typename T> inline Matrix3x3<T> isnan(const Matrix3x3<T> &m) {
  return Matrix3x3<T>(isnan(m[0][0]), isnan(m[0][1]), isnan(m[0][2]),
                      isnan(m[1][0]), isnan(m[1][1]), isnan(m[1][2]),
                      isnan(m[2][0]), isnan(m[2][1]), isnan(m[2][2]));
}
template <typename T> inline Matrix4x4<T> isnan(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(
      isnan(m[0][0]), isnan(m[0][1]), isnan(m[0][2]), isnan(m[0][3]),
      isnan(m[1][0]), isnan(m[1][1]), isnan(m[1][2]), isnan(m[1][3]),
      isnan(m[2][0]), isnan(m[2][1]), isnan(m[2][2]), isnan(m[2][3]),
      isnan(m[3][0]), isnan(m[3][1]), isnan(m[3][2]), isnan(m[3][3]));
}

template <typename T> T min(T &s1, T &s2) { return std::min(s1, s2); }
template <typename T>
Vector2<T> min(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
}
template <typename T>
Vector3<T> min(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector2<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
}
template <typename T>
Vector4<T> min(const Vector4<T> &v1, const Vector4<T> &v2) {
  return Vector2<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z),
                    min(v1.w, v2.w));
}
template <typename T> Point2<T> min(const Point2<T> &v1, const Point2<T> &v2) {
  return Point2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
}
template <typename T> Point3<T> min(const Point3<T> &v1, const Point3<T> &v2) {
  return Point2<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
}
template <typename T> Point4<T> min(const Point4<T> &v1, const Point4<T> &v2) {
  return Point2<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z),
                   min(v1.w, v2.w));
}
template <typename T>
Normal2<T> min(const Normal2<T> &v1, const Normal2<T> &v2) {
  return Normal2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
}
template <typename T>
Normal3<T> min(const Normal3<T> &v1, const Normal3<T> &v2) {
  return Normal2<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
}
template <typename T>
Normal4<T> min(const Normal4<T> &v1, const Normal4<T> &v2) {
  return Normal2<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z),
                    min(v1.w, v2.w));
}

template <typename T> T max(T &s1, T &s2) { return std::max(s1, s2); }
template <typename T>
Vector2<T> max(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
}
template <typename T>
Vector3<T> max(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector2<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
}
template <typename T>
Vector4<T> max(const Vector4<T> &v1, const Vector4<T> &v2) {
  return Vector2<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z),
                    max(v1.w, v2.w));
}
template <typename T> Point2<T> max(const Point2<T> &v1, const Point2<T> &v2) {
  return Point2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
}
template <typename T> Point3<T> max(const Point3<T> &v1, const Point3<T> &v2) {
  return Point2<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
}
template <typename T> Point4<T> max(const Point4<T> &v1, const Point4<T> &v2) {
  return Point2<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z),
                   max(v1.w, v2.w));
}
template <typename T>
Normal2<T> max(const Normal2<T> &v1, const Normal2<T> &v2) {
  return Normal2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
}
template <typename T>
Normal3<T> max(const Normal3<T> &v1, const Normal3<T> &v2) {
  return Normal2<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
}
template <typename T>
Normal4<T> max(const Normal4<T> &v1, const Normal4<T> &v2) {
  return Normal2<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z),
                    max(v1.w, v2.w));
}

template <typename T> T min_component(const Vector2<T> &v) {
  return min(v.x, v.y);
}
template <typename T> T min_component(const Vector3<T> &v) {
  return min(v.x, min(v.y, v.z));
}
template <typename T> T min_component(const Vector4<T> &v) {
  return min(v.x, min(v.y, min(v.z, v.w)));
}
template <typename T> T min_component(const Point2<T> &v) {
  return min(v.x, v.y);
}
template <typename T> T min_component(const Point3<T> &v) {
  return min(v.x, min(v.y, v.z));
}
template <typename T> T min_component(const Point4<T> &v) {
  return min(v.x, min(v.y, min(v.z, v.w)));
}
template <typename T> T min_component(const Normal2<T> &v) {
  return min(v.x, v.y);
}
template <typename T> T min_component(const Normal3<T> &v) {
  return min(v.x, min(v.y, v.z));
}
template <typename T> T min_component(const Normal4<T> &v) {
  return min(v.x, min(v.y, min(v.z, v.w)));
}

template <typename T> T max_component(const Vector2<T> &v) {
  return max(v.x, v.y);
}
template <typename T> T max_component(const Vector3<T> &v) {
  return max(v.x, max(v.y, v.z));
}
template <typename T> T max_component(const Vector4<T> &v) {
  return max(v.x, max(v.y, max(v.z, v.w)));
}
template <typename T> T max_component(const Point2<T> &v) {
  return max(v.x, v.y);
}
template <typename T> T max_component(const Point3<T> &v) {
  return max(v.x, max(v.y, v.z));
}
template <typename T> T max_component(const Point4<T> &v) {
  return max(v.x, max(v.y, max(v.z, v.w)));
}
template <typename T> T max_component(const Normal2<T> &v) {
  return max(v.x, v.y);
}
template <typename T> T max_component(const Normal3<T> &v) {
  return max(v.x, max(v.y, v.z));
}
template <typename T> T max_component(const Normal4<T> &v) {
  return max(v.x, max(v.y, max(v.z, v.w)));
}

template <typename T>
Vector2<T> permute(const Vector2<T> &v, typename Vector2<T>::size_type x,
                   typename Vector2<T>::size_type y) {
  return Vector2<T>(v[x], v[y]);
}
template <typename T>
Vector3<T> permute(const Vector3<T> &v, typename Vector3<T>::size_type x,
                   typename Vector3<T>::size_type y,
                   typename Vector3<T>::size_type z) {
  return Vector3<T>(v[x], v[y], v[z]);
}
template <typename T>
Vector4<T> permute(const Vector4<T> &v, typename Vector4<T>::size_type x,
                   typename Vector4<T>::size_type y,
                   typename Vector4<T>::size_type z,
                   typename Vector4<T>::size_type w) {
  return Vector4<T>(v[x], v[y], v[z], v[w]);
}
template <typename T>
Point2<T> permute(const Point2<T> &v, typename Point2<T>::size_type x,
                  typename Point2<T>::size_type y) {
  return Point2<T>(v[x], v[y]);
}
template <typename T>
Point3<T> permute(const Point3<T> &v, typename Point3<T>::size_type x,
                  typename Point3<T>::size_type y,
                  typename Point3<T>::size_type z) {
  return Point3<T>(v[x], v[y], v[z]);
}
template <typename T>
Point4<T> permute(const Point4<T> &v, typename Point4<T>::size_type x,
                  typename Point4<T>::size_type y,
                  typename Point4<T>::size_type z,
                  typename Point4<T>::size_type w) {
  return Point4<T>(v[x], v[y], v[z], v[w]);
}
template <typename T>
Normal2<T> permute(const Normal2<T> &v, typename Normal2<T>::size_type x,
                   typename Normal2<T>::size_type y) {
  return Normal2<T>(v[x], v[y]);
}
template <typename T>
Normal3<T> permute(const Normal3<T> &v, typename Normal3<T>::size_type x,
                   typename Normal3<T>::size_type y,
                   typename Normal3<T>::size_type z) {
  return Normal3<T>(v[x], v[y], v[z]);
}
template <typename T>
Normal4<T> permute(const Normal4<T> &v, typename Normal4<T>::size_type x,
                   typename Normal4<T>::size_type y,
                   typename Normal4<T>::size_type z,
                   typename Normal4<T>::size_type w) {
  return Normal4<T>(v[x], v[y], v[z], v[w]);
}

} // namespace specula

#endif // SPECULA_MATH_COMMON_HPP_
