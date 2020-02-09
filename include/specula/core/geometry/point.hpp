#ifndef SPECULA_CORE_GEOMETRY_POINT_HPP_
#define SPECULA_CORE_GEOMETRY_POINT_HPP_

#include "specula/global.hpp"

namespace specula {
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Point {
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
};

template <typename T, typename> class Point2 : public Point<T> {
public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;

  Point2() : x(0), y(0) {}
  Point2(const T &v) : x(v), y(v) { CHECK(!has_nans()); }
  Point2(const T &x, const T &y) : x(x), y(y) { CHECK(!has_nans()); }
  explicit Point2(const Point3<T> &p) : x(p.x), y(p.y) { CHECK(!has_nans()); }
  template <typename U>
  explicit Point2(const Point2<U> &p)
      : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)) {
    CHECK(!has_nans());
  }
  template <typename U>
  explicit Point2(const Vector2<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {
    CHECK(!has_nans());
  }

  inline bool has_nans() const SPECULA_NOEXCEPT {
    return std::isnan(x) || std::isnan(y);
  }

  Point2<T> operator+(const Vector2<T> &v) const {
    CHECK(!v.has_nans());
    return Point2<T>(x + v.x, y + v.y);
  }
  Point2<T> &operator+=(const Vector2<T> &v) {
    CHECK(!v.has_nans());
    x += v.x;
    y += v.y;
    return *this;
  }
  Point2<T> operator+(const Point2<T> &p) const {
    CHECK(!p.has_nans());
    return Point2<T>(x + p.x, y + p.y);
  }
  Point2<T> &operator+=(const Point2<T> &p) {
    CHECK(!p.has_nans());
    x += p.x;
    y += p.y;
    return *this;
  }
  Vector2<T> operator-(const Point2<T> &p) const {
    CHECK(!p.has_nans());
    return Vector2<T>(x - p.x, y - p.y);
  }
  Point2<T> operator-(const Vector2<T> &v) const {
    CHECK(!v.has_nans());
    return Point2<T>(x - v.x, y - v.y);
  }
  Point2<T> &operator-=(const Vector2<T> &v) {
    CHECK(!v.has_nans());
    x -= v.x;
    y -= v.y;
    return *this;
  }
  template <typename U> Point2<T> operator*(const U &f) const {
    CHECK(!std::isnan(f));
    return Point2<T>(x * f, y * f);
  }
  template <typename U> Point2<T> &operator*=(const U &f) {
    CHECK(!std::isnan(f));
    x *= f;
    y *= f;
    return *this;
  }
  template <typename U> Point2<T> operator/(const U &f) const {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    return Point2<T>(x * inv, y * inv);
  }
  template <typename U> Point2<T> &operator/=(const U &f) {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    return *this;
  }
  Point2<T> operator-() const { return Point2<T>(-x, -y); }

  inline bool operator==(const Point2<T> &v) const {
    return x == v.x && y == v.y;
  }
  inline bool operator!=(const Point2<T> &v) const {
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

  inline std::string fmt() const { return fmt::format("[{}, {}]", x, y); }

  T x, y;
};

template <typename T, typename> class Point3 : public Point<T> {
public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;

  Point3() : x(0), y(0), z(0) {}
  Point3(const T &v) : x(v), y(v), z(v) { CHECK(!has_nans()); }
  Point3(const T &x, const T &y, const T &z) : x(x), y(y), z(z) {
    CHECK(!has_nans());
  }
  template <typename U>
  explicit Point3(const Point3<U> &p)
      : x(static_cast<T>(p.x)), y(static_cast<T>(p.y)), z(static_cast<T>(p.z)) {
    CHECK(!has_nans());
  }
  template <typename U>
  explicit Point3(const Vector3<U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)) {
    CHECK(!has_nans());
  }

  inline bool has_nans() const SPECULA_NOEXCEPT {
    return std::isnan(x) || std::isnan(y) || std::isnan(z);
  }

  Point3<T> operator+(const Vector3<T> &v) const {
    CHECK(!v.has_nans());
    return Point3<T>(x + v.x, y + v.y, z + v.z);
  }
  Point3<T> &operator+=(const Vector3<T> &v) {
    CHECK(!v.has_nans());
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Point3<T> operator+(const Point3<T> &p) const {
    CHECK(!p.has_nans());
    return Point2<T>(x + p.x, y + p.y, z + p.z);
  }
  Point2<T> &operator+=(const Point3<T> &p) {
    CHECK(!p.has_nans());
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
  }
  Vector3<T> operator-(const Point3<T> &p) const {
    CHECK(!p.has_nans());
    return Vector3<T>(x - p.x, y - p.y, z - p.z);
  }
  Point3<T> operator-(const Vector3<T> &v) const {
    CHECK(!v.has_nans());
    return Point3<T>(x - v.x, y - v.y, z - v.z);
  }
  Point3<T> &operator-=(const Vector3<T> &v) {
    CHECK(!v.has_nans());
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  template <typename U> Point3<T> operator*(const U &f) const {
    CHECK(!std::isnan(f));
    return Point3<T>(x * f, y * f, z * f);
  }
  template <typename U> Point3<T> &operator*=(const U &f) {
    CHECK(!std::isnan(f));
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  template <typename U> Point3<T> operator/(const U &f) const {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    return Point3<T>(x * inv, y * inv, z * inv);
  }
  template <typename U> Point3<T> &operator/=(const U &f) {
    CHECK(!std::isnan(f));
    CHECK_NE(f, 0);
    Float inv = Float(1) / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Point3<T> operator-() const { return Point3<T>(-x, -y, -z); }

  inline bool operator==(const Point3<T> &p) const {
    return x == p.x && y == p.y && z == p.z;
  }
  inline bool operator!=(const Point3<T> &p) const {
    return x != p.x || y != p.y || z != p.z;
  }

  reference at(const size_type &i) {
    CHECK(i >= 0 && i <= 3);
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }
  SPECULA_CONSTEXPR const_reference at(const size_type &i) const {
    CHECK(i >= 0 && i <= 3);
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }
  reference operator[](const size_type &i) {
    CHECK(i >= 0 && i <= 3);
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }
  SPECULA_CONSTEXPR const_reference operator[](const size_type &i) const {
    CHECK(i >= 0 && i <= 3);
    if (i == 0)
      return x;
    else if (i == 1)
      return y;
    return z;
  }

  inline std::string fmt() const {
    return fmt::format("[{}, {}, {}]", x, y, z);
  }

  T x, y, z;
};

typedef Point2<Float> Point2f;
typedef Point2<Int> Point2i;
typedef Point3<Float> Point3f;
typedef Point3<Int> Point3i;

template <typename T, typename U>
inline Point2<T> operator*(const U &s, const Point2<T> &p) {
  return p * s;
}
template <typename T, typename U>
inline Point3<T> operator*(const U &s, const Point3<T> &p) {
  return p * s;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Point2<T> &v) {
  return out << v.fmt();
}
template <typename T>
std::ostream &operator<<(std::ostream &out, const Point3<T> &v) {
  return out << v.fmt();
}

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_POINT_HPP_