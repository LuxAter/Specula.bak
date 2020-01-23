#ifndef SPECULA_MATRIX2X2_HPP_
#define SPECULA_MATRIX2X2_HPP_

#include <memory>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

#include "../vector/vector2.hpp"

namespace specula {
template <typename T> class Matrix2x2 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  Matrix2x2() SPECULA_NOEXCEPT {
    T unit = T(1);
    T zero = T();
    data[0][0] = unit;
    data[0][1] = zero;
    data[1][0] = zero;
    data[1][1] = unit;
  }
  Matrix2x2(const T &s) {
    T zero = T();
    data[0][0] = s;
    data[0][1] = zero;
    data[1][0] = zero;
    data[1][1] = s;
  }
  Matrix2x2(const T &m00, const T &m01, const T &m10, const T &m11) {
    data[0][0] = m00;
    data[0][1] = m01;
    data[1][0] = m10;
    data[1][1] = m11;
  }
  Matrix2x2(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    memcpy(data, m.data, 4 * sizeof(T));
  }
  ~Matrix2x2() SPECULA_NOEXCEPT {}

  Matrix2x2 &operator=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    memcpy(data, m.data, 4 * sizeof(T));
    return *this;
  }

  bool operator==(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return data[0][0] == m.data[0][0] && data[0][1] == m.data[0][1] &&
           data[1][0] == m.data[1][0] && data[1][1] == m.data[1][1];
  }
  bool operator!=(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return data[0][0] != m.data[0][0] || data[0][1] != m.data[0][1] ||
           data[1][0] != m.data[1][0] || data[1][1] != m.data[1][1];
  }

  pointer operator[](size_type r) { return data[r]; }
  const_pointer operator[](size_type r) const { return data[r]; }
  pointer at(size_type r) {
    if (r < 0 || r >= 2)
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    return data[r];
  }
  const_pointer at(size_type r) const {
    if (r < 0 || r >= 2)
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    return data[r];
  }
  reference at(size_type r, size_type c) {
    if (r < 0 || r >= 2)
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    else if (c < 0 || c >= 2) {
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __c (which is " +
              std::to_string(c)
          << ") >= this->columns() (which is " +
                 std::to_string(this->columns()) + ")");
    }
    return data[r][c];
  }
  const_reference at(size_type r, size_type c) const {
    if (r < 0 || r >= 2)
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __n (which is " +
              std::to_string(r)
          << ") >= this->rows() (which is " + std::to_string(this->rows()) +
                 ")");
    else if (c < 0 || c >= 2) {
      throw std::out_of_range(
          "specula::Matrix2x2::_M_range_check: __c (which is " +
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
    data[1][0] = zero;
    data[1][1] = zero;
  }

  void swap(Matrix2x2 &m) SPECULA_NOEXCEPT { std::swap(data, m.data); }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 4; }
  SPECULA_CONSTEXPR size_type rows() const SPECULA_NOEXCEPT { return 2; }
  SPECULA_CONSTEXPR size_type columns() const SPECULA_NOEXCEPT { return 2; }

  Matrix2x2 operator+(const T &s) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] + s, data[0][1] + s, data[1][0] + s,
                     data[1][1] + s);
  }
  Matrix2x2 operator+(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] + m.data[0][0], data[0][1] + m.data[0][1],
                     data[1][0] + m.data[1][0], data[1][1] + m.data[1][1]);
  }
  Matrix2x2 &operator+=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] += s;
    data[0][1] += s;
    data[1][0] += s;
    data[1][1] += s;
    return *this;
  }
  Matrix2x2 &operator+=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    data[0][0] += m.data[0][0];
    data[0][1] += m.data[0][1];
    data[1][0] += m.data[1][0];
    data[1][1] += m.data[1][1];
    return *this;
  }
  Matrix2x2 operator-(const T &s) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] - s, data[0][1] - s, data[1][0] - s,
                     data[1][1] - s);
  }
  Matrix2x2 operator-(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] - m.data[0][0], data[0][1] - m.data[0][1],
                     data[1][0] - m.data[1][0], data[1][1] - m.data[1][1]);
  }
  Matrix2x2 &operator-=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] -= s;
    data[0][1] -= s;
    data[1][0] -= s;
    data[1][1] -= s;
    return *this;
  }
  Matrix2x2 &operator-=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    data[0][0] -= m.data[0][0];
    data[0][1] -= m.data[0][1];
    data[1][0] -= m.data[1][0];
    data[1][1] -= m.data[1][1];
    return *this;
  }
  Matrix2x2 operator*(const T &s) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] * s, data[0][1] * s, data[1][0] * s,
                     data[1][1] * s);
  }
  Matrix2x2 operator*(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return Matrix2x2<T>(data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0],
                        data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1],
                        data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0],
                        data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1]);
  }
  Vector2<T> operator*(const Vector2<T> &v) const SPECULA_NOEXCEPT {
    return Vector2<T>(data[0][0] * v.x + data[0][1] * v.y,
                      data[1][0] * v.x + data[1][1] * v.y);
  }
  Matrix2x2 &operator*=(const T &s) SPECULA_NOEXCEPT {
    data[0][0] *= s;
    data[0][1] *= s;
    data[1][0] *= s;
    data[1][1] *= s;
    return *this;
  }
  Matrix2x2 &operator*=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    value_type t0, t1;
    t0 = data[0][0] * m.data[0][0] + data[0][1] * m.data[1][0];
    t1 = data[0][0] * m.data[0][1] + data[0][1] * m.data[1][1];

    data[0][0] = t0;
    data[0][1] = t1;

    t0 = data[1][0] * m.data[0][0] + data[1][1] * m.data[1][0];
    t1 = data[1][0] * m.data[0][1] + data[1][1] * m.data[1][1];

    data[1][0] = t0;
    data[1][1] = t1;

    t0 = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0];
    t1 = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1];

    data[2][0] = t0;
    data[2][1] = t1;

    t0 = data[2][0] * m.data[0][0] + data[2][1] * m.data[1][0];
    t1 = data[2][0] * m.data[0][1] + data[2][1] * m.data[1][1];

    data[2][0] = t0;
    data[2][1] = t1;

    return *this;
  }
  Matrix2x2 operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Matrix2x2(data[0][0] * inv, data[0][1] * inv, data[1][0] * inv,
                     data[1][1] * inv);
  }
  Matrix2x2 operator/(const Matrix2x2 &m) const SPECULA_NOEXCEPT {
    return Matrix2x2(data[0][0] / m.data[0][0], data[0][1] / m.data[0][1],
                     data[1][0] / m.data[1][0], data[1][1] / m.data[1][1]);
  }
  Matrix2x2 &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    data[0][0] *= inv;
    data[0][1] *= inv;
    data[1][0] *= inv;
    data[1][1] *= inv;
    return *this;
  }
  Matrix2x2 &operator/=(const Matrix2x2 &m) SPECULA_NOEXCEPT {
    data[0][0] /= m.data[0][0];
    data[0][1] /= m.data[0][1];
    data[1][0] /= m.data[1][0];
    data[1][1] /= m.data[1][1];
    return *this;
  }

  std::string fmt() const {
    return fmt::format("[[{},{}],[{},{}]]", data[0][0], data[0][1], data[1][0],
                       data[1][1]);
  }

  T data[2][2];
};

typedef Matrix2x2<Float> Matrix2f;
typedef Matrix2x2<Int> Matrix2i;
typedef Matrix2x2<Float> Matrix2x2f;
typedef Matrix2x2<Int> Matrix2x2i;

template <typename T> using Matrix2 = Matrix2x2<T>;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix2x2<T> &m) {
  return out << m.fmt();
}
} // namespace specula

#endif // SPECULA_MATRIX2X2_HPP_
