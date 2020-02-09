#ifndef SPECULA_CORE_GEOMETRY_NORMAL_HPP_
#define SPECULA_CORE_GEOMETRY_NORMAL_HPP_

#include "specula/global.hpp"

namespace specula {
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Normal {
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
};

template <typename T, typename> class Normal2 : public Normal<T> {
public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;

  Normal2() : x(0), y(0) {}
  Normal2(const T &x, const T &y) : x(x), y(y) { CHECK(!has_nans()); }
  explicit Normal2(const Vector2<T> &v) : x(v.x), y(v.y) { CHECK(!has_nans()); }

  inline bool has_nans() const SPECULA_NOEXCEPT {
    return std::isnan(x) || std::isnan(y);
  }

  Normal2<T> operator+(const Normal2<T> &v) const {
    CHECK(!v.has_nans());
    return Normal2<T>(x + v.x, y + v.y);
  }
  Normal2<T> &operator+=(const Normal2<T> &v) {
    CHECK(!v.has_nans());
    x += v.x;
    y += v.y;
    return *this;
  }
  Normal2<T> operator-(const Normal2<T> &v) const {
    CHECK(!v.has_nans());
    return Normal2<T>(x - v.x, y - v.y);
  }
  Normal2<T> &operator-=(const Normal2<T> &v) {
    CHECK(!v.has_nans());
    x -= v.x;
    y -= v.y;
    return *this;
  }
  template <typename U> Normal2<T> operator*(const U &f) const {
    CHECK(!std::isnan(f));
    return Normal2<T>(x * f, y * f);
  }
  template <typename U> Normal2<T> &operator*=(const U &f) {
    CHECK(!std::isnan(f));
    x *= f;
    y *= f;
    return *this;
  }
  template <typename U> Normal2<T> operator/(const U &f) const {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    return Normal2<T>(x * inv, y * inv);
  }
  template <typename U> Normal2<T> &operator/=(const U &f) {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    return *this;
  }
  Normal2<T> operator-() const { return Normal2<T>(-x, -y); }

  inline bool operator==(const Normal2<T> &v) const {
    return x == v.x && y == v.y;
  }
  inline bool operator!=(const Normal2<T> &v) const {
    return x != v.x || y != v.y;
  }

  reference at(const size_type &i) {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return x;
    return y;
  }
  SPECULA_CONSTEXPR const_reference at(const size_type &i) const {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return x;
    return y;
  }
  reference operator[](const size_type &i) {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return x;
    return y;
  }
  SPECULA_CONSTEXPR const_reference operator[](const size_type &i) const {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return x;
    return y;
  }

  inline value_type length_squared() const SPECULA_NOEXCEPT {
    return x * x + y * y;
  }
  inline value_type length() const SPECULA_NOEXCEPT {
    return std::sqrt(x * x + y * y);
  }

  inline std::string fmt() const { return fmt::format("[{}, {}]", x, y); }

  T x, y;
};

template <typename T, typename> class Normal3 : public Normal<T> {
public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;

  Normal3() : x(0), y(0), z(0) {}
  Normal3(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {
    CHECK(!has_nans());
  }
  explicit Normal3(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {
    CHECK(!has_nans());
  }

  inline bool has_nans() const SPECULA_NOEXCEPT {
    return std::isnan(x) || std::isnan(y) || std::isnan(z);
  }

  Normal3<T> operator+(const Normal3<T> &v) const {
    CHECK(!v.has_nans());
    return Normal3<T>(x + v.x, y + v.y, z + v.z);
  }
  Normal3<T> &operator+=(const Normal3<T> &v) {
    CHECK(!v.has_nans());
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Normal3<T> operator-(const Normal3<T> &v) const {
    CHECK(!v.has_nans());
    return Normal3<T>(x - v.x, y - v.y, z - v.z);
  }
  Normal3<T> &operator-=(const Normal3<T> &v) {
    CHECK(!v.has_nans());
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  template <typename U> Normal3<T> operator*(const U &f) const {
    CHECK(!std::isnan(f));
    return Normal3<T>(x * f, y * f, z * f);
  }
  template <typename U> Normal3<T> &operator*=(const U &f) {
    CHECK(!std::isnan(f));
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  template <typename U> Normal3<T> operator/(const U &f) const {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    return Normal3<T>(x * inv, y * inv, z * inv);
  }
  template <typename U> Normal3<T> &operator/=(const U &f) {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Normal3<T> operator-() const { return Normal3<T>(-x, -y, -z); }

  inline bool operator==(const Normal3<T> &v) const {
    return x == v.x && y == v.y && z == v.z;
  }
  inline bool operator!=(const Normal3<T> &v) const {
    return x != v.x || y != v.y || z != v.z;
  }

  reference at(const size_type &i) {
    CHECK(i >= 0 && i <= 2);
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }
  SPECULA_CONSTEXPR const_reference at(const size_type &i) const {
    CHECK(i >= 0 && i <= 2);
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }
  reference operator[](const size_type &i) {
    CHECK(i >= 0 && i <= 2);
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }
  SPECULA_CONSTEXPR const_reference operator[](const size_type &i) const {
    CHECK(i >= 0 && i <= 2);
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }

  inline value_type length_squared() const SPECULA_NOEXCEPT {
    return x * x + y * y + z * z;
  }
  inline value_type length() const SPECULA_NOEXCEPT {
    return std::sqrt(x * x + y * y + z * z);
  }

  inline std::string fmt() const {
    return fmt::format("[{}, {}, {}]", x, y, z);
  }

  T x, y, z;
};

typedef Normal2<Float> Normal2f;
typedef Normal2<Int> Normal2i;
typedef Normal3<Float> Normal3f;
typedef Normal3<Int> Normal3i;

template <typename T, typename U>
inline Normal2<T> operator*(const U &s, const Normal2<T> &n) {
  return n * s;
}
template <typename T, typename U>
inline Normal3<T> operator*(const U &s, const Normal3<T> &n) {
  return n * s;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Normal2<T> &n) {
  return out << n.fmt();
}
template <typename T>
std::ostream &operator<<(std::ostream &out, const Normal3<T> &n) {
  return out << n.fmt();
}

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_NORMAL_HPP_