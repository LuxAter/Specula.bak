#ifndef SPECULA_MATRIX3X3_HPP_
#define SPECULA_MATRIX3X3_HPP_

#include <memory>
#include <stdexcept>

#include "../../global.hpp"

#include "../vector/vector3.hpp"

namespace specula {
/**
 * @brief \f$3\times 3\f$ Matrix
 * @ingroup Matrix
 *
 * This matrix class implements a \f$3\times 3\f$ square matrix. The elements
 * are stored in row major order, so they are stored in the following format:
 * \f[
 * \begin{pmatrix}
 * m_{00} & m_{01} & m_{02}\\
 * m_{10} & m_{11} & m_{12}\\
 * m_{20} & m_{21} & m_{22}
 * \end{pmatrix}
 * \f]
 *
 * @tparam T Element type for matrix
 */
template <typename T> class Matrix3x3 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  Matrix3x3() SPECULA_NOEXCEPT {
    T unit = T(1);
    T zero = T();
    data[0][0] = unit;
    data[0][1] = zero;
    data[0][2] = zero;
    data[1][0] = zero;
    data[1][1] = unit;
    data[1][2] = zero;
    data[2][0] = zero;
    data[2][1] = zero;
    data[2][2] = unit;
  }
  Matrix3x3(const T &s) {
    T zero = T();
    data[0][0] = s;
    data[0][1] = zero;
    data[0][2] = zero;
    data[1][0] = zero;
    data[1][1] = s;
    data[1][2] = zero;
    data[2][0] = zero;
    data[2][1] = zero;
    data[2][2] = s;
  }
  Matrix3x3(const T &m00, const T &m01, const T &m02, const T &m10,
            const T &m11, const T &m12, const T &m20, const T &m21,
            const T &m22) {
    data[0][0] = m00;
    data[0][1] = m01;
    data[0][2] = m02;
    data[1][0] = m10;
    data[1][1] = m11;
    data[1][2] = m12;
    data[2][0] = m20;
    data[2][1] = m21;
    data[2][2] = m22;
  }
  Matrix3x3(const Matrix3x3 &m) SPECULA_NOEXCEPT {
    memcpy(data, m.data, 9 * sizeof(T));
  }
  ~Matrix3x3() SPECULA_NOEXCEPT {}

  Matrix3x3 &operator=(const Matrix3x3 &m) SPECULA_NOEXCEPT {
    memcpy(data, m.data, 9 * sizeof(T));
    return *this;
  }

  bool operator==(const Matrix3x3 &m) const SPECULA_NOEXCEPT {
    return data[0][0] == m.data[0][0] && data[0][1] == m.data[0][1] &&
           data[0][2] == m.data[0][2] && data[1][0] == m.data[1][0] &&
           data[1][1] == m.data[1][1] && data[1][2] == m.data[1][2] &&
           data[2][0] == m.data[2][0] && data[2][1] == m.data[2][1] &&
           data[2][2] == m.data[2][2];
  }
  bool operator!=(const Matrix3x3 &m) const SPECULA_NOEXCEPT {
    return data[0][0] != m.data[0][0] || data[0][1] != m.data[0][1] ||
           data[0][2] != m.data[0][2] || data[1][0] != m.data[1][0] ||
           data[1][1] != m.data[1][1] || data[1][2] != m.data[1][2] ||
           data[2][0] != m.data[2][0] || data[2][1] != m.data[2][1] ||
           data[2][2] != m.data[2][2];
  }

  pointer operator[](size_type r) { return data[r]; }
  const_pointer operator[](size_type r) const { return data[r]; }
  pointer at(size_type r) {
    if (r < 0 || r >= 3)
      throw std::out_of_range(
          "specula::Matrix3x3::_M_range_check: __n (which is " +
          std::to_string(r) + ") >= this->rows() (which is " +
          std::to_string(this->rows()) + ")");
    return data[r];
  }
  const_pointer at(size_type r) const {
    if (r < 0 || r >= 3)
      throw std::out_of_range(
          "specula::Matrix3x3::_M_range_check: __n (which is " +
          std::to_string(r) + ") >= this->rows() (which is " +
          std::to_string(this->rows()) + ")");
    return data[r];
  }
  reference at(size_type r, size_type c) {
    if (r < 0 || r >= 3)
      throw std::out_of_range(
          "specula::Matrix3x3::_M_range_check: __n (which is " +
          std::to_string(r) + ") >= this->rows() (which is " +
          std::to_string(this->rows()) + ")");
    else if (c < 0 || c >= 3) {
      throw std::out_of_range(
          "specula::Matrix3x3::_M_range_check: __c (which is " +
          std::to_string(c) + ") >= this->columns() (which is " +
          std::to_string(this->columns()) + ")");
    }
    return data[r][c];
  }
  const_reference at(size_type r, size_type c) const {
    if (r < 0 || r >= 3)
      throw std::out_of_range(
          "specula::Matrix3x3::_M_range_check: __n (which is " +
          std::to_string(r) + ") >= this->rows() (which is " +
          std::to_string(this->rows()) + ")");
    else if (c < 0 || c >= 3) {
      throw std::out_of_range(
          "specula::Matrix3x3::_M_range_check: __c (which is " +
          std::to_string(c) + ") >= this->columns() (which is " +
          std::to_string(this->columns()) + ")");
    }
    return data[r][c];
  }

  void clear() SPECULA_NOEXCEPT {
    T zero = T();
    data[0][0] = zero;
    data[0][1] = zero;
    data[0][2] = zero;
    data[1][0] = zero;
    data[1][1] = zero;
    data[1][2] = zero;
    data[2][0] = zero;
    data[2][1] = zero;
    data[2][2] = zero;
  }

  void swap(Matrix3x3 &m) SPECULA_NOEXCEPT { std::swap(data, m.data); }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 9; }
  SPECULA_CONSTEXPR size_type rows() const SPECULA_NOEXCEPT { return 3; }
  SPECULA_CONSTEXPR size_type columns() const SPECULA_NOEXCEPT { return 3; }

  Matrix3x3 operator+(const T &s) const SPECULA_NOEXCEPT {
    return Matrix3x3(data[0][0] + s, data[0][1] + s, data[0][2] + s,
                     data[1][0] + s, data[1][1] + s, data[1][2] + s,
                     data[2][0] + s, data[2][1] + s, data[2][2] + s);
  }
  Matrix3x3 operator+(const Matrix3x3 &m) const SPECULA_NOEXCEPT {
    return Matrix3x3(data[0][0] + m.data[0][0], data[0][1] + m.data[0][1],
                     data[0][2] + m.data[0][2], data[1][0] + m.data[1][0],
                     data[1][1] + m.data[1][1], data[1][2] + m.data[1][2],
                     data[2][0] + m.data[2][0], data[2][1] + m.data[2][1],
                     data[2][2] + m.data[2][2]);
  }
  Matrix3x3 &operator+=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] += s;
    data[0][1] += s;
    data[0][2] += s;
    data[1][0] += s;
    data[1][1] += s;
    data[1][2] += s;
    data[2][0] += s;
    data[2][1] += s;
    data[2][2] += s;
    return *this;
  }
  Matrix3x3 &operator+=(const Matrix3x3 &m) SPECULA_NOEXCEPT {
    data[0][0] += m.data[0][0];
    data[0][1] += m.data[0][1];
    data[0][2] += m.data[0][2];
    data[1][0] += m.data[1][0];
    data[1][1] += m.data[1][1];
    data[1][2] += m.data[1][2];
    data[2][0] += m.data[2][0];
    data[2][1] += m.data[2][1];
    data[2][2] += m.data[2][2];
    return *this;
  }
  Matrix3x3 operator-(const T &s) const SPECULA_NOEXCEPT {
    return Matrix3x3(data[0][0] - s, data[0][1] - s, data[0][2] - s,
                     data[1][0] - s, data[1][1] - s, data[1][2] - s,
                     data[2][0] - s, data[2][1] - s, data[2][2] - s);
  }
  Matrix3x3 operator-(const Matrix3x3 &m) const SPECULA_NOEXCEPT {
    return Matrix3x3(data[0][0] - m.data[0][0], data[0][1] - m.data[0][1],
                     data[0][2] - m.data[0][2], data[1][0] - m.data[1][0],
                     data[1][1] - m.data[1][1], data[1][2] - m.data[1][2],
                     data[2][0] - m.data[2][0], data[2][1] - m.data[2][1],
                     data[2][2] - m.data[2][2]);
  }
  Matrix3x3 &operator-=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] -= s;
    data[0][1] -= s;
    data[0][2] -= s;
    data[1][0] -= s;
    data[1][1] -= s;
    data[1][2] -= s;
    data[2][0] -= s;
    data[2][1] -= s;
    data[2][2] -= s;
    return *this;
  }
  Matrix3x3 &operator-=(const Matrix3x3 &m) SPECULA_NOEXCEPT {
    data[0][0] -= m.data[0][0];
    data[0][1] -= m.data[0][1];
    data[0][2] -= m.data[0][2];
    data[1][0] -= m.data[1][0];
    data[1][1] -= m.data[1][1];
    data[1][2] -= m.data[1][2];
    data[2][0] -= m.data[2][0];
    data[2][1] -= m.data[2][1];
    data[2][2] -= m.data[2][2];
    return *this;
  }
  Matrix3x3 operator*(const T &s) const SPECULA_NOEXCEPT {
    return Matrix3x3(data[0][0] * s, data[0][1] * s, data[0][2] * s,
                     data[1][0] * s, data[1][1] * s, data[1][2] * s,
                     data[2][0] * s, data[2][1] * s, data[2][2] * s);
  }
  Matrix3x3 operator*(const Matrix3x3 &m) const SPECULA_NOEXCEPT {
    return Matrix3x3<T>(data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] +
                            data[0][2] * m.data[2][0],
                        data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] +
                            data[0][2] * m.data[2][1],
                        data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] +
                            data[0][2] * m.data[2][2],
                        data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] +
                            data[1][2] * m.data[2][0],
                        data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] +
                            data[1][2] * m.data[2][1],
                        data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] +
                            data[1][2] * m.data[2][2],
                        data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] +
                            data[2][2] * m.data[2][0],
                        data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] +
                            data[2][2] * m.data[2][1],
                        data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] +
                            data[2][2] * m.data[2][2]);
  }
  Vector3<T> operator*(const Vector3<T> &v) const SPECULA_NOEXCEPT {
    return Vector3<T>(data[0][0] * v.x + data[0][1] * v.y + data[0][2] * v.z,
                      data[1][0] * v.x + data[1][1] * v.y + data[1][2] * v.z,
                      data[2][0] * v.x + data[2][1] * v.y + data[2][2] * v.z);
  }
  Matrix3x3 &operator*=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] *= s;
    data[0][1] *= s;
    data[0][2] *= s;
    data[1][0] *= s;
    data[1][1] *= s;
    data[1][2] *= s;
    data[2][0] *= s;
    data[2][1] *= s;
    data[2][2] *= s;
    return *this;
  }
  Matrix3x3 &operator*=(const Matrix3x3 &m) SPECULA_NOEXCEPT {
    value_type t0, t1, t2, t3;
    t0 = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0] +
         data[0][2] * m.data[2][0];
    t1 = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1] +
         data[0][2] * m.data[2][1];
    t2 = data[0][0] * m.data[0][2] + data[0][1] * m.data[1][2] +
         data[0][2] * m.data[2][2];

    data[0][0] = t0;
    data[0][1] = t1;
    data[0][2] = t2;

    t0 = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0] +
         data[1][2] * m.data[2][0];
    t1 = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1] +
         data[1][2] * m.data[2][1];
    t2 = data[1][0] * m.data[0][2] + data[1][1] * m.data[1][2] +
         data[1][2] * m.data[2][2];

    data[1][0] = t0;
    data[1][1] = t1;
    data[1][2] = t2;

    t0 = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0] +
         data[2][2] * m.data[2][0];
    t1 = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1] +
         data[2][2] * m.data[2][1];
    t2 = data[2][0] * m.data[0][2] + data[2][1] * m.data[1][2] +
         data[2][2] * m.data[2][2];

    data[2][0] = t0;
    data[2][1] = t1;
    data[2][2] = t2;

    t0 = data[3][0] * m.data[0][0] + data[3][1] * m.data[1][0] +
         data[3][2] * m.data[2][0];
    t1 = data[3][0] * m.data[0][1] + data[3][1] * m.data[1][1] +
         data[3][2] * m.data[2][1];
    t2 = data[3][0] * m.data[0][2] + data[3][1] * m.data[1][2] +
         data[3][2] * m.data[2][2];

    data[3][0] = t0;
    data[3][1] = t1;
    data[3][2] = t2;

    return *this;
  }
  Matrix3x3 operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Matrix3x3(data[0][0] * inv, data[0][1] * inv, data[0][2] * inv,
                     data[1][0] * inv, data[1][1] * inv, data[1][2] * inv,
                     data[2][0] * inv, data[2][1] * inv, data[2][2] * inv);
  }
  Matrix3x3 operator/(const Matrix3x3 &m) const SPECULA_NOEXCEPT {
    return Matrix3x3(data[0][0] / m.data[0][0], data[0][1] / m.data[0][1],
                     data[0][2] / m.data[0][2], data[1][0] / m.data[1][0],
                     data[1][1] / m.data[1][1], data[1][2] / m.data[1][2],
                     data[2][0] / m.data[2][0], data[2][1] / m.data[2][1],
                     data[2][2] / m.data[2][2]);
  }
  Matrix3x3 &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    data[0][0] *= inv;
    data[0][1] *= inv;
    data[0][2] *= inv;
    data[1][0] *= inv;
    data[1][1] *= inv;
    data[1][2] *= inv;
    data[2][0] *= inv;
    data[2][1] *= inv;
    data[2][2] *= inv;
    return *this;
  }
  Matrix3x3 &operator/=(const Matrix3x3 &m) SPECULA_NOEXCEPT {
    data[0][0] /= m.data[0][0];
    data[0][1] /= m.data[0][1];
    data[0][2] /= m.data[0][2];
    data[1][0] /= m.data[1][0];
    data[1][1] /= m.data[1][1];
    data[1][2] /= m.data[1][2];
    data[2][0] /= m.data[2][0];
    data[2][1] /= m.data[2][1];
    data[2][2] /= m.data[2][2];
    return *this;
  }

  std::string fmt() const {
    return fmt::format("[[{},{},{}],[{},{},{}],[{},{},{}]]", data[0][0],
                       data[0][1], data[0][2], data[1][0], data[1][1],
                       data[1][2], data[2][0], data[2][1], data[2][2]);
  }

  T data[3][3];
};

typedef Matrix3x3<Float> Matrix3f;
typedef Matrix3x3<Int> Matrix3i;
typedef Matrix3x3<Float> Matrix3x3f;
typedef Matrix3x3<Int> Matrix3x3i;

template <typename T> using Matrix3 = Matrix3x3<T>;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix3x3<T> &m) {
  return out << m.fmt();
}
} // namespace specula

#endif // SPECULA_MATRIX3X3_HPP_
