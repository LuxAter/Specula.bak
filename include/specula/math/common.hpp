#ifndef SPECULA_MATH_COMMON_HPP_
#define SPECULA_MATH_COMMON_HPP_

#include "../global.hpp"

#include "bounds.hpp"
#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "vector.hpp"

namespace specula {

/**
 * @ingroup Math
 * @brief Computes the absolute value of some value
 *
 * This is equivalent to `std::abs(s)`, but is preferred in conjunction with the
 * other overloaded versions of `abs`.
 *
 * @tparam T Value type of `s`
 * @param s Value to compute the absolute value of
 *
 * @return The absolute value of `s`.
 * @see abs(const Matrix2x2<T>&),
 *      abs(const Matrix3x3<T>&),
 *      abs(const Matrix4x4<T>&),
 *      abs(const Normal2<T>&),
 *      abs(const Normal3<T>&),
 *      abs(const Normal4<T>&),
 *      abs(const Point2<T>&),
 *      abs(const Point3<T>&),
 *      abs(const Point4<T>&),
 *      abs(const Vector2<T>&),
 *      abs(const Vector3<T>&),
 *      abs(const Vector4<T>&),
 */
template <typename T> inline T abs(const T &s) { return std::abs(s); }
/**
 * @ingroup Math Vector
 * @brief Computes the absolute value of some `Vector2`
 *
 * This computes the absolute value element wise for the vector.
 *
 * @tparam T Value type of vector class
 * @param v Vector to compute the absolute value of
 *
 * @return The absolute value of the vector `v`.
 * @see abs(const T&)
 */
template <typename T> inline Vector2<T> abs(const Vector2<T> &v) {
  return Vector2<T>(abs(v.x), abs(v.y));
}
/**
 * @ingroup Math Vector
 * @brief Computes the absolute value of some `Vector3`
 *
 * This computes the absolute value element wise for the vector.
 *
 * @tparam T Value type of vector class
 * @param v Vector to compute the absolute value of
 *
 * @return The absolute value of the vector `v`.
 * @see abs(const T&)
 */
template <typename T> inline Vector3<T> abs(const Vector3<T> &v) {
  return Vector3<T>(abs(v.x), abs(v.y), abs(v.z));
}
/**
 * @ingroup Math Vector
 * @brief Computes the absolute value of some `Vector4`
 *
 * This computes the absolute value element wise for the vector.
 *
 * @tparam T Value type of vector class
 * @param v Vector to compute the absolute value of
 *
 * @return The absolute value of the vector `v`.
 * @see abs(const T&)
 */
template <typename T> inline Vector4<T> abs(const Vector4<T> &v) {
  return Vector4<T>(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
}
/**
 * @ingroup Math Point
 * @brief Computes the absolute value of some `Point2`
 *
 * This computes the absolute value element wise for the point.
 *
 * @tparam T Value type of point class
 * @param p Point to compute the absolute value of
 *
 * @return The absolute value of the point `p`.
 * @see abs(const T&)
 */
template <typename T> inline Point2<T> abs(const Point2<T> &p) {
  return Point2<T>(abs(p.x), abs(p.y));
}
/**
 * @ingroup Math Point
 * @brief Computes the absolute value of some `Point3`
 *
 * This computes the absolute value element wise for the point.
 *
 * @tparam T Value type of point class
 * @param p Point to compute the absolute value of
 *
 * @return The absolute value of the point `p`.
 * @see abs(const T&)
 */
template <typename T> inline Point3<T> abs(const Point3<T> &p) {
  return Point3<T>(abs(p.x), abs(p.y), abs(p.z));
}
/**
 * @ingroup Math Point
 * @brief Computes the absolute value of some `Point4`
 *
 * This computes the absolute value element wise for the point.
 *
 * @tparam T Value type of point class
 * @param p Point to compute the absolute value of
 *
 * @return The absolute value of the point `p`.
 * @see abs(const T&)
 */
template <typename T> inline Point4<T> abs(const Point4<T> &p) {
  return Point4<T>(abs(p.x), abs(p.y), abs(p.z), abs(p.w));
}
/**
 * @ingroup Math Normal
 * @brief Computes the absolute value of some `Normal2`
 *
 * This computes the absolute value element wise for the normal.
 *
 * @tparam T Value type of normal class
 * @param n Normal to compute the absolute value of
 *
 * @return The absolute value of the normal `n`.
 * @see abs(const T&)
 */
template <typename T> inline Normal2<T> abs(const Normal2<T> &n) {
  return Normal2<T>(abs(n.x), abs(n.y));
}
/**
 * @ingroup Math Normal
 * @brief Computes the absolute value of some `Normal3`
 *
 * This computes the absolute value element wise for the normal.
 *
 * @tparam T Value type of normal class
 * @param n Normal to compute the absolute value of
 *
 * @return The absolute value of the normal `n`.
 * @see abs(const T&)
 */
template <typename T> inline Normal3<T> abs(const Normal3<T> &n) {
  return Normal3<T>(abs(n.x), abs(n.y), abs(n.z));
}
/**
 * @ingroup Math Normal
 * @brief Computes the absolute value of some `Normal4`
 *
 * This computes the absolute value element wise for the normal.
 *
 * @tparam T Value type of normal class
 * @param n Normal to compute the absolute value of
 *
 * @return The absolute value of the normal `n`.
 * @see abs(const T&)
 */
template <typename T> inline Normal4<T> abs(const Normal4<T> &n) {
  return Normal4<T>(abs(n.x), abs(n.y), abs(n.z), abs(n.w));
}
/**
 * @ingroup Math Matrix
 * @brief Computes the absolute value of some `Matrix2x2`
 *
 * This computes the absolute value element wise for the matrix.
 *
 * @tparam T Value type of matrix class
 * @param m Matrix to compute the absolute value of
 *
 * @return The absolute value of the matrix `m`.
 * @see abs(const T&)
 */
template <typename T> inline Matrix2x2<T> abs(const Matrix2x2<T> &m) {
  return Matrix2x2<T>(abs(m[0][0]), abs(m[0][1]), abs(m[1][0]), abs(m[1][1]));
}
/**
 * @ingroup Math Matrix
 * @brief Computes the absolute value of some `Matrix3x3`
 *
 * This computes the absolute value element wise for the matrix.
 *
 * @tparam T Value type of matrix class
 * @param m Matrix to compute the absolute value of
 *
 * @return The absolute value of the matrix `m`.
 * @see abs(const T&)
 */
template <typename T> inline Matrix3x3<T> abs(const Matrix3x3<T> &m) {
  return Matrix3x3<T>(abs(m[0][0]), abs(m[0][1]), abs(m[0][2]), abs(m[1][0]),
                      abs(m[1][1]), abs(m[1][2]), abs(m[2][0]), abs(m[2][1]),
                      abs(m[2][2]));
}
/**
 * @ingroup Math Matrix
 * @brief Computes the absolute value of some `Matrix4x4`
 *
 * This computes the absolute value element wise for the matrix.
 *
 * @tparam T Value type of matrix class
 * @param m Matrix to compute the absolute value of
 *
 * @return The absolute value of the matrix `m`.
 * @see abs(const T&)
 */
template <typename T> inline Matrix4x4<T> abs(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(abs(m[0][0]), abs(m[0][1]), abs(m[0][2]), abs(m[0][3]),
                      abs(m[1][0]), abs(m[1][1]), abs(m[1][2]), abs(m[1][3]),
                      abs(m[2][0]), abs(m[2][1]), abs(m[2][2]), abs(m[2][3]),
                      abs(m[3][0]), abs(m[3][1]), abs(m[3][2]), abs(m[3][3]));
}

/**
 * @ingroup Math
 * @brief Computes the ceiling of the provided value.
 *
 * This is equivalent to `std::ceil(s)`, but is preferred in conjunction with
 * the other overloaded versions of `ceil`.
 *
 * @tparam T Value type of `s`
 * @param s Value to compute the ceiling value of
 *
 * @return The value of `s` rounded up to the ceiling.
 * @see ceil(const Matrix2x2<T>&),
 *      ceil(const Matrix3x3<T>&),
 *      ceil(const Matrix4x4<T>&),
 *      ceil(const Normal2<T>&),
 *      ceil(const Normal3<T>&),
 *      ceil(const Normal4<T>&),
 *      ceil(const Point2<T>&),
 *      ceil(const Point3<T>&),
 *      ceil(const Point4<T>&),
 *      ceil(const Vector2<T>&),
 *      ceil(const Vector3<T>&),
 *      ceil(const Vector4<T>&),
 */
template <typename T> inline T ceil(const T &s) { return std::ceil(s); }
/**
 * @ingroup Math Vector
 * @brief Computes the ceiling of the provided `Vector2`.
 *
 * This computes the ceiling element wise for the vector.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to compute the ceiling of
 *
 * @return The vector `v` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Vector2<T> ceil(const Vector2<T> &v) {
  return Vector2<T>(ceil(v.x), ceil(v.y));
}
/**
 * @ingroup Math Vector
 * @brief Computes the ceiling of the provided `Vector3`.
 *
 * This computes the ceiling element wise for the vector.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to compute the ceiling of
 *
 * @return The vector `v` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Vector3<T> ceil(const Vector3<T> &v) {
  return Vector3<T>(ceil(v.x), ceil(v.y), ceil(v.z));
}
/**
 * @ingroup Math Vector
 * @brief Computes the ceiling of the provided `Vector4`.
 *
 * This computes the ceiling element wise for the vector.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to compute the ceiling of
 *
 * @return The vector `v` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Vector4<T> ceil(const Vector4<T> &v) {
  return Vector4<T>(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
}
/**
 * @ingroup Math Point
 * @brief Computes the ceiling of the provided `Point2`.
 *
 * This computes the ceiling element wise for the point.
 *
 * @tparam T Value type of the point class
 * @param p Point to compute the ceiling of
 *
 * @return The point `p` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Point2<T> ceil(const Point2<T> &p) {
  return Point2<T>(ceil(p.x), ceil(p.y));
}
/**
 * @ingroup Math Point
 * @brief Computes the ceiling of the provided `Point3`.
 *
 * This computes the ceiling element wise for the point.
 *
 * @tparam T Value type of the point class
 * @param p Point to compute the ceiling of
 *
 * @return The point `p` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Point3<T> ceil(const Point3<T> &p) {
  return Point3<T>(ceil(p.x), ceil(p.y), ceil(p.z));
}
/**
 * @ingroup Math Point
 * @brief Computes the ceiling of the provided `Point4`.
 *
 * This computes the ceiling element wise for the point.
 *
 * @tparam T Value type of the point class
 * @param p Point to compute the ceiling of
 *
 * @return The point `p` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Point4<T> ceil(const Point4<T> &p) {
  return Point4<T>(ceil(p.x), ceil(p.y), ceil(p.z), ceil(p.w));
}
/**
 * @ingroup Math Normal
 * @brief Computes the ceiling of the provided `Normal2`.
 *
 * This computes the ceiling element wise for the normal.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to compute the ceiling of
 *
 * @return The normal `n` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Normal2<T> ceil(const Normal2<T> &n) {
  return Normal2<T>(ceil(n.x), ceil(n.y));
}
/**
 * @ingroup Math Normal
 * @brief Computes the ceiling of the provided `Normal3`.
 *
 * This computes the ceiling element wise for the normal.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to compute the ceiling of
 *
 * @return The normal `n` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Normal3<T> ceil(const Normal3<T> &n) {
  return Normal3<T>(ceil(n.x), ceil(n.y), ceil(n.z));
}
/**
 * @ingroup Math Normal
 * @brief Computes the ceiling of the provided `Normal4`.
 *
 * This computes the ceiling element wise for the normal.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to compute the ceiling of
 *
 * @return The normal `n` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Normal4<T> ceil(const Normal4<T> &n) {
  return Normal4<T>(ceil(n.x), ceil(n.y), ceil(n.z), ceil(n.w));
}
/**
 * @ingroup Math Matrix
 * @brief Computes the ceiling of the provided `Matrix2x2`.
 *
 * This computes the ceiling element wise for the matrix.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to compute the ceiling of
 *
 * @return The matrix `m` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Matrix2x2<T> ceil(const Matrix2x2<T> &m) {
  return Matrix2x2<T>(ceil(m[0][0]), ceil(m[0][1]), ceil(m[1][0]),
                      ceil(m[1][1]));
}
/**
 * @ingroup Math Matrix
 * @brief Computes the ceiling of the provided `Matrix3x3`.
 *
 * This computes the ceiling element wise for the matrix.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to compute the ceiling of
 *
 * @return The matrix `m` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Matrix3x3<T> ceil(const Matrix3x3<T> &m) {
  return Matrix3x3<T>(ceil(m[0][0]), ceil(m[0][1]), ceil(m[0][2]),
                      ceil(m[1][0]), ceil(m[1][1]), ceil(m[1][2]),
                      ceil(m[2][0]), ceil(m[2][1]), ceil(m[2][2]));
}
/**
 * @ingroup Math Matrix
 * @brief Computes the ceiling of the provided `Matrix4x4`.
 *
 * This computes the ceiling element wise for the matrix.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to compute the ceiling of
 *
 * @return The matrix `m` with each element rounded up to the ceiling.
 * @see ceil(const T&)
 */
template <typename T> inline Matrix4x4<T> ceil(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(
      ceil(m[0][0]), ceil(m[0][1]), ceil(m[0][2]), ceil(m[0][3]), ceil(m[1][0]),
      ceil(m[1][1]), ceil(m[1][2]), ceil(m[1][3]), ceil(m[2][0]), ceil(m[2][1]),
      ceil(m[2][2]), ceil(m[2][3]), ceil(m[3][0]), ceil(m[3][1]), ceil(m[3][2]),
      ceil(m[3][3]));
}

/**
 * @ingroup Math
 * @brief Computes the floor of the provided value.
 *
 * This is equivalent to `std::floor(s)`, but is preferred in conjunction with
 * the other overloaded versions of `floor`.
 *
 * @tparam T Value type of `s`
 * @param s Value to compute the floor value of
 *
 * @return The value of `s` rounded down to the floor.
 * @see floor(const Matrix2x2<T>&),
 *      floor(const Matrix3x3<T>&),
 *      floor(const Matrix4x4<T>&),
 *      floor(const Normal2<T>&),
 *      floor(const Normal3<T>&),
 *      floor(const Normal4<T>&),
 *      floor(const Point2<T>&),
 *      floor(const Point3<T>&),
 *      floor(const Point4<T>&),
 *      floor(const Vector2<T>&),
 *      floor(const Vector3<T>&),
 *      floor(const Vector4<T>&),
 */
template <typename T> inline T floor(const T &s) { return std::floor(s); }
/**
 * @ingroup Math Vector
 * @brief Computes the floor of the provided `Vector2`.
 *
 * This computes the floor element wise for the vector.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to compute the floor of
 *
 * @return The vector `v` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Vector2<T> floor(const Vector2<T> &v) {
  return Vector2<T>(floor(v.x), floor(v.y));
}
/**
 * @ingroup Math Vector
 * @brief Computes the floor of the provided `Vector3`.
 *
 * This computes the floor element wise for the vector.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to compute the floor of
 *
 * @return The vector `v` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Vector3<T> floor(const Vector3<T> &v) {
  return Vector3<T>(floor(v.x), floor(v.y), floor(v.z));
}
/**
 * @ingroup Math Vector
 * @brief Computes the floor of the provided `Vector4`.
 *
 * This computes the floor element wise for the vector.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to compute the floor of
 *
 * @return The vector `v` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Vector4<T> floor(const Vector4<T> &v) {
  return Vector4<T>(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
}
/**
 * @ingroup Math Point
 * @brief Computes the floor of the provided `Point2`.
 *
 * This computes the floor element wise for the point.
 *
 * @tparam T Value type of the point class
 * @param v Point to compute the floor of
 *
 * @return The point `p` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Point2<T> floor(const Point2<T> &p) {
  return Point2<T>(floor(p.x), floor(p.y));
}
/**
 * @ingroup Math Point
 * @brief Computes the floor of the provided `Point3`.
 *
 * This computes the floor element wise for the point.
 *
 * @tparam T Value type of the point class
 * @param v Point to compute the floor of
 *
 * @return The point `p` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Point3<T> floor(const Point3<T> &p) {
  return Point3<T>(floor(p.x), floor(p.y), floor(p.z));
}
/**
 * @ingroup Math Point
 * @brief Computes the floor of the provided `Point4`.
 *
 * This computes the floor element wise for the point.
 *
 * @tparam T Value type of the point class
 * @param v Point to compute the floor of
 *
 * @return The point `p` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Point4<T> floor(const Point4<T> &p) {
  return Point4<T>(floor(p.x), floor(p.y), floor(p.z), floor(p.w));
}
/**
 * @ingroup Math Normal
 * @brief Computes the floor of the provided `Normal2`.
 *
 * This computes the floor element wise for the normal.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to compute the floor of
 *
 * @return The normal `n` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Normal2<T> floor(const Normal2<T> &n) {
  return Normal2<T>(floor(n.x), floor(n.y));
}
/**
 * @ingroup Math Normal
 * @brief Computes the floor of the provided `Normal3`.
 *
 * This computes the floor element wise for the normal.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to compute the floor of
 *
 * @return The normal `n` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Normal3<T> floor(const Normal3<T> &n) {
  return Normal3<T>(floor(n.x), floor(n.y), floor(n.z));
}
/**
 * @ingroup Math Normal
 * @brief Computes the floor of the provided `Normal4`.
 *
 * This computes the floor element wise for the normal.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to compute the floor of
 *
 * @return The normal `n` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Normal4<T> floor(const Normal4<T> &n) {
  return Normal4<T>(floor(n.x), floor(n.y), floor(n.z), floor(n.w));
}
/**
 * @ingroup Math Matrix
 * @brief Computes the floor of the provided `Matrix2x2`.
 *
 * This computes the floor element wise for the matrix.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to compute the floor of
 *
 * @return The matrix `m` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Matrix2x2<T> floor(const Matrix2x2<T> &m) {
  return Matrix2x2<T>(floor(m[0][0]), floor(m[0][1]), floor(m[1][0]),
                      floor(m[1][1]));
}
/**
 * @ingroup Math Matrix
 * @brief Computes the floor of the provided `Matrix3x3`.
 *
 * This computes the floor element wise for the matrix.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to compute the floor of
 *
 * @return The matrix `m` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Matrix3x3<T> floor(const Matrix3x3<T> &m) {
  return Matrix3x3<T>(floor(m[0][0]), floor(m[0][1]), floor(m[0][2]),
                      floor(m[1][0]), floor(m[1][1]), floor(m[1][2]),
                      floor(m[2][0]), floor(m[2][1]), floor(m[2][2]));
}
/**
 * @ingroup Math Matrix
 * @brief Computes the floor of the provided `Matrix4x4`.
 *
 * This computes the floor element wise for the matrix.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to compute the floor of
 *
 * @return The matrix `m` with each element rounded down to the floor.
 * @see floor(const T&)
 */
template <typename T> inline Matrix4x4<T> floor(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(
      floor(m[0][0]), floor(m[0][1]), floor(m[0][2]), floor(m[0][3]),
      floor(m[1][0]), floor(m[1][1]), floor(m[1][2]), floor(m[1][3]),
      floor(m[2][0]), floor(m[2][1]), floor(m[2][2]), floor(m[2][3]),
      floor(m[3][0]), floor(m[3][1]), floor(m[3][2]), floor(m[3][3]));
}

/**
 * @ingroup Math
 * @brief Check if value is infinity
 *
 * This is equivalent to `std::isinf(s)`, but is preferred in conjunction with
 * the other overloaded versions of `isinf`.
 *
 * @tparam T Value type of `s`
 * @param s Value to check
 *
 * @return `true` if `s` is infinity, `false` otherwise
 * @see isinf(const Matrix2x2<T>&),
 *      isinf(const Matrix3x3<T>&),
 *      isinf(const Matrix4x4<T>&),
 *      isinf(const Normal2<T>&),
 *      isinf(const Normal3<T>&),
 *      isinf(const Normal4<T>&),
 *      isinf(const Point2<T>&),
 *      isinf(const Point3<T>&),
 *      isinf(const Point4<T>&),
 *      isinf(const Vector2<T>&),
 *      isinf(const Vector3<T>&),
 *      isinf(const Vector4<T>&),
 */
template <typename T> inline T isinf(const T &s) { return std::isinf(s); }
/**
 * @ingroup Math Vector
 * @brief Check if `Vector2` is infinity
 *
 * This checks if any elements of the vector are infinity.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to check
 *
 * @return `true` if any elements of `v` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline bool isinf(const Vector2<T> &v) {
  return isinf(v.x) || isinf(v.y);
}
/**
 * @ingroup Math Vector
 * @brief Check if `Vector3` is infinity
 *
 * This checks if any elements of the vector are infinity.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to check
 *
 * @return `true` if any elements of `v` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Vector3<T> isinf(const Vector3<T> &v) {
  return isinf(v.x) || isinf(v.y) || isinf(v.z);
}
/**
 * @ingroup Math Vector
 * @brief Check if `Vector4` is infinity
 *
 * This checks if any elements of the vector are infinity.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to check
 *
 * @return `true` if any elements of `v` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Vector4<T> isinf(const Vector4<T> &v) {
  return isinf(v.x) || isinf(v.y) || isinf(v.z) || isinf(v.w);
}
/**
 * @ingroup Math Point
 * @brief Check if `Point2` is infinity
 *
 * This checks if any elements of the point are infinity.
 *
 * @tparam T Value type of the point class
 * @param p Point to check
 *
 * @return `true` if any elements of `p` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Point2<T> isinf(const Point2<T> &p) {
  return isinf(p.x) || isinf(p.y);
}
/**
 * @ingroup Math Point
 * @brief Check if `Point3` is infinity
 *
 * This checks if any elements of the point are infinity.
 *
 * @tparam T Value type of the point class
 * @param p Point to check
 *
 * @return `true` if any elements of `p` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Point3<T> isinf(const Point3<T> &p) {
  return isinf(p.x) || isinf(p.y) || isinf(p.z);
}
/**
 * @ingroup Math Point
 * @brief Check if `Point4` is infinity
 *
 * This checks if any elements of the point are infinity.
 *
 * @tparam T Value type of the point class
 * @param p Point to check
 *
 * @return `true` if any elements of `p` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Point4<T> isinf(const Point4<T> &p) {
  return isinf(p.x) || isinf(p.y) || isinf(p.z) || isinf(p.w);
}
/**
 * @ingroup Math Normal
 * @brief Check if `Normal2` is infinity
 *
 * This checks if any elements of the normal are infinity.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to check
 *
 * @return `true` if any elements of `n` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Normal2<T> isinf(const Normal2<T> &n) {
  return isinf(n.x) || isinf(n.y);
}
/**
 * @ingroup Math Normal
 * @brief Check if `Normal3` is infinity
 *
 * This checks if any elements of the normal are infinity.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to check
 *
 * @return `true` if any elements of `n` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Normal3<T> isinf(const Normal3<T> &n) {
  return isinf(n.x) || isinf(n.y) || isinf(n.z);
}
/**
 * @ingroup Math Normal
 * @brief Check if `Normal4` is infinity
 *
 * This checks if any elements of the normal are infinity.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to check
 *
 * @return `true` if any elements of `n` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Normal4<T> isinf(const Normal4<T> &n) {
  return isinf(n.x) || isinf(n.y) || isinf(n.z) || isinf(n.w);
}
/**
 * @ingroup Math Matrix
 * @brief Check if `Matrix2x2` is infinity
 *
 * This checks if any elements of the matrix are infinity.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to check
 *
 * @return `true` if any elements of `m` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Matrix2x2<T> isinf(const Matrix2x2<T> &m) {
  return isinf(m[0][0]) || isinf(m[0][1]) || isinf(m[1][0]) || isinf(m[1][1]);
}
/**
 * @ingroup Math Matrix
 * @brief Check if `Matrix3x3` is infinity
 *
 * This checks if any elements of the matrix are infinity.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to check
 *
 * @return `true` if any elements of `m` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Matrix3x3<T> isinf(const Matrix3x3<T> &m) {
  return isinf(m[0][0]) || isinf(m[0][1]) || isinf(m[0][2]) || isinf(m[1][0]) ||
         isinf(m[1][1]) || isinf(m[1][2]) || isinf(m[2][0]) || isinf(m[2][1]) ||
         isinf(m[2][2]);
}
/**
 * @ingroup Math Matrix
 * @brief Check if `Matrix4x4` is infinity
 *
 * This checks if any elements of the matrix are infinity.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to check
 *
 * @return `true` if any elements of `m` are infinity, `false` otherwise
 * @see isinf(const T& s)
 */
template <typename T> inline Matrix4x4<T> isinf(const Matrix4x4<T> &m) {
  return isinf(m[0][0]) || isinf(m[0][1]) || isinf(m[0][2]) || isinf(m[0][3]) ||
         isinf(m[1][0]) || isinf(m[1][1]) || isinf(m[1][2]) || isinf(m[1][3]) ||
         isinf(m[2][0]) || isinf(m[2][1]) || isinf(m[2][2]) || isinf(m[2][3]) ||
         isinf(m[3][0]) || isinf(m[3][1]) || isinf(m[3][2]) || isinf(m[3][3]);
}

/**
 * @ingroup Math
 * @brief Check if value is not a number
 *
 * This is equivalent to `std::isnan(s)`, but is preferred in conjunction with
 * the other overloaded versions of `isnan`.
 *
 * @tparam T Value type of `s`
 * @param s Value to check
 *
 * @return `true` if `s` is not a number, `false` otherwise
 * @see isnan(const Matrix2x2<T>&),
 *      isnan(const Matrix3x3<T>&),
 *      isnan(const Matrix4x4<T>&),
 *      isnan(const Normal2<T>&),
 *      isnan(const Normal3<T>&),
 *      isnan(const Normal4<T>&),
 *      isnan(const Point2<T>&),
 *      isnan(const Point3<T>&),
 *      isnan(const Point4<T>&),
 *      isnan(const Vector2<T>&),
 *      isnan(const Vector3<T>&),
 *      isnan(const Vector4<T>&),
 */
template <typename T> inline T isnan(const T &s) { return std::isnan(s); }
/**
 * @ingroup Math Vector
 * @brief Check if `Vector2` is not a number
 *
 * This checks if any elements of the vector are not a number.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to check
 *
 * @return `true` if any elements of `v` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline bool isnan(const Vector2<T> &v) {
  return isnan(v.x) || isnan(v.y);
}
/**
 * @ingroup Math Vector
 * @brief Check if `Vector3` is not a number
 *
 * This checks if any elements of the vector are not a number.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to check
 *
 * @return `true` if any elements of `v` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Vector3<T> isnan(const Vector3<T> &v) {
  return isnan(v.x) || isnan(v.y) || isnan(v.z);
}
/**
 * @ingroup Math Vector
 * @brief Check if `Vector4` is not a number
 *
 * This checks if any elements of the vector are not a number.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to check
 *
 * @return `true` if any elements of `v` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Vector4<T> isnan(const Vector4<T> &v) {
  return isnan(v.x) || isnan(v.y) || isnan(v.z) || isnan(v.w);
}
/**
 * @ingroup Math Point
 * @brief Check if `Point2` is not a number
 *
 * This checks if any elements of the point are not a number.
 *
 * @tparam T Value type of the point class
 * @param p Point to check
 *
 * @return `true` if any elements of `p` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Point2<T> isnan(const Point2<T> &p) {
  return isnan(p.x) || isnan(p.y);
}
/**
 * @ingroup Math Point
 * @brief Check if `Point3` is not a number
 *
 * This checks if any elements of the point are not a number.
 *
 * @tparam T Value type of the point class
 * @param p Point to check
 *
 * @return `true` if any elements of `p` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Point3<T> isnan(const Point3<T> &p) {
  return isnan(p.x) || isnan(p.y) || isnan(p.z);
}
/**
 * @ingroup Math Point
 * @brief Check if `Point4` is not a number
 *
 * This checks if any elements of the point are not a number.
 *
 * @tparam T Value type of the point class
 * @param p Point to check
 *
 * @return `true` if any elements of `p` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Point4<T> isnan(const Point4<T> &p) {
  return isnan(p.x) || isnan(p.y) || isnan(p.z) || isnan(p.w);
}
/**
 * @ingroup Math Normal
 * @brief Check if `Normal2` is not a number
 *
 * This checks if any elements of the normal are not a number.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to check
 *
 * @return `true` if any elements of `n` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Normal2<T> isnan(const Normal2<T> &n) {
  return isnan(n.x) || isnan(n.y);
}
/**
 * @ingroup Math Normal
 * @brief Check if `Normal3` is not a number
 *
 * This checks if any elements of the normal are not a number.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to check
 *
 * @return `true` if any elements of `n` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Normal3<T> isnan(const Normal3<T> &n) {
  return isnan(n.x) || isnan(n.y) || isnan(n.z);
}
/**
 * @ingroup Math Normal
 * @brief Check if `Normal4` is not a number
 *
 * This checks if any elements of the normal are not a number.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to check
 *
 * @return `true` if any elements of `n` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Normal4<T> isnan(const Normal4<T> &n) {
  return isnan(n.x) || isnan(n.y) || isnan(n.z) || isnan(n.w);
}
/**
 * @ingroup Math Matrix
 * @brief Check if `Matrix2x2` is not a number
 *
 * This checks if any elements of the matrix are not a number.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to check
 *
 * @return `true` if any elements of `m` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Matrix2x2<T> isnan(const Matrix2x2<T> &m) {
  return isnan(m[0][0]) || isnan(m[0][1]) || isnan(m[1][0]) || isnan(m[1][1]);
}
/**
 * @ingroup Math Matrix
 * @brief Check if `Matrix3x3` is not a number
 *
 * This checks if any elements of the matrix are not a number.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to check
 *
 * @return `true` if any elements of `m` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Matrix3x3<T> isnan(const Matrix3x3<T> &m) {
  return isnan(m[0][0]) || isnan(m[0][1]) || isnan(m[0][2]) || isnan(m[1][0]) ||
         isnan(m[1][1]) || isnan(m[1][2]) || isnan(m[2][0]) || isnan(m[2][1]) ||
         isnan(m[2][2]);
}
/**
 * @ingroup Math Matrix
 * @brief Check if `Matrix4x4` is not a number
 *
 * This checks if any elements of the matrix are not a number.
 *
 * @tparam T Value type of the matrix class
 * @param m Matrix to check
 *
 * @return `true` if any elements of `m` are not a number, `false` otherwise
 * @see isnan(const T& s)
 */
template <typename T> inline Matrix4x4<T> isnan(const Matrix4x4<T> &m) {
  return isnan(m[0][0]) || isnan(m[0][1]) || isnan(m[0][2]) || isnan(m[0][3]) ||
         isnan(m[1][0]) || isnan(m[1][1]) || isnan(m[1][2]) || isnan(m[1][3]) ||
         isnan(m[2][0]) || isnan(m[2][1]) || isnan(m[2][2]) || isnan(m[2][3]) ||
         isnan(m[3][0]) || isnan(m[3][1]) || isnan(m[3][2]) || isnan(m[3][3]);
}

/**
 * @ingroup Math
 * @brief Computes the minimum of two values
 *
 * This is equivalent to `std::min(s)`, but is preferred in conjunction with the
 * other overloaded versions of `min`.
 *
 * @tparam T Value type of the values
 * @param s1 First value to consider
 * @param s2 Second value to consider
 *
 * @return `s1` if `s1<s2` otherwise `s2`.
 * @see min(const Normal2<T>&),
 *      min(const Normal3<T>&),
 *      min(const Normal4<T>&),
 *      min(const Point2<T>&),
 *      min(const Point3<T>&),
 *      min(const Point4<T>&),
 *      min(const Vector2<T>&),
 *      min(const Vector3<T>&),
 *      min(const Vector4<T>&),
 */
template <typename T> T min(T &s1, T &s2) { return std::min(s1, s2); }
/**
 * @ingroup Math Vector
 * @brief Computes the minimum of two `Vector2`s
 *
 * This computes the minimum element wise for the vector.
 *
 * @tparam T Value type for the vector classes
 * @param v1 First vector to consider
 * @param v2 Second vector to consider
 *
 * @return Vector with minimum values from `v1` and `v2`.
 * @see min(const T&, const T&)
 */
template <typename T>
Vector2<T> min(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(min(v1.x, v2.x), min(v1.y, v2.y));
}
/**
 * @ingroup Math Vector
 * @brief Computes the minimum of two `Vector3`s
 *
 * This computes the minimum element wise for the vector.
 *
 * @tparam T Value type for the vector classes
 * @param v1 First vector to consider
 * @param v2 Second vector to consider
 *
 * @return Vector with minimum values from `v1` and `v2`.
 * @see min(const T&, const T&)
 */
template <typename T>
Vector3<T> min(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector2<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
}
/**
 * @ingroup Math Vector
 * @brief Computes the minimum of two `Vector4`s
 *
 * This computes the minimum element wise for the vector.
 *
 * @tparam T Value type for the vector classes
 * @param v1 First vector to consider
 * @param v2 Second vector to consider
 *
 * @return Vector with minimum values from `v1` and `v2`.
 * @see min(const T&, const T&)
 */
template <typename T>
Vector4<T> min(const Vector4<T> &v1, const Vector4<T> &v2) {
  return Vector2<T>(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z),
                    min(v1.w, v2.w));
}
/**
 * @ingroup Math Point
 * @brief Computes the minimum of two `Point2`s
 *
 * This computes the minimum element wise for the point. 
 *
 * @tparam T Value type for the point classes
 * @param p1 First point to consider
 * @param p2 Second point to consider
 *
 * @return Point with minimum values from `p1` and `p2`.
 * @see min(const T&, const T&)
 */
template <typename T> Point2<T> min(const Point2<T> &p1, const Point2<T> &p2) {
  return Point2<T>(min(p1.x, p2.x), min(p1.y, p2.y));
}
/**
 * @ingroup Math Point
 * @brief Computes the minimum of two `Point3`s
 *
 * This computes the minimum element wise for the point. 
 *
 * @tparam T Value type for the point classes
 * @param p1 First point to consider
 * @param p2 Second point to consider
 *
 * @return Point with minimum values from `p1` and `p2`.
 * @see min(const T&, const T&)
 */
template <typename T> Point3<T> min(const Point3<T> &p1, const Point3<T> &p2) {
  return Point3<T>(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
}
/**
 * @ingroup Math Point
 * @brief Computes the minimum of two `Point4`s
 *
 * This computes the minimum element wise for the point. 
 *
 * @tparam T Value type for the point classes
 * @param p1 First point to consider
 * @param p2 Second point to consider
 *
 * @return Point with minimum values from `p1` and `p2`.
 * @see min(const T&, const T&)
 */
template <typename T> Point4<T> min(const Point4<T> &p1, const Point4<T> &p2) {
  return Point4<T>(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z),
                   min(p1.w, p2.w));
}
/**
 * @ingroup Math Normal
 * @brief Computes the minimum of two `Normal2`s
 *
 * This computes the minimum element wise for the normal.
 *
 * @tparam T Value type for the normal classes
 * @param n1 First normal to consider
 * @param n2 Second normal to consider
 *
 * @return Normal with minimum values from `n1` and `n2`.
 * @see min(const T&, const T&)
 */
template <typename T>
Normal2<T> min(const Normal2<T> &n1, const Normal2<T> &n2) {
  return Normal2<T>(min(n1.x, n2.x), min(n1.y, n2.y));
}
/**
 * @ingroup Math Normal
 * @brief Computes the minimum of two `Normal3`s
 *
 * This computes the minimum element wise for the normal.
 *
 * @tparam T Value type for the normal classes
 * @param n1 First normal to consider
 * @param n2 Second normal to consider
 *
 * @return Normal with minimum values from `n1` and `n2`.
 * @see min(const T&, const T&)
 */
template <typename T>
Normal3<T> min(const Normal3<T> &n1, const Normal3<T> &n2) {
  return Normal3<T>(min(n1.x, n2.x), min(n1.y, n2.y), min(n1.z, n2.z));
}
/**
 * @ingroup Math Normal
 * @brief Computes the minimum of two `Normal4`s
 *
 * This computes the minimum element wise for the normal.
 *
 * @tparam T Value type for the normal classes
 * @param n1 First normal to consider
 * @param n2 Second normal to consider
 *
 * @return Normal with minimum values from `n1` and `n2`.
 * @see min(const T&, const T&)
 */
template <typename T>
Normal4<T> min(const Normal4<T> &n1, const Normal4<T> &n2) {
  return Normal4<T>(min(n1.x, n2.x), min(n1.y, n2.y), min(n1.z, n2.z),
                    min(n1.w, n2.w));
}

/**
 * @ingroup Math
 * @brief Computes the maximum of two values
 *
 * This is equivalent to `std::max(s)`, but is preferred in conjunction with the
 * other overloaded versions of `max`.
 *
 * @tparam T Value type of the values
 * @param s1 First value to consider
 * @param s2 Second value to consider
 *
 * @return `s1` if `s1>2` otherwise `s2`.
 * @see max(const Normal2<T>&),
 *      max(const Normal3<T>&),
 *      max(const Normal4<T>&),
 *      max(const Point2<T>&),
 *      max(const Point3<T>&),
 *      max(const Point4<T>&),
 *      max(const Vector2<T>&),
 *      max(const Vector3<T>&),
 *      max(const Vector4<T>&),
 */
template <typename T> T max(T &s1, T &s2) { return std::max(s1, s2); }
/**
 * @ingroup Math Vector
 * @brief Computes the maximum of two `Vector2`s
 *
 * This computes the maximum element wise for the vector.
 *
 * @tparam T Value type for the vector classes
 * @param v1 First vector to consider
 * @param v2 Second vector to consider
 *
 * @return Vector with maximum values from `v1` and `v2`.
 * @see max(const T&, const T&)
 */
template <typename T>
Vector2<T> max(const Vector2<T> &v1, const Vector2<T> &v2) {
  return Vector2<T>(max(v1.x, v2.x), max(v1.y, v2.y));
}
/**
 * @ingroup Math Vector
 * @brief Computes the maximum of two `Vector3`s
 *
 * This computes the maximum element wise for the vector.
 *
 * @tparam T Value type for the vector classes
 * @param v1 First vector to consider
 * @param v2 Second vector to consider
 *
 * @return Vector with maximum values from `v1` and `v2`.
 * @see max(const T&, const T&)
 */
template <typename T>
Vector3<T> max(const Vector3<T> &v1, const Vector3<T> &v2) {
  return Vector2<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
}
/**
 * @ingroup Math Vector
 * @brief Computes the maximum of two `Vector4`s
 *
 * This computes the maximum element wise for the vector.
 *
 * @tparam T Value type for the vector classes
 * @param v1 First vector to consider
 * @param v2 Second vector to consider
 *
 * @return Vector with maximum values from `v1` and `v2`.
 * @see max(const T&, const T&)
 */
template <typename T>
Vector4<T> max(const Vector4<T> &v1, const Vector4<T> &v2) {
  return Vector2<T>(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z),
                    max(v1.w, v2.w));
}
/**
 * @ingroup Math Point
 * @brief Computes the maximum of two `Point2`s
 *
 * This computes the maximum element wise for the point. 
 *
 * @tparam T Value type for the point classes
 * @param p1 First point to consider
 * @param p2 Second point to consider
 *
 * @return Point with maximum values from `p1` and `p2`.
 * @see max(const T&, const T&)
 */
template <typename T> Point2<T> max(const Point2<T> &p1, const Point2<T> &p2) {
  return Point2<T>(max(p1.x, p2.x), max(p1.y, p2.y));
}
/**
 * @ingroup Math Point
 * @brief Computes the maximum of two `Point3`s
 *
 * This computes the maximum element wise for the point. 
 *
 * @tparam T Value type for the point classes
 * @param p1 First point to consider
 * @param p2 Second point to consider
 *
 * @return Point with maximum values from `p1` and `p2`.
 * @see max(const T&, const T&)
 */
template <typename T> Point3<T> max(const Point3<T> &p1, const Point3<T> &p2) {
  return Point3<T>(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
}
/**
 * @ingroup Math Point
 * @brief Computes the maximum of two `Point4`s
 *
 * This computes the maximum element wise for the point. 
 *
 * @tparam T Value type for the point classes
 * @param p1 First point to consider
 * @param p2 Second point to consider
 *
 * @return Point with maximum values from `p1` and `p2`.
 * @see max(const T&, const T&)
 */
template <typename T> Point4<T> max(const Point4<T> &p1, const Point4<T> &p2) {
  return Point4<T>(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z),
                   max(p1.w, p2.w));
}
/**
 * @ingroup Math Normal
 * @brief Computes the maximum of two `Normal2`s
 *
 * This computes the maximum element wise for the normal.
 *
 * @tparam T Value type for the normal classes
 * @param n1 First normal to consider
 * @param n2 Second normal to consider
 *
 * @return Normal with maximum values from `n1` and `n2`.
 * @see max(const T&, const T&)
 */
template <typename T>
Normal2<T> max(const Normal2<T> &n1, const Normal2<T> &n2) {
  return Normal2<T>(max(n1.x, n2.x), max(n1.y, n2.y));
}
/**
 * @ingroup Math Normal
 * @brief Computes the maximum of two `Normal3`s
 *
 * This computes the maximum element wise for the normal.
 *
 * @tparam T Value type for the normal classes
 * @param n1 First normal to consider
 * @param n2 Second normal to consider
 *
 * @return Normal with maximum values from `n1` and `n2`.
 * @see max(const T&, const T&)
 */
template <typename T>
Normal3<T> max(const Normal3<T> &n1, const Normal3<T> &n2) {
  return Normal3<T>(max(n1.x, n2.x), max(n1.y, n2.y), max(n1.z, n2.z));
}
/**
 * @ingroup Math Normal
 * @brief Computes the maximum of two `Normal4`s
 *
 * This computes the maximum element wise for the normal.
 *
 * @tparam T Value type for the normal classes
 * @param n1 First normal to consider
 * @param n2 Second normal to consider
 *
 * @return Normal with maximum values from `n1` and `n2`.
 * @see max(const T&, const T&)
 */
template <typename T>
Normal4<T> max(const Normal4<T> &n1, const Normal4<T> &n2) {
  return Normal4<T>(max(n1.x, n2.x), max(n1.y, n2.y), max(n1.z, n2.z),
                    max(n1.w, n2.w));
}

/**
 * @ingroup Math Vector
 * @brief Computes the minimum value in the `Vector2`
 *
 * @tparam T Value type of the vector class
 * @param v Vector to get the minimum component of
 *
 * @return The component of the vector with the minimum value.
 */
template <typename T> T min_component(const Vector2<T> &v) {
  return min(v.x, v.y);
}
/**
 * @ingroup Math Vector
 * @brief Computes the minimum value in the `Vector3`
 *
 * @tparam T Value type of the vector class
 * @param v Vector to get the minimum component of
 *
 * @return The component of the vector with the minimum value.
 */
template <typename T> T min_component(const Vector3<T> &v) {
  return min(v.x, min(v.y, v.z));
}
/**
 * @ingroup Math Vector
 * @brief Computes the minimum value in the `Vector4`
 *
 * @tparam T Value type of the vector class
 * @param v Vector to get the minimum component of
 *
 * @return The component of the vector with the minimum value.
 */
template <typename T> T min_component(const Vector4<T> &v) {
  return min(v.x, min(v.y, min(v.z, v.w)));
}
/**
 * @ingroup Math Point
 * @brief Computes the minimum value in the `Point2`
 *
 * @tparam T Value type of the point class
 * @param p Point to get the minimum component of
 *
 * @return The component of the point with the minimum value.
 */
template <typename T> T min_component(const Point2<T> &p) {
  return min(p.x, p.y);
}
/**
 * @ingroup Math Point
 * @brief Computes the minimum value in the `Point3`
 *
 * @tparam T Value type of the point class
 * @param p Point to get the minimum component of
 *
 * @return The component of the point with the minimum value.
 */
template <typename T> T min_component(const Point3<T> &p) {
  return min(p.x, min(p.y, p.z));
}
/**
 * @ingroup Math Point
 * @brief Computes the minimum value in the `Point4`
 *
 * @tparam T Value type of the point class
 * @param p Point to get the minimum component of
 *
 * @return The component of the point with the minimum value.
 */
template <typename T> T min_component(const Point4<T> &p) {
  return min(p.x, min(p.y, min(p.z, p.w)));
}
/**
 * @ingroup Math Normal
 * @brief Computes the minimum value in the `Normal2`
 *
 * @tparam T Value type of the normal class
 * @param n Normal to get the minimum component of
 *
 * @return The component of the normal with the minimum value.
 */
template <typename T> T min_component(const Normal2<T> &n) {
  return min(n.x, n.y);
}
/**
 * @ingroup Math Normal
 * @brief Computes the minimum value in the `Normal3`
 *
 * @tparam T Value type of the normal class
 * @param n Normal to get the minimum component of
 *
 * @return The component of the normal with the minimum value.
 */
template <typename T> T min_component(const Normal3<T> &n) {
  return min(n.x, min(n.y, n.z));
}
/**
 * @ingroup Math Normal
 * @brief Computes the minimum value in the `Normal4`
 *
 * @tparam T Value type of the normal class
 * @param n Normal to get the minimum component of
 *
 * @return The component of the normal with the minimum value.
 */
template <typename T> T min_component(const Normal4<T> &n) {
  return min(n.x, min(n.y, min(n.z, n.w)));
}

/**
 * @ingroup Math Vector
 * @brief Computes the maximum value in the `Vector2`
 *
 * @tparam T Value type of the vector class
 * @param v Vector to get the maximum component of
 *
 * @return The component of the vector with the maximum value.
 */
template <typename T> T max_component(const Vector2<T> &v) {
  return max(v.x, v.y);
}
/**
 * @ingroup Math Vector
 * @brief Computes the maximum value in the `Vector3`
 *
 * @tparam T Value type of the vector class
 * @param v Vector to get the maximum component of
 *
 * @return The component of the vector with the maximum value.
 */
template <typename T> T max_component(const Vector3<T> &v) {
  return max(v.x, max(v.y, v.z));
}
/**
 * @ingroup Math Vector
 * @brief Computes the maximum value in the `Vector4`
 *
 * @tparam T Value type of the vector class
 * @param v Vector to get the maximum component of
 *
 * @return The component of the vector with the maximum value.
 */
template <typename T> T max_component(const Vector4<T> &v) {
  return max(v.x, max(v.y, max(v.z, v.w)));
}
/**
 * @ingroup Math Point
 * @brief Computes the maximum value in the `Point2`
 *
 * @tparam T Value type of the point class
 * @param p Point to get the maximum component of
 *
 * @return The component of the point with the maximum value.
 */
template <typename T> T max_component(const Point2<T> &p) {
  return max(p.x, p.y);
}
/**
 * @ingroup Math Point
 * @brief Computes the maximum value in the `Point3`
 *
 * @tparam T Value type of the point class
 * @param p Point to get the maximum component of
 *
 * @return The component of the point with the maximum value.
 */
template <typename T> T max_component(const Point3<T> &p) {
  return max(p.x, max(p.y, p.z));
}
/**
 * @ingroup Math Point
 * @brief Computes the maximum value in the `Point4`
 *
 * @tparam T Value type of the point class
 * @param p Point to get the maximum component of
 *
 * @return The component of the point with the maximum value.
 */
template <typename T> T max_component(const Point4<T> &p) {
  return max(p.x, max(p.y, max(p.z, p.w)));
}
/**
 * @ingroup Math Normal
 * @brief Computes the maximum value in the `Normal2`
 *
 * @tparam T Value type of the normal class
 * @param n Normal to get the maximum component of
 *
 * @return The component of the normal with the maximum value.
 */
template <typename T> T max_component(const Normal2<T> &n) {
  return max(n.x, n.y);
}
/**
 * @ingroup Math Normal
 * @brief Computes the maximum value in the `Normal3`
 *
 * @tparam T Value type of the normal class
 * @param n Normal to get the maximum component of
 *
 * @return The component of the normal with the maximum value.
 */
template <typename T> T max_component(const Normal3<T> &n) {
  return max(n.x, max(n.y, n.z));
}
/**
 * @ingroup Math Normal
 * @brief Computes the maximum value in the `Normal4`
 *
 * @tparam T Value type of the normal class
 * @param n Normal to get the maximum component of
 *
 * @return The component of the normal with the maximum value.
 */
template <typename T> T max_component(const Normal4<T> &n) {
  return max(n.x, max(n.y, max(n.z, n.w)));
}

/**
 * @ingroup Math Vector
 * @brief Constructs a new `Vector2` from a permutation
 *
 * This is equivalent to `Vector2<T>(v[x], v[y])`.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to permute
 * @param x The index of the new \f$x\f$ value
 * @param y The index of the new \f$y\f$ value
 *
 * @return Vector `v` after the permutation.
 */
template <typename T>
Vector2<T> permute(const Vector2<T> &v, typename Vector2<T>::size_type x,
                   typename Vector2<T>::size_type y) {
  return Vector2<T>(v[x], v[y]);
}
/**
 * @ingroup Math Vector
 * @brief Constructs a new `Vector3` from a permutation
 *
 * This is equivalent to `Vector3<T>(v[x], v[y], v[z])`.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to permute
 * @param x The index of the new \f$x\f$ value
 * @param y The index of the new \f$y\f$ value
 * @param z The index of the new \f$z\f$ value
 *
 * @return Vector `v` after the permutation.
 */
template <typename T>
Vector3<T> permute(const Vector3<T> &v, typename Vector3<T>::size_type x,
                   typename Vector3<T>::size_type y,
                   typename Vector3<T>::size_type z) {
  return Vector3<T>(v[x], v[y], v[z]);
}
/**
 * @ingroup Math Vector
 * @brief Constructs a new `Vector4` from a permutation
 *
 * This is equivalent to `Vector4<T>(v[x], v[y], v[z], v[w])`.
 *
 * @tparam T Value type of the vector class
 * @param v Vector to permute
 * @param x The index of the new \f$x\f$ value
 * @param y The index of the new \f$y\f$ value
 * @param z The index of the new \f$z\f$ value
 * @param w The index of the new \f$w\f$ value
 *
 * @return Vector `v` after the permutation.
 */
template <typename T>
Vector4<T> permute(const Vector4<T> &v, typename Vector4<T>::size_type x,
                   typename Vector4<T>::size_type y,
                   typename Vector4<T>::size_type z,
                   typename Vector4<T>::size_type w) {
  return Vector4<T>(v[x], v[y], v[z], v[w]);
}
/**
 * @ingroup Math Point
 * @brief Constructs a new `Point2` from a permutation
 *
 * This is equivalent to `Point2<T>(p[x], p[y])`.
 *
 * @tparam T Value type of the point class
 * @param p Point to permute
 * @param x The index of the new \f$x\f$ value
 * @param y The index of the new \f$y\f$ value
 *
 * @return Point `p` after the permutation.
 */
template <typename T>
Point2<T> permute(const Point2<T> &p, typename Point2<T>::size_type x,
                  typename Point2<T>::size_type y) {
  return Point2<T>(p[x], p[y]);
}
/**
 * @ingroup Math Point
 * @brief Constructs a new `Point3` from a permutation
 *
 * This is equivalent to `Point3<T>(p[x], p[y], p[z])`.
 *
 * @tparam T Value type of the point class
 * @param p Point to permute
 * @param x The index of the new \f$x\f$ value
 * @param y The index of the new \f$y\f$ value
 * @param z The index of the new \f$z\f$ value
 *
 * @return Point `p` after the permutation.
 */
template <typename T>
Point3<T> permute(const Point3<T> &p, typename Point3<T>::size_type x,
                  typename Point3<T>::size_type y,
                  typename Point3<T>::size_type z) {
  return Point3<T>(p[x], p[y], p[z]);
}
/**
 * @ingroup Math Point
 * @brief Constructs a new `Point4` from a permutation
 *
 * This is equivalent to `Point4<T>(p[x], p[y], p[z], p[w])`.
 *
 * @tparam T Value type of the point class
 * @param p Point to permute
 * @param x The index of the new \f$x\f$ value
 * @param y The index of the new \f$y\f$ value
 * @param z The index of the new \f$z\f$ value
 * @param w The index of the new \f$w\f$ value
 *
 * @return Point `p` after the permutation.
 */
template <typename T>
Point4<T> permute(const Point4<T> &p, typename Point4<T>::size_type x,
                  typename Point4<T>::size_type y,
                  typename Point4<T>::size_type z,
                  typename Point4<T>::size_type w) {
  return Point4<T>(p[x], p[y], p[z], p[w]);
}
/**
 * @ingroup Math Normal
 * @brief Constructs a new `Normal2` from a permutation
 *
 * This is equivalent to `Normal2<T>(n[x], n[y])`.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to permute
 * @param x The index of the new \f$x\f$ value
 * @param y The index of the new \f$y\f$ value
 *
 * @return Normal `n` after the permutation.
 */
template <typename T>
Normal2<T> permute(const Normal2<T> &n, typename Normal2<T>::size_type x,
                   typename Normal2<T>::size_type y) {
  return Normal2<T>(n[x], n[y]);
}
/**
 * @ingroup Math Normal
 * @brief Constructs a new `Normal3` from a permutation
 *
 * This is equivalent to `Normal3<T>(n[x], n[y], n[z])`.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to permute
 * @param x The index of the new \f$x\f$ value
 * @param y The index of the new \f$y\f$ value
 * @param z The index of the new \f$z\f$ value
 *
 * @return Normal `n` after the permutation.
 */
template <typename T>
Normal3<T> permute(const Normal3<T> &n, typename Normal3<T>::size_type x,
                   typename Normal3<T>::size_type y,
                   typename Normal3<T>::size_type z) {
  return Normal3<T>(n[x], n[y], n[z]);
}
/**
 * @ingroup Math Normal
 * @brief Constructs a new `Normal4` from a permutation
 *
 * This is equivalent to `Normal4<T>(n[x], n[y], n[z], n[w])`.
 *
 * @tparam T Value type of the normal class
 * @param n Normal to permute
 * @param x The index of the new \f$x\f$ value
 * @param y The index of the new \f$y\f$ value
 * @param z The index of the new \f$z\f$ value
 * @param w The index of the new \f$w\f$ value
 *
 * @return Normal `n` after the permutation.
 */
template <typename T>
Normal4<T> permute(const Normal4<T> &n, typename Normal4<T>::size_type x,
                   typename Normal4<T>::size_type y,
                   typename Normal4<T>::size_type z,
                   typename Normal4<T>::size_type w) {
  return Normal4<T>(n[x], n[y], n[z], n[w]);
}

} // namespace specula

#endif // SPECULA_MATH_COMMON_HPP_
