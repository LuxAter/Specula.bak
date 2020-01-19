#ifndef SPECULA_BOUNDS3_HPP_
#define SPECULA_BOUNDS3_HPP_

#include <limits>

#include "../preprocessor.hpp"

#include "point3.hpp"
#include "vector3.hpp"

#include "common.hpp"
#include "geometric.hpp"

namespace specula {
template <typename T> class Bounds3 {
public:
  class Iterator : public std::forward_iterator_tag {
  public:
    Iterator(const Bounds3<T> *b, const Point3<T> &pt) : p(pt), bounds(b) {}
    Iterator operator++() {
      this->advance();
      return *this;
    }
    Iterator operator++(int) {
      Iterator old = *this;
      advance();
      return old;
    }
    bool operator==(const Iterator &bi) const {
      return p == bi.p && bounds == bi.bounds;
    }
    bool operator!=(const Iterator &bi) const {
      return p != bi.p || bounds != bi.bounds;
    }
    Point3<T> operator*() const { return p; }

  private:
    void advance() {
      ++p.x;
      if (p.x == bounds->p_max.x) {
        p.x = bounds->p_min.x;
        ++p.y;
        if (p.y == bounds->p_max.y) {
          p.y = bounds->p_min.y;
          ++p.z;
        }
      }
    }
    Point3<T> p;
    const Bounds3<T> *bounds;
  };

  typedef T value_type;
  typedef std::size_t size_type;

  Bounds3() {
    T min_num = std::numeric_limits<T>::lowest();
    T max_num = std::numeric_limits<T>::max();
    p_min = Point3<T>(max_num, max_num, max_num);
    p_max = Point3<T>(min_num, min_num, min_num);
  }
  Bounds3(const Point3<T> &p) : p_min(p), p_max(p) {}
  Bounds3(const Point3<T> &p1, const Point3<T> &p2)
      : p_min(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)),
        p_max(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
              std::max(p1.z, p2.z)) {}

  Point3<T> corner(const size_type i) const {
    return Point3<T>(this->at((i & 1)).x, this->at((i & 2) ? 1 : 0).y,
                     this->at((i & 4) ? 1 : 0).z);
  }
  Vector3<T> diagonal() const { return p_max - p_min; }
  T surface_area() const {
    Vector3<T> d = this->diagonal();
    return T(2) * (d.x * d.y + d.x * d.z + d.y * d.z);
  }
  T volume() const {
    Vector3<T> d = this->diagonal();
    return d.x * d.y * d.z;
  }
  Point3<T> lerp(const Point3f &t) const {
    return Point3<T>(lerp(p_min.x, p_max.x, t.x), lerp(p_min.y, p_max.y, t.y),
                     lerp(p_min.z, p_max.z, t.z));
  }
  Vector3<T> offset(const Point3<T> &p) const {
    Vector3<T> o = p - p_min;
    if (p_max.x > p_min.x)
      o.x /= p_max.x - p_min.x;
    if (p_max.y > p_min.y)
      o.y /= p_max.y - p_min.y;
    if (p_max.z > p_min.z)
      o.z /= p_max.z - p_min.z;
    return o;
  }

  std::pair<Point3<T>, Float> bounding_sphere() const {
    Point3<T> center = (p_min + p_max) / 2;
    return std::make_pair<Point3<T>, Float>(
        center, inside(center, *this) ? distance(center, p_max) : 0);
  }

  size_type maximum_extent() const {
    Vector3<T> d = this->diagonal();
    if (d.x > d.y && d.x > d.z)
      return 0;
    else if (d.y > d.z)
      return 1;
    else
      return 2;
  }

  inline Iterator begin() const { return Iterator(this, p_min); }
  inline Iterator end() const {
    Point3<T> p_end(p_min.x, p_min.y, p_max.z);
    if (p_min.x >= p_max.x || p_min.y >= p_max.y || p_min.z >= p_max.z)
      p_end = p_min;
    return Iterator(this, p_end);
  }

  Point3<T> &at(const size_type i) {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    switch (i) {
    default:
    case 0:
      return p_min;
    case 1:
      return p_max;
    }
  }
  const Point3<T> &at(const size_type i) const {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    switch (i) {
    default:
    case 0:
      return p_min;
    case 1:
      return p_max;
    }
  }

  Point3<T> &operator[](const size_type i) {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    switch (i) {
    default:
    case 0:
      return p_min;
    case 1:
      return p_max;
    }
  }
  const Point3<T> &operator[](const size_type i) const {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    switch (i) {
    default:
    case 0:
      return p_min;
    case 1:
      return p_max;
    }
  }
  bool operator==(const Bounds3<T> &b) const {
    return b.p_min == p_min && b.p_max == p_max;
  }
  bool operator!=(const Bounds3<T> &b) const {
    return b.p_min != p_min || b.p_max != p_max;
  }

  Point3<T> p_min, p_max;
};

typedef Bounds3<Float> Bounds3f;
typedef Bounds3<Int> Bounds3i;

} // namespace specula

#endif // SPECULA_BOUNDS3_HPP_