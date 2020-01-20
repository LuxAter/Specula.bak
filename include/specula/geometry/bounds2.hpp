#ifndef SPECULA_BOUNDS2_HPP_
#define SPECULA_BOUNDS2_HPP_

#include <limits>

#include "../preprocessor.hpp"

#include "point2.hpp"
#include "vector2.hpp"

#include "common.hpp"
#include "geometric.hpp"

namespace specula {
template <typename T> class Bounds2 {
public:
  class Iterator : public std::forward_iterator_tag {
  public:
    Iterator(const Bounds2<T> *b, const Point2<T> &pt) : p(pt), bounds(b) {}
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
      }
    }
    Point2<T> p;
    const Bounds2<T> *bounds;
  };

  typedef T value_type;
  typedef std::size_t size_type;

  Bounds2() {
    T min_num = std::numeric_limits<T>::lowest();
    T max_num = std::numeric_limits<T>::max();
    p_min = Point2<T>(max_num, max_num);
    p_max = Point2<T>(min_num, min_num);
  }
  Bounds2(const Point2<T> &p) : p_min(p), p_max(p) {}
  Bounds2(const Point2<T> &p1, const Point2<T> &p2)
      : p_min(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
        p_max(std::max(p1.x, p2.x), std::max(p1.y, p2.y)) {}

  Point3<T> corner(const size_type i) const {
    return Point2<T>(this->at((i & 1)).x, this->at((i & 2) ? 1 : 0).y);
  }
  Vector2<T> diagonal() const { return p_max - p_min; }
  T area() const {
    Vector2<T> d = this->diagonal();
    return d.x * d.y;
  }
  Point2<T> lerp(const Point2f &t) const {
    return Point2<T>(lerp(p_min.x, p_max.x, t.x), lerp(p_min.y, p_max.y, t.y));
  }
  Vector2<T> offset(const Point2<T> &p) const {
    Vector2<T> o = p - p_min;
    if (p_max.x > p_min.x)
      o.x /= p_max.x - p_min.x;
    if (p_max.y > p_min.y)
      o.y /= p_max.y - p_min.y;
    return o;
  }

  std::pair<Point2<T>, Float> bounding_sphere() const {
    Point2<T> center = (p_min + p_max) / 2;
    return std::make_pair<Point2<T>, Float>(
        center, inside(center, *this) ? distance(center, p_max) : 0);
  }

  size_type maximum_extent() const {
    Vector2<T> d = this->diagonal();
    if (d.x > d.y)
      return 0;
    else
      return 2;
  }

  inline Iterator begin() const { return Iterator(this, p_min); }
  inline Iterator end() const {
    Point2<T> p_end(p_min.x, p_min.y);
    if (p_min.x >= p_max.x || p_min.y >= p_max.y)
      p_end = p_min;
    return Iterator(this, p_end);
  }

  Point2<T> &at(const size_type i) {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    switch (i) {
    default:
    case 0:
      return p_min;
    case 1:
      return p_max;
    }
  }
  const Point2<T> &at(const size_type i) const {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    switch (i) {
    default:
    case 0:
      return p_min;
    case 1:
      return p_max;
    }
  }

  Point2<T> &operator[](const size_type i) {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    switch (i) {
    default:
    case 0:
      return p_min;
    case 1:
      return p_max;
    }
  }
  const Point2<T> &operator[](const size_type i) const {
    SPECULA_ASSERT(i >= 0 && i <= 1);
    switch (i) {
    default:
    case 0:
      return p_min;
    case 1:
      return p_max;
    }
  }
  bool operator==(const Bounds2<T> &b) const {
    return b.p_min == p_min && b.p_max == p_max;
  }
  bool operator!=(const Bounds2<T> &b) const {
    return b.p_min != p_min || b.p_max != p_max;
  }

  Point2<T> p_min, p_max;
};

typedef Bounds2<Float> Bounds3f;
typedef Bounds2<Int> Bounds3i;

} // namespace specula

#endif // SPECULA_BOUNDS2_HPP_