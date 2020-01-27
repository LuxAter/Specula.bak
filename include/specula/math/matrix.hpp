#ifndef SPECULA_MATRIX_HPP_
#define SPECULA_MATRIX_HPP_

#include "../global.hpp"

#include "matrix/matrix2x2.hpp"
#include "matrix/matrix3x3.hpp"
#include "matrix/matrix4x4.hpp"

/**
 * @defgroup Matrix
 * @ingroup Math
 * @brief Standard `Matrix` classes and operations
 *
 * This module implements standard Matrix classes, and operations to use
 * these classes. Specifically it implements `Matrix2x2<T>`, `Matrix3x3<T>`, and
 * `Matrix4x4<T>`. Other more generalized matricies have been omited from the
 * implementation, as they are unneccessary for the use of the renderer.
 *
 * These matrix implementations are primarily used in the Transformation
 * classes, as the internal data of the transformation.
 *
 */

namespace specula {
template <typename T> T determinant(const Matrix2x2<T> &m) {
  return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
}
template <typename T> T determinant(const Matrix3x3<T> &m) {
  return m.data[0][0] *
             (m.data[1][1] * m.data[2][2] - m.data[1][2] * m.data[2][1]) -
         m.data[0][1] *
             (m.data[1][0] * m.data[2][2] - m.data[1][2] * m.data[2][0]) +
         m.data[0][2] *
             (m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0]);
}
template <typename T> T determinant(const Matrix4x4<T> &m) {
  return m.data[0][0] *
             (m.data[1][1] *
                  (m.data[2][2] * m.data[3][3] - m.data[3][2] * m.data[2][3]) -
              m.data[1][2] *
                  (m.data[2][1] * m.data[3][3] - m.data[3][1] * m.data[2][3]) +
              m.data[1][3] *
                  (m.data[2][1] * m.data[3][2] - m.data[2][2] * m.data[3][1])) -
         m.data[0][1] *
             (m.data[1][0] *
                  (m.data[2][2] * m.data[3][3] - m.data[3][2] * m.data[2][3]) -
              m.data[1][2] *
                  (m.data[2][0] * m.data[3][3] - m.data[3][0] * m.data[2][3]) +
              m.data[1][3] *
                  (m.data[2][0] * m.data[3][2] - m.data[3][0] * m.data[2][2])) +
         m.data[0][2] *
             (m.data[1][0] *
                  (m.data[2][1] * m.data[3][3] - m.data[3][1] * m.data[2][3]) -
              m.data[1][1] *
                  (m.data[2][0] * m.data[3][3] - m.data[3][0] * m.data[2][3]) +
              m.data[1][3] *
                  (m.data[2][0] * m.data[3][1] - m.data[3][0] * m.data[2][1])) -
         m.data[0][3] *
             (m.data[1][0] *
                  (m.data[2][1] * m.data[3][2] - m.data[3][1] * m.data[2][2]) -
              m.data[1][1] *
                  (m.data[2][0] * m.data[3][2] - m.data[3][0] * m.data[2][2]) +
              m.data[1][2] *
                  (m.data[2][0] * m.data[3][1] - m.data[3][0] * m.data[2][1]));
}
template <typename T> Matrix2x2<T> transpose(const Matrix2x2<T> &m) {
  return Matrix2x2<T>(m.data[0][0], m.data[1][0], m.data[0][1], m.data[1][1]);
}
template <typename T> Matrix3x3<T> transpose(const Matrix3x3<T> &m) {
  return Matrix3x3<T>(m.data[0][0], m.data[1][0], m.data[2][0], m.data[0][1],
                      m.data[1][1], m.data[2][1], m.data[0][2], m.data[1][2],
                      m.data[2][2]);
}
template <typename T> Matrix4x4<T> transpose(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(m.data[0][0], m.data[1][0], m.data[2][0], m.data[3][0],
                      m.data[0][1], m.data[1][1], m.data[2][1], m.data[3][1],
                      m.data[0][2], m.data[1][2], m.data[2][2], m.data[3][2],
                      m.data[0][3], m.data[1][3], m.data[2][3], m.data[3][3]);
}
template <typename T> Matrix2x2<T> inverse(const Matrix2x2<T> &m) {
  T one_over_det = static_cast<T>(1) /
                   (m.data[0][0] * m.data[1][1] - m.data[1][0] * m.data[0][1]);
  return Matrix2x2<T>(m[1][1] * one_over_det, -m[0][1] * one_over_det,
                      m[1][0] * one_over_det, m[0][0] * one_over_det);
}
template <typename T> Matrix3x3<T> inverse(const Matrix3x3<T> &m) {
  T invdet = static_cast<T>(1) /
             (m.data[0][0] *
                  (m.data[1][1] * m.data[2][2] - m.data[1][2] * m.data[2][1]) -
              m.data[0][1] *
                  (m.data[1][0] * m.data[2][2] - m.data[1][2] * m.data[2][0]) +
              m.data[0][2] *
                  (m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0]));
  return Matrix3x3<T>(
      (m.data[1][1] * m.data[2][2] - m.data[2][1] * m.data[1][2]) * invdet,
      (m.data[0][2] * m.data[2][1] - m.data[0][1] * m.data[2][2]) * invdet,
      (m.data[0][1] * m.data[1][2] - m.data[0][2] * m.data[1][1]) * invdet,
      (m.data[1][2] * m.data[2][0] - m.data[1][0] * m.data[2][2]) * invdet,
      (m.data[0][0] * m.data[2][2] - m.data[0][2] * m.data[2][0]) * invdet,
      (m.data[1][0] * m.data[0][2] - m.data[0][0] * m.data[1][2]) * invdet,
      (m.data[1][0] * m.data[2][1] - m.data[2][0] * m.data[1][1]) * invdet,
      (m.data[2][0] * m.data[0][1] - m.data[0][0] * m.data[2][1]) * invdet,
      (m.data[0][0] * m.data[1][1] - m.data[1][0] * m.data[0][1]) * invdet);
}
template <typename T> Matrix4x4<T> inverse(const Matrix4x4<T> &m) {
  T A2323 = m.data[2][2] * m.data[3][3] - m.data[2][3] * m.data[3][2];
  T A1323 = m.data[2][1] * m.data[3][3] - m.data[2][3] * m.data[3][1];
  T A1223 = m.data[2][1] * m.data[3][2] - m.data[2][2] * m.data[3][1];
  T A0323 = m.data[2][0] * m.data[3][3] - m.data[2][3] * m.data[3][0];
  T A0223 = m.data[2][0] * m.data[3][2] - m.data[2][2] * m.data[3][0];
  T A0123 = m.data[2][0] * m.data[3][1] - m.data[2][1] * m.data[3][0];
  T A2313 = m.data[1][2] * m.data[3][3] - m.data[1][3] * m.data[3][2];
  T A1313 = m.data[1][1] * m.data[3][3] - m.data[1][3] * m.data[3][1];
  T A1213 = m.data[1][1] * m.data[3][2] - m.data[1][2] * m.data[3][1];
  T A2312 = m.data[1][2] * m.data[2][3] - m.data[1][3] * m.data[2][2];
  T A1312 = m.data[1][1] * m.data[2][3] - m.data[1][3] * m.data[2][1];
  T A1212 = m.data[1][1] * m.data[2][2] - m.data[1][2] * m.data[2][1];
  T A0313 = m.data[1][0] * m.data[3][3] - m.data[1][3] * m.data[3][0];
  T A0213 = m.data[1][0] * m.data[3][2] - m.data[1][2] * m.data[3][0];
  T A0312 = m.data[1][0] * m.data[2][3] - m.data[1][3] * m.data[2][0];
  T A0212 = m.data[1][0] * m.data[2][2] - m.data[1][2] * m.data[2][0];
  T A0113 = m.data[1][0] * m.data[3][1] - m.data[1][1] * m.data[3][0];
  T A0112 = m.data[1][0] * m.data[2][1] - m.data[1][1] * m.data[2][0];

  T det =
      m.data[0][0] *
          (m.data[1][1] * A2323 - m.data[1][2] * A1323 + m.data[1][3] * A1223) -
      m.data[0][1] *
          (m.data[1][0] * A2323 - m.data[1][2] * A0323 + m.data[1][3] * A0223) +
      m.data[0][2] *
          (m.data[1][0] * A1323 - m.data[1][1] * A0323 + m.data[1][3] * A0123) -
      m.data[0][3] *
          (m.data[1][0] * A1223 - m.data[1][1] * A0223 + m.data[1][2] * A0123);
  det = 1 / det;

  return Matrix4x4<T>(
      det *
          (m.data[1][1] * A2323 - m.data[1][2] * A1323 + m.data[1][3] * A1223),
      det *
          -(m.data[0][1] * A2323 - m.data[0][2] * A1323 + m.data[0][3] * A1223),
      det *
          (m.data[0][1] * A2313 - m.data[0][2] * A1313 + m.data[0][3] * A1213),
      det *
          -(m.data[0][1] * A2312 - m.data[0][2] * A1312 + m.data[0][3] * A1212),
      det *
          -(m.data[1][0] * A2323 - m.data[1][2] * A0323 + m.data[1][3] * A0223),
      det *
          (m.data[0][0] * A2323 - m.data[0][2] * A0323 + m.data[0][3] * A0223),
      det *
          -(m.data[0][0] * A2313 - m.data[0][2] * A0313 + m.data[0][3] * A0213),
      det *
          (m.data[0][0] * A2312 - m.data[0][2] * A0312 + m.data[0][3] * A0212),
      det *
          (m.data[1][0] * A1323 - m.data[1][1] * A0323 + m.data[1][3] * A0123),
      det *
          -(m.data[0][0] * A1323 - m.data[0][1] * A0323 + m.data[0][3] * A0123),
      det *
          (m.data[0][0] * A1313 - m.data[0][1] * A0313 + m.data[0][3] * A0113),
      det *
          -(m.data[0][0] * A1312 - m.data[0][1] * A0312 + m.data[0][3] * A0112),
      det *
          -(m.data[1][0] * A1223 - m.data[1][1] * A0223 + m.data[1][2] * A0123),
      det *
          (m.data[0][0] * A1223 - m.data[0][1] * A0223 + m.data[0][2] * A0123),
      det *
          -(m.data[0][0] * A1213 - m.data[0][1] * A0213 + m.data[0][2] * A0113),
      det *
          (m.data[0][0] * A1212 - m.data[0][1] * A0212 + m.data[0][2] * A0112));
}
} // namespace specula

#endif // SPECULA_MATRIX_HPP_
