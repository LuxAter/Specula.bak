#ifndef SPECULA_BOUNDS_BOUNDS2_HPP_
#define SPECULA_BOUNDS_BOUNDS2_HPP_

#include "../../global.hpp"

#include "../point/point2.hpp"
#include "../vector/vector2.hpp"

namespace specula {
/**
 * @brief Bounds in 2D
 * @ingroup Bounds
 *
 * This bounds class implements a bounding box in 2D, represented by two
 * `Point2`s.
 *
 * @tparam T Element type of bounding points.
 */
template <typename T> class Bounds2 {
public:
  typedef Point2<T> value_type;
  typedef Point2<T> &reference;
  typedef const Point2<T> &const_reference;
  typedef Point2<T> *pointer;
  typedef const Point2<T> *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  class iterator : public std::forward_iterator_tag {
  public:
    iterator(const Bounds2<T> *b, const Point2<T> &pt) : p(pt), bounds(b) {}
    iterator operator++() {
      advance();
      return *this;
    }
    iterator operator++(int) {
      iterator old = *this;
      advance();
      return old;
    }
    bool operator==(const iterator &it) const {
      return p == it.p && bounds == it.bounds;
    }
    bool operator!=(const iterator &it) const {
      return p != it.p || bounds != it.bounds;
    }
    Point2<T> operator*() const { return p; }

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

  Bounds2()
      : p_min(std::numeric_limits<T>::max()),
        p_max(std::numeric_limits<T>::lowest()) {}
  explicit Bounds2(const Point2<T> &p) : p_min(p), p_max(p) {}
  Bounds2(const Point2<T> &p1, const Point2<T> &p2) {
    p_min = Point2<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
    p_max = Point2<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
  }
  template <typename U> explicit operator Bounds2<U>() const {
    return Bounds2<U>(Point2<U>(p_min), Point2<U>(p_max));
  }
  iterator begin() const { return iterator(this, p_min); }
  iterator end() const {
    Point2<T> p_end(p_min.x, p_min.y);
    if (p_min.x >= p_max.x || p_min.y >= p_max.y)
      p_end = p_min;
    return iterator(this, p_end);
  }
  bool operator==(const Bounds2<T> &b) const {
    return p_min == b.p_min && p_max == b.p_max;
  }
  bool operator!=(const Bounds2<T> &b) const {
    return p_min != b.p_min || p_max != b.p_max;
  }
  Point2<T> corner(size_type i) const {
    if (i < 0 || i >= 4)
      throw std::out_of_range(
          "specula::Bounds2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(8) + ")");
    return Point2<T>(this->at((i & 1)).x, this->at((i & 2) ? 1 : 0).y);
  }
  reference at(size_type i) {
    switch (i) {
    case 0:
      return p_min;
    case 1:
      return p_max;
    default:
      throw std::out_of_range(
          "specula::Bounds2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(2) + ")");
    }
  }
  const_reference at(size_type i) const {
    switch (i) {
    case 0:
      return p_min;
    case 1:
      return p_max;
    default:
      throw std::out_of_range(
          "specula::Bounds2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(2) + ")");
    }
  }
  reference operator[](size_type i) {
    switch (i) {
    case 0:
      return p_min;
    case 1:
      return p_max;
    default:
      throw std::out_of_range(
          "specula::Bounds2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(2) + ")");
    }
  }
  const_reference operator[](size_type i) const {
    switch (i) {
    case 0:
      return p_min;
    case 1:
      return p_max;
    default:
      throw std::out_of_range(
          "specula::Bounds2::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(2) + ")");
    }
  }
  Vector2<T> diagonal() const { return p_max - p_min; }
  T area() const {
    Vector2<T> d = p_min - p_min;
    return d.x * d.y;
  }
  T length() const {
    Vector2<T> d = p_min - p_min;
    return 2 * (d.x + d.y);
  }
  size_type maximum_extent() const {
    Vector2<T> d = p_max - p_min;
    if (d.x > d.y) {
      return 0;
    } else {
      return 1;
    }
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
  std::pair<Point2<T>, Float> BoundingSphere() const {
    Point2<T> center = (p_min + p_max) / 2;
    return std::make_pair(center,
                          inside(center, *this) ? distance(center, p_max) : 0);
  }

  std::string fmt() const { return fmt::format("[{} - {}]", p_min, p_max); }

  Point2<T> p_min, p_max;
};

typedef Bounds2<Float> Bounds2f;
typedef Bounds2<Int> Bounds2i;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Bounds2<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_BOUNDS_BOUNDS2_HPP_
