#ifndef SPECULA_CORE_GEOMETRY_VECTOR_HPP_
#define SPECULA_CORE_GEOMETRY_VECTOR_HPP_

#include "specula/global.hpp"

namespace specula {

template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Vector {
public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
};

template <typename T, typename> class Vector2 : public Vector<T> {
public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;

  Vector2() : x(0), y(0) {}
  Vector2(T v) : x(v), y(v) { CHECK(!has_nans()); }
  Vector2(T x, T y) : x(x), y(y) { CHECK(!has_nans()); }
  explicit Vector2(const Point2<T> &p) : x(p.x), y(p.y) { CHECK(!has_nans()); }
  explicit Vector2(const Point3<T> &p) : x(p.x), y(p.y) { CHECK(!has_nans()); }
  explicit Vector2(const Normal2<T> &n) : x(n.x), y(n.y) { CHECK(!has_nans()); }
  explicit Vector2(const Normal3<T> &n) : x(n.x), y(n.y) { CHECK(!has_nans()); }
  template <typename U>
  explicit Vector2(const Vector2<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {
    CHECK(!has_nans());
  }

  inline bool has_nans() const SPECULA_NOEXCEPT {
    return std::isnan(x) || std::isnan(y);
  }

  Vector2<T> operator+(const Vector2<T> &v) const {
    CHECK(!v.has_nans());
    return Vector2<T>(x + v.x, y + v.y);
  }
  Vector2<T> &operator+=(const Vector2<T> &v) {
    CHECK(!v.has_nans());
    x += v.x;
    y += v.y;
    return *this;
  }
  Vector2<T> operator-(const Vector2<T> &v) const {
    CHECK(!v.has_nans());
    return Vector2<T>(x - v.x, y - v.y);
  }
  Vector2<T> &operator-=(const Vector2<T> &v) {
    CHECK(!v.has_nans());
    x -= v.x;
    y -= v.y;
    return *this;
  }
  template <typename U> Vector2<T> operator*(const U &f) const {
    CHECK(!std::isnan(f));
    return Vector2<T>(x * f, y * f);
  }
  template <typename U> Vector2<T> &operator*=(const U &f) {
    CHECK(!std::isnan(f));
    x *= f;
    y *= f;
    return *this;
  }
  template <typename U> Vector2<T> operator/(const U &f) const {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    return Vector2<T>(x * inv, y * inv);
  }
  template <typename U> Vector2<T> &operator/=(const U &f) {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    return *this;
  }
  Vector2<T> operator-() const { return Vector2<T>(-x, -y); }

  inline bool operator==(const Vector2<T> &v) const {
    return x == v.x && y == v.y;
  }
  inline bool operator!=(const Vector2<T> &v) const {
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

template <typename T, typename> class Vector3 : public Vector<T> {
public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;

  Vector3() : x(0), y(0), z(0) {}
  Vector3(T v) : x(v), y(v), z(v) { CHECK(!has_nans()); }
  Vector3(T x, T y, T z) : x(x), y(y), z(z) { CHECK(!has_nans()); }
  explicit Vector3(const Point3<T> &p) : x(p.x), y(p.y), z(p.z) {
    CHECK(!has_nans());
  }
  explicit Vector3(const Normal3<T> &n) : x(n.x), y(n.y), z(n.z) {
    CHECK(!has_nans());
  }
  template <typename U>
  explicit Vector3(const Vector3<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) {
    CHECK(!has_nans());
  }

  inline bool has_nans() const SPECULA_NOEXCEPT {
    return std::isnan(x) || std::isnan(y) || std::isnan(z);
  }

  Vector3<T> operator+(const Vector3<T> &v) const {
    CHECK(!v.has_nans());
    return Vector3<T>(x + v.x, y + v.y, z + v.z);
  }
  Vector3<T> &operator+=(const Vector3<T> &v) {
    CHECK(!v.has_nans());
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vector3<T> operator-(const Vector3<T> &v) const {
    CHECK(!v.has_nans());
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
  }
  Vector3<T> &operator-=(const Vector3<T> &v) {
    CHECK(!v.has_nans());
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  template <typename U> Vector3<T> operator*(const U &f) const {
    CHECK(!std::isnan(f));
    return Vector3<T>(x * f, y * f, z * f);
  }
  template <typename U> Vector3<T> &operator*=(const U &f) {
    CHECK(!std::isnan(f));
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  template <typename U> Vector3<T> operator/(const U &f) const {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    return Vector3<T>(x * inv, y * inv, z * inv);
  }
  template <typename U> Vector3<T> &operator/=(const U &f) {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Vector3<T> operator-() const { return Vector3<T>(-x, -y, -z); }

  inline bool operator==(const Vector3<T> &v) const {
    return x == v.x && y == v.y && z == v.z;
  }
  inline bool operator!=(const Vector3<T> &v) const {
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

typedef Vector2<Float> Vector2f;
typedef Vector2<Int> Vector2i;
typedef Vector3<Float> Vector3f;
typedef Vector3<Int> Vector3i;

template <typename T, typename U>
inline Vector2<T> operator*(const U &s, const Vector2<T> &v) {
  return v * s;
}
template <typename T, typename U>
inline Vector3<T> operator*(const U &s, const Vector3<T> &v) {
  return v * s;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector2<T> &v) {
  return out << v.fmt();
}
template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector3<T> &v) {
  return out << v.fmt();
}

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_VECTOR_HPP_
