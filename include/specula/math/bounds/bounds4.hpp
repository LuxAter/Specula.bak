#ifndef SPECULA_BOUNDS_BOUNDS4_HPP_
#define SPECULA_BOUNDS_BOUNDS4_HPP_

#include "../../global.hpp"

#include "../point/point4.hpp"
#include "../vector/vector4.hpp"

namespace specula {
/**
 * @brief Bounds in 4D
 * @ingroup Bounds
 *
 * This bounds class implements a bounding box in 4D, represented by two
 * `Point4`s.
 *
 * @tparam T Element type of bounding points.
 */
template <typename T> class Bounds4 {
public:
  typedef Point4<T> value_type;
  typedef Point4<T> &reference;
  typedef const Point4<T> &const_reference;
  typedef Point4<T> *pointer;
  typedef const Point4<T> *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  class iterator : public std::forward_iterator_tag {
  public:
    iterator(const Bounds4<T> *b, const Point4<T> &pt) : p(pt), bounds(b) {}
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
    Point4<T> operator*() const { return p; }

  private:
    void advance() {
      ++p.x;
      if (p.x == bounds->p_max.x) {
        p.x = bounds->p_min.x;
        ++p.y;
        if (p.y == bounds->p_max.y) {
          p.y = bounds->p_min.y;
          ++p.z;
          if (p.z == bounds->p_max.z) {
            p.z = bounds->p_min.z;
            ++p.w;
          }
        }
      }
    }
    Point4<T> p;
    const Bounds4<T> *bounds;
  };

  Bounds4()
      : p_min(std::numeric_limits<T>::max()),
        p_max(std::numeric_limits<T>::lowest()) {}
  explicit Bounds4(const Point4<T> &p) : p_min(p), p_max(p) {}
  Bounds4(const Point4<T> &p1, const Point4<T> &p2) {
    p_min = Point4<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                      std::min(p1.z, p2.z), std::min(p1.w, p2.w));
    p_max = Point4<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                      std::max(p1.z, p2.z), std::max(p1.w, p2.w));
  }
  template <typename U> explicit operator Bounds4<U>() const {
    return Bounds4<U>(Point4<U>(p_min), Point4<U>(p_max));
  }
  iterator begin() const { return iterator(this, p_min); }
  iterator end() const {
    Point4<T> p_end(p_min.x, p_min.y, p_min.z, p_max.w);
    if (p_min.x >= p_max.x || p_min.y >= p_max.y || p_min.z >= p_max.z ||
        p_min.w > p_max.w)
      p_end = p_min;
    return iterator(this, p_end);
  }
  bool operator==(const Bounds4<T> &b) const {
    return p_min == b.p_min && p_max == b.p_max;
  }
  bool operator!=(const Bounds4<T> &b) const {
    return p_min != b.p_min || p_max != b.p_max;
  }
  Point4<T> corner(size_type i) const {
    if (i < 0 || i >= 16)
      throw std::out_of_range(
          "specula::Bounds4::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(16) + ")");
    return Point4<T>(this->at((i & 1)).x, this->at((i & 2) ? 1 : 0).y,
                     this->at((i & 4) ? 1 : 0).z, this->at((i & 8) ? 1 : 0).z);
  }
  reference at(size_type i) {
    switch (i) {
    case 0:
      return p_min;
    case 1:
      return p_max;
    default:
      throw std::out_of_range(
          "specula::Bounds4::_M_range_check: __n (which is " +
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
          "specula::Bounds4::_M_range_check: __n (which is " +
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
          "specula::Bounds4::_M_range_check: __n (which is " +
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
          "specula::Bounds4::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(2) + ")");
    }
  }
  Vector4<T> diagonal() const { return p_max - p_min; }
  T hypervolume() const {
    Vector4<T> d = p_max - p_min;
    return d.x * d.y * d.z * d.w;
  }
  T volume() const {
    Vector4<T> d = p_min - p_min;
    return 2 * (d.x * d.y * d.z + d.x * d.y * d.w + d.x * d.z * d.w +
                d.y * d.z * d.w);
  }
  T area() const {
    Vector4<T> d = p_min - p_min;
    return 4 * (d.x * d.y + d.x * d.z + d.x * d.w + d.y * d.z + d.y * d.w +
                d.z * d.w);
  }
  T length() const {
    Vector4<T> d = p_min - p_min;
    return 6 * (d.x + d.y + d.z + d.w);
  }
  size_type maximum_extent() const {
    Vector4<T> d = p_max - p_min;
    if (d.x > d.y && d.x > d.z && d.x > d.w) {
      return 0;
    } else if (d.y > d.z && d.y > d.w) {
      return 1;
    } else if (d.z > d.w) {
      return 2;
    } else {
      return 3;
    }
  }
  Point4<T> lerp(const Point4f &t) const {
    return Point4<T>(lerp(p_min.x, p_max.x, t.x), lerp(p_min.y, p_max.y, t.y),
                     lerp(p_min.z, p_max.z, t.z), lerp(p_min.w, p_max.w, t.w));
  }
  Vector4<T> offset(const Point4<T> &p) const {
    Vector4<T> o = p - p_min;
    if (p_max.x > p_min.x)
      o.x /= p_max.x - p_min.x;
    if (p_max.y > p_min.y)
      o.y /= p_max.y - p_min.y;
    if (p_max.z > p_min.z)
      o.z /= p_max.z - p_min.z;
    if (p_max.w > p_min.w)
      o.w /= p_max.w - p_min.w;
    return o;
  }
  std::pair<Point4<T>, Float> BoundingSphere() const {
    Point4<T> center = (p_min + p_max) / 2;
    return std::make_pair(center,
                          inside(center, *this) ? distance(center, p_max) : 0);
  }

  std::string fmt() const { return fmt::format("[{} - {}]", p_min, p_max); }

  Point4<T> p_min, p_max;
};

typedef Bounds4<Float> Bounds4f;
typedef Bounds4<Int> Bounds4i;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Bounds4<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_BOUNDS_BOUNDS4_HPP_
