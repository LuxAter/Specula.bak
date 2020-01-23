#ifndef SPECULA_MATRIX4X4_HPP_
#define SPECULA_MATRIX4X4_HPP_

#include <memory>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

#include "../vector/vector4.hpp"

namespace specula {
template <typename T> class Matrix4x4 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  Matrix4x4() SPECULA_NOEXCEPT {
    T unit = T(1);
    T zero = T();
    data[0][0] = unit;
    data[0][1] = zero;
    data[0][2] = zero;
    data[0][3] = zero;
    data[1][0] = zero;
    data[1][1] = unit;
    data[1][2] = zero;
    data[1][3] = zero;
    data[2][0] = zero;
    data[2][1] = zero;
    data[2][2] = unit;
    data[2][3] = zero;
    data[3][0] = zero;
    data[3][1] = zero;
    data[3][2] = zero;
    data[3][3] = unit;
  }
  Matrix4x4(const T &s) {
    T zero = T();
    data[0][0] = s;
    data[0][1] = zero;
    data[0][2] = zero;
    data[0][3] = zero;
    data[1][0] = zero;
    data[1][1] = s;
    data[1][2] = zero;
    data[1][3] = zero;
    data[2][0] = zero;
    data[2][1] = zero;
    data[2][2] = s;
    data[2][3] = zero;
    data[3][0] = zero;
    data[3][1] = zero;
    data[3][2] = zero;
    data[3][3] = s;
  }
  Matrix4x4(const T &m00, const T &m01, const T &m02, const T &m03,
            const T &m10, const T &m11, const T &m12, const T &m13,
            const T &m20, const T &m21, const T &m22, const T &m23,
            const T &m30, const T &m31, const T &m32, const T &m33) {
    data[0][0] = m00;
    data[0][1] = m01;
    data[0][2] = m02;
    data[0][3] = m03;
    data[1][0] = m10;
    data[1][1] = m11;
    data[1][2] = m12;
    data[1][3] = m13;
    data[2][0] = m20;
    data[2][1] = m21;
    data[2][2] = m22;
    data[2][3] = m23;
    data[3][0] = m30;
    data[3][1] = m31;
    data[3][2] = m32;
    data[3][3] = m33;
  }
  Matrix4x4(const Matrix4x4 &m) SPECULA_NOEXCEPT {
    memcpy(data, m.data, 16 * sizeof(T));
  }
  ~Matrix4x4() SPECULA_NOEXCEPT {}

  Matrix4x4 &operator=(const Matrix4x4 &m) SPECULA_NOEXCEPT {
    memcpy(data, m.data, 16 * sizeof(T));
    return *this;
  }

  bool operator==(const Matrix4x4 &m) const SPECULA_NOEXCEPT {
    return data[0][0] == m.data[0][0] && data[0][1] == m.data[0][1] &&
           data[0][2] == m.data[0][2] && data[0][3] == m.data[0][3] &&
           data[1][0] == m.data[1][0] && data[1][1] == m.data[1][1] &&
           data[1][2] == m.data[1][2] && data[1][3] == m.data[1][3] &&
           data[2][0] == m.data[2][0] && data[2][1] == m.data[2][1] &&
           data[2][2] == m.data[2][2] && data[2][3] == m.data[2][3] &&
           data[3][0] == m.data[3][0] && data[3][1] == m.data[3][1] &&
           data[3][2] == m.data[3][2] && data[3][3] == m.data[3][3];
  }
  bool operator!=(const Matrix4x4 &m) const SPECULA_NOEXCEPT {
    return data[0][0] != m.data[0][0] || data[0][1] != m.data[0][1] ||
           data[0][2] != m.data[0][2] || data[0][3] != m.data[0][3] ||
           data[1][0] != m.data[1][0] || data[1][1] != m.data[1][1] ||
           data[1][2] != m.data[1][2] || data[1][3] != m.data[1][3] ||
           data[2][0] != m.data[2][0] || data[2][1] != m.data[2][1] ||
           data[2][2] != m.data[2][2] || data[2][3] != m.data[2][3] ||
           data[3][0] != m.data[3][0] || data[3][1] != m.data[3][1] ||
           data[3][2] != m.data[3][2] || data[3][3] != m.data[3][3];
  }

  pointer operator[](size_type r) { return data[r]; }
  const_pointer operator[](size_type r) const { return data[r]; }
  pointer at(size_type r) {
    if (r < 0 || r >= 4)
      throw std::out_of_range(
          "specula::Matrix4x4::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    return data[r];
  }
  const_pointer at(size_type r) const {
    if (r < 0 || r >= 4)
      throw std::out_of_range(
          "specula::Matrix4x4::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    return data[r];
  }
  reference at(size_type r, size_type c) {
    if (r < 0 || r >= 4)
      throw std::out_of_range(
          "specula::Matrix4x4::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    else if (c < 0 || c >= 4) {
      throw std::out_of_range(
          "specula::Matrix4x4::_M_range_check: __c (which is " +
              std::to_string(c)
          << ") >= this->columns() (which is " +
                 std::to_string(this->columns()) + ")");
    }
    return data[r][c];
  }
  const_reference at(size_type r, size_type c) const {
    if (r < 0 || r >= 4)
      throw std::out_of_range(
          "specula::Matrix4x4::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    else if (c < 0 || c >= 4) {
      throw std::out_of_range(
          "specula::Matrix4x4::_M_range_check: __c (which is " +
              std::to_string(c)
          << ") >= this->columns() (which is " +
                 std::to_string(this->columns()) + ")");
    }
    return data[r][c];
  }

  void clear() SPECULA_NOEXCEPT {
    T zero = T();
    data[0][0] = zero;
    data[0][1] = zero;
    data[0][2] = zero;
    data[0][3] = zero;
    data[1][0] = zero;
    data[1][1] = zero;
    data[1][2] = zero;
    data[1][3] = zero;
    data[2][0] = zero;
    data[2][1] = zero;
    data[2][2] = zero;
    data[2][3] = zero;
    data[3][0] = zero;
    data[3][1] = zero;
    data[3][2] = zero;
    data[3][3] = zero;
  }

  void swap(Matrix4x4 &m) SPECULA_NOEXCEPT { std::swap(data, m.data); }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 16; }
  SPECULA_CONSTEXPR size_type rows() const SPECULA_NOEXCEPT { return 4; }
  SPECULA_CONSTEXPR size_type columns() const SPECULA_NOEXCEPT { return 4; }

  Matrix4x4 operator+(const T &s) const SPECULA_NOEXCEPT {
    return Matrix4x4(
        data[0][0] + s, data[0][1] + s, data[0][2] + s, data[0][3] + s,
        data[1][0] + s, data[1][1] + s, data[1][2] + s, data[1][3] + s,
        data[2][0] + s, data[2][1] + s, data[2][2] + s, data[2][3] + s,
        data[3][0] + s, data[3][1] + s, data[3][2] + s, data[3][3] + s);
  }
  Matrix4x4 operator+(const Matrix4x4 &m) const SPECULA_NOEXCEPT {
    return Matrix4x4(data[0][0] + m.data[0][0], data[0][1] + m.data[0][1],
                     data[0][2] + m.data[0][2], data[0][3] + m.data[0][3],
                     data[1][0] + m.data[1][0], data[1][1] + m.data[1][1],
                     data[1][2] + m.data[1][2], data[1][3] + m.data[1][3],
                     data[2][0] + m.data[2][0], data[2][1] + m.data[2][1],
                     data[2][2] + m.data[2][2], data[2][3] + m.data[2][3],
                     data[3][0] + m.data[3][0], data[3][1] + m.data[3][1],
                     data[3][2] + m.data[3][2], data[3][3] + m.data[3][3]);
  }
  Matrix4x4 &operator+=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] += s;
    data[0][1] += s;
    data[0][2] += s;
    data[0][3] += s;
    data[1][0] += s;
    data[1][1] += s;
    data[1][2] += s;
    data[1][3] += s;
    data[2][0] += s;
    data[2][1] += s;
    data[2][2] += s;
    data[2][3] += s;
    data[3][0] += s;
    data[3][1] += s;
    data[3][2] += s;
    data[3][3] += s;
    return *this;
  }
  Matrix4x4 &operator+=(const Matrix4x4 &m) SPECULA_NOEXCEPT {
    data[0][0] += m.data[0][0];
    data[0][1] += m.data[0][1];
    data[0][2] += m.data[0][2];
    data[0][3] += m.data[0][3];
    data[1][0] += m.data[1][0];
    data[1][1] += m.data[1][1];
    data[1][2] += m.data[1][2];
    data[1][3] += m.data[1][3];
    data[2][0] += m.data[2][0];
    data[2][1] += m.data[2][1];
    data[2][2] += m.data[2][2];
    data[2][3] += m.data[2][3];
    data[3][0] += m.data[3][0];
    data[3][1] += m.data[3][1];
    data[3][2] += m.data[3][2];
    data[3][3] += m.data[3][3];
    return *this;
  }
  Matrix4x4 operator-(const T &s) const SPECULA_NOEXCEPT {
    return Matrix4x4(
        data[0][0] - s, data[0][1] - s, data[0][2] - s, data[0][3] - s,
        data[1][0] - s, data[1][1] - s, data[1][2] - s, data[1][3] - s,
        data[2][0] - s, data[2][1] - s, data[2][2] - s, data[2][3] - s,
        data[3][0] - s, data[3][1] - s, data[3][2] - s, data[3][3] - s);
  }
  Matrix4x4 operator-(const Matrix4x4 &m) const SPECULA_NOEXCEPT {
    return Matrix4x4(data[0][0] - m.data[0][0], data[0][1] - m.data[0][1],
                     data[0][2] - m.data[0][2], data[0][3] - m.data[0][3],
                     data[1][0] - m.data[1][0], data[1][1] - m.data[1][1],
                     data[1][2] - m.data[1][2], data[1][3] - m.data[1][3],
                     data[2][0] - m.data[2][0], data[2][1] - m.data[2][1],
                     data[2][2] - m.data[2][2], data[2][3] - m.data[2][3],
                     data[3][0] - m.data[3][0], data[3][1] - m.data[3][1],
                     data[3][2] - m.data[3][2], data[3][3] - m.data[3][3]);
  }
  Matrix4x4 &operator-=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] -= s;
    data[0][1] -= s;
    data[0][2] -= s;
    data[0][3] -= s;
    data[1][0] -= s;
    data[1][1] -= s;
    data[1][2] -= s;
    data[1][3] -= s;
    data[2][0] -= s;
    data[2][1] -= s;
    data[2][2] -= s;
    data[2][3] -= s;
    data[3][0] -= s;
    data[3][1] -= s;
    data[3][2] -= s;
    data[3][3] -= s;
    return *this;
  }
  Matrix4x4 &operator-=(const Matrix4x4 &m) SPECULA_NOEXCEPT {
    data[0][0] -= m.data[0][0];
    data[0][1] -= m.data[0][1];
    data[0][2] -= m.data[0][2];
    data[0][3] -= m.data[0][3];
    data[1][0] -= m.data[1][0];
    data[1][1] -= m.data[1][1];
    data[1][2] -= m.data[1][2];
    data[1][3] -= m.data[1][3];
    data[2][0] -= m.data[2][0];
    data[2][1] -= m.data[2][1];
    data[2][2] -= m.data[2][2];
    data[2][3] -= m.data[2][3];
    data[3][0] -= m.data[3][0];
    data[3][1] -= m.data[3][1];
    data[3][2] -= m.data[3][2];
    data[3][3] -= m.data[3][3];
    return *this;
  }
  Matrix4x4 operator*(const T &s) const SPECULA_NOEXCEPT {
    return Matrix4x4(
        data[0][0] * s, data[0][1] * s, data[0][2] * s, data[0][3] * s,
        data[1][0] * s, data[1][1] * s, data[1][2] * s, data[1][3] * s,
        data[2][0] * s, data[2][1] * s, data[2][2] * s, data[2][3] * s,
        data[3][0] * s, data[3][1] * s, data[3][2] * s, data[3][3] * s);
  }
  Matrix4x4 operator*(const Matrix4x4 &m) const SPECULA_NOEXCEPT {
    return Matrix4x4<T>(
        data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] +
            data[0][2] * m.data[2][0] + data[3][0] * m.data[3][0],
        data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] +
            data[0][2] * m.data[2][1] + data[3][0] * m.data[3][1],
        data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] +
            data[0][2] * m.data[2][2] + data[3][0] * m.data[3][2],
        data[0][0] * m.data[0][3] + data[0][1] * m.data[1][3] +
            data[0][2] * m.data[2][3] + data[3][0] * m.data[3][3],
        data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] +
            data[1][2] * m.data[2][0] + data[3][0] * m.data[3][0],
        data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] +
            data[1][2] * m.data[2][1] + data[3][0] * m.data[3][1],
        data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] +
            data[1][2] * m.data[2][2] + data[3][0] * m.data[3][2],
        data[1][0] * m.data[0][3] + data[1][1] * m.data[1][3] +
            data[1][2] * m.data[2][3] + data[3][0] * m.data[3][3],
        data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] +
            data[2][2] * m.data[2][0] + data[3][0] * m.data[3][0],
        data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] +
            data[2][2] * m.data[2][1] + data[3][0] * m.data[3][1],
        data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] +
            data[2][2] * m.data[2][2] + data[3][0] * m.data[3][2],
        data[2][0] * m.data[0][3] + data[2][1] * m.data[1][3] +
            data[2][2] * m.data[2][3] + data[3][0] * m.data[3][3],
        data[3][0] * m.data[0][0] + data[3][1] * m.data[1][0] +
            data[3][2] * m.data[2][0] + data[3][0] * m.data[3][0],
        data[3][0] * m.data[0][1] + data[3][1] * m.data[1][1] +
            data[3][2] * m.data[2][1] + data[3][0] * m.data[3][1],
        data[3][0] * m.data[0][2] + data[3][1] * m.data[1][2] +
            data[3][2] * m.data[2][2] + data[3][0] * m.data[3][2],
        data[3][0] * m.data[0][3] + data[3][1] * m.data[1][3] +
            data[3][2] * m.data[2][3] + data[3][0] * m.data[3][3]);
  }
  Vector4<T> operator*(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z +
                          data[0][3] * v.w,
                      data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z +
                          data[1][3] * v.w,
                      data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z +
                          data[2][3] * v.w,
                      data[3][0] * v.x + data[3][1] * v.y + data[3][2] * v.z +
                          data[3][3] * v.w);
  }
  Matrix4x4 &operator*=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] *= s;
    data[0][1] *= s;
    data[0][2] *= s;
    data[0][3] *= s;
    data[1][0] *= s;
    data[1][1] *= s;
    data[1][2] *= s;
    data[1][3] *= s;
    data[2][0] *= s;
    data[2][1] *= s;
    data[2][2] *= s;
    data[2][3] *= s;
    data[3][0] *= s;
    data[3][1] *= s;
    data[3][2] *= s;
    data[3][3] *= s;
    return *this;
  }
  Matrix4x4 &operator*=(const Matrix4x4 &m) SPECULA_NOEXCEPT {
    value_type t0, t1, t2, t3;
    t0 = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] +
         data[0][2] * m.data[2][0] + data[3][0] * m.data[3][0];
    t1 = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] +
         data[0][2] * m.data[2][1] + data[3][0] * m.data[3][1];
    t2 = data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] +
         data[0][2] * m.data[2][2] + data[3][0] * m.data[3][2];
    t3 = data[0][0] * m.data[0][3] + data[0][1] * m.data[1][3] +
         data[0][2] * m.data[2][3] + data[3][0] * m.data[3][3];

    data[0][0] = t0;
    data[0][1] = t1;
    data[0][2] = t2;
    data[0][3] = t3;

    t0 = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] +
         data[1][2] * m.data[2][0] + data[3][0] * m.data[3][0];
    t1 = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] +
         data[1][2] * m.data[2][1] + data[3][0] * m.data[3][1];
    t2 = data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] +
         data[1][2] * m.data[2][2] + data[3][0] * m.data[3][2];
    t3 = data[1][0] * m.data[0][3] + data[1][1] * m.data[1][3] +
         data[1][2] * m.data[2][3] + data[3][0] * m.data[3][3];

    data[1][0] = t0;
    data[1][1] = t1;
    data[1][2] = t2;
    data[1][3] = t3;

    t0 = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] +
         data[2][2] * m.data[2][0] + data[3][0] * m.data[3][0];
    t1 = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] +
         data[2][2] * m.data[2][1] + data[3][0] * m.data[3][1];
    t2 = data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] +
         data[2][2] * m.data[2][2] + data[3][0] * m.data[3][2];
    t3 = data[2][0] * m.data[0][3] + data[2][1] * m.data[1][3] +
         data[2][2] * m.data[2][3] + data[3][0] * m.data[3][3];

    data[2][0] = t0;
    data[2][1] = t1;
    data[2][2] = t2;
    data[2][3] = t3;

    t0 = data[3][0] * m.data[0][0] + data[3][1] * m.data[1][0] +
         data[3][2] * m.data[2][0] + data[3][0] * m.data[3][0];
    t1 = data[3][0] * m.data[0][1] + data[3][1] * m.data[1][1] +
         data[3][2] * m.data[2][1] + data[3][0] * m.data[3][1];
    t2 = data[3][0] * m.data[0][2] + data[3][1] * m.data[1][2] +
         data[3][2] * m.data[2][2] + data[3][0] * m.data[3][2];
    t3 = data[3][0] * m.data[0][3] + data[3][1] * m.data[1][3] +
         data[3][2] * m.data[2][3] + data[3][0] * m.data[3][3];

    data[3][0] = t0;
    data[3][1] = t1;
    data[3][2] = t2;
    data[3][3] = t3;

    return *this;
  }
  Matrix4x4 operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Matrix4x4(
        data[0][0] * inv, data[0][1] * inv, data[0][2] * inv, data[0][3] * inv,
        data[1][0] * inv, data[1][1] * inv, data[1][2] * inv, data[1][3] * inv,
        data[2][0] * inv, data[2][1] * inv, data[2][2] * inv, data[2][3] * inv,
        data[3][0] * inv, data[3][1] * inv, data[3][2] * inv, data[3][3] * inv);
  }
  Matrix4x4 operator/(const Matrix4x4 &m) const SPECULA_NOEXCEPT {
    return Matrix4x4(data[0][0] / m.data[0][0], data[0][1] / m.data[0][1],
                     data[0][2] / m.data[0][2], data[0][3] / m.data[0][3],
                     data[1][0] / m.data[1][0], data[1][1] / m.data[1][1],
                     data[1][2] / m.data[1][2], data[1][3] / m.data[1][3],
                     data[2][0] / m.data[2][0], data[2][1] / m.data[2][1],
                     data[2][2] / m.data[2][2], data[2][3] / m.data[2][3],
                     data[3][0] / m.data[3][0], data[3][1] / m.data[3][1],
                     data[3][2] / m.data[3][2], data[3][3] / m.data[3][3]);
  }
  Matrix4x4 &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    data[0][0] *= inv;
    data[0][1] *= inv;
    data[0][2] *= inv;
    data[0][3] *= inv;
    data[1][0] *= inv;
    data[1][1] *= inv;
    data[1][2] *= inv;
    data[1][3] *= inv;
    data[2][0] *= inv;
    data[2][1] *= inv;
    data[2][2] *= inv;
    data[2][3] *= inv;
    data[3][0] *= inv;
    data[3][1] *= inv;
    data[3][2] *= inv;
    data[3][3] *= inv;
    return *this;
  }
  Matrix4x4 &operator/=(const Matrix4x4 &m) SPECULA_NOEXCEPT {
    data[0][0] /= m.data[0][0];
    data[0][1] /= m.data[0][1];
    data[0][2] /= m.data[0][2];
    data[0][3] /= m.data[0][3];
    data[1][0] /= m.data[1][0];
    data[1][1] /= m.data[1][1];
    data[1][2] /= m.data[1][2];
    data[1][3] /= m.data[1][3];
    data[2][0] /= m.data[2][0];
    data[2][1] /= m.data[2][1];
    data[2][2] /= m.data[2][2];
    data[2][3] /= m.data[2][3];
    data[3][0] /= m.data[3][0];
    data[3][1] /= m.data[3][1];
    data[3][2] /= m.data[3][2];
    data[3][3] /= m.data[3][3];
    return *this;
  }

  std::string fmt() const {
    return fmt::format(
        "[[{},{},{},{}],[{},{},{},{}],[{},{},{},{}],[{},{},{},{}]]", data[0][0],
        data[0][1], data[0][2], data[0][3], data[1][0], data[1][1], data[1][2],
        data[1][3], data[2][0], data[2][1], data[2][2], data[2][3], data[3][0],
        data[3][1], data[3][2], data[3][3]);
  }

  T data[4][4];
};

typedef Matrix4x4<Float> Matrix4f;
typedef Matrix4x4<Int> Matrix4i;
typedef Matrix4x4<Float> Matrix4x4f;
typedef Matrix4x4<Int> Matrix4x4i;

template <typename T> using Matrix4 = Matrix4x4<T>;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix4x4<T> &m) {
  return out << m.fmt();
}
} // namespace specula

#endif // SPECULA_MATRIX4X4_HPP_
