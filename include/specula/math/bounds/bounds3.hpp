#ifndef SPECULA_BOUNDS_BOUNDS3_HPP_
#define SPECULA_BOUNDS_BOUNDS3_HPP_

#include "../../global.hpp"

#include "../point/point3.hpp"
#include "../ray.hpp"
#include "../vector/vector3.hpp"

namespace specula {
template <typename T> class Bounds3 {
public:
  typedef Point3<T> value_type;
  typedef Point3<T> &reference;
  typedef const Point3<T> &const_reference;
  typedef Point3<T> *pointer;
  typedef const Point3<T> *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  class iterator : public std::forward_iterator_tag {
  public:
    iterator(const Bounds3<T> *b, const Point3<T> &pt) : p(pt), bounds(b) {}
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

  Bounds3()
      : p_min(std::numeric_limits<T>::max()),
        p_max(std::numeric_limits<T>::lowest()) {}
  explicit Bounds3(const Point3<T> &p) : p_min(p), p_max(p) {}
  Bounds3(const Point3<T> &p1, const Point3<T> &p2) {
    p_min = Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                      std::min(p1.z, p2.z));
    p_max = Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                      std::max(p1.z, p2.z));
  }
  template <typename U> explicit operator Bounds3<U>() const {
    return Bounds3<U>(Point3<U>(p_min), Point3<U>(p_max));
  }
  iterator begin() const { return iterator(this, p_min); }
  iterator end() const {
    Point3<T> p_end(p_min.x, p_min.y, p_min.z);
    if (p_min.x >= p_max.x || p_min.y >= p_max.y || p_min.z >= p_max.z)
      p_end = p_min;
    return iterator(this, p_end);
  }
  bool operator==(const Bounds3<T> &b) const {
    return p_min == b.p_min && p_max == b.p_max;
  }
  bool operator!=(const Bounds3<T> &b) const {
    return p_min != b.p_min || p_max != b.p_max;
  }
  Point3<T> corner(size_type i) const {
    if (i < 0 || i >= 8)
      throw std::out_of_range(
          "specula::Bounds3::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(8) + ")");
    return Point3<T>(this->at((i & 1)).x, this->at((i & 2) ? 1 : 0).y,
                     this->at((i & 4) ? 1 : 0).z);
  }
  reference at(size_type i) {
    switch (i) {
    case 0:
      return p_min;
    case 1:
      return p_max;
    default:
      throw std::out_of_range(
          "specula::Bounds3::_M_range_check: __n (which is " +
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
          "specula::Bounds3::_M_range_check: __n (which is " +
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
          "specula::Bounds3::_M_range_check: __n (which is " +
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
          "specula::Bounds3::_M_range_check: __n (which is " +
          std::to_string(i) + ") >= this->size() (which is " +
          std::to_string(2) + ")");
    }
  }
  Vector3<T> diagonal() const { return p_max - p_min; }
  T volume() const {
    Vector3<T> d = p_min - p_min;
    return d.x * d.y * d.z;
  }
  T area() const {
    Vector3<T> d = p_min - p_min;
    return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
  }
  T length() const {
    Vector3<T> d = p_min - p_min;
    return 4 * (d.x + d.y + d.z + d.w);
  }
  size_type maximum_extent() const {
    Vector3<T> d = p_max - p_min;
    if (d.x > d.y && d.x > d.z) {
      return 0;
    } else if (d.y > d.z) {
      return 1;
    } else {
      return 2;
    }
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
  std::pair<Point3<T>, Float> BoundingSphere() const {
    Point3<T> center = (p_min + p_max) / 2;
    return std::make_pair(center,
                          inside(center, *this) ? distance(center, p_max) : 0);
  }

  inline bool IntersectP(const Ray &ray, Float *hitt0 = nullptr,
                         Float *hitt1 = nullptr) const {
    Float t0 = 0, t1 = ray.t_max;
    for (size_type i = 0; i < 3; ++i) {
      Float inv_ray_dir = 1 / ray.d[i];
      Float t_near = (p_min[i] - ray.o[i]) * inv_ray_dir;
      Float t_far = (p_max[i] - ray.o[i]) * inv_ray_dir;
      if (t_near > t_far)
        std::swap(t_near, t_far);
      // TODO: Determine what this gamma function is
      t_far *= 1 + 2 * gamma(3);
      t0 = t_near > t0 ? t_near : t0;
      t1 = t_far < t1 ? t_far : t1;
      if (t0 > t1)
        return false;
    }
    if (hitt0)
      *hitt0 = t0;
    if (hitt1)
      *hitt1 = t1;
    return true;
  }
  inline bool IntersectP(const Ray &ray, const Vector3f &&inv_dir,
                         const Int dir_is_neg[3]) const {
    Float tx_min = (at(dir_is_neg[0]).x - ray.o.x) * inv_dir.x;
    Float tx_max = (at(1 - dir_is_neg[0]).x - ray.o.x) * inv_dir.x;
    Float ty_min = (at(dir_is_neg[1]).y - ray.o.y) * inv_dir.y;
    Float ty_max = (at(1 - dir_is_neg[1]).y - ray.o.y) * inv_dir.y;

    tx_max *= 1 + 2 * gamma(3);
    ty_max *= 1 + 2 * gamma(3);
    if (tx_min > ty_max || ty_min > tx_max)
      return false;
    if (ty_min > tx_min)
      tx_min = ty_min;
    if (ty_max < tx_max)
      tx_max = ty_max;
    Float tz_min = (at(dir_is_neg[2]).z - ray.o.z) * inv_dir.z;
    Float tz_max = (at(1 - dir_is_neg[2]).z - ray.o.z) * inv_dir.z;

    tz_max *= 1 + 2 * gamma(3);
    if (tx_min > tz_max || tz_min > tx_max)
      return false;
    if (tz_min > tx_min)
      tx_min = tz_min;
    if (tz_max < tx_max)
      tx_max = tz_max;
    return (tx_min < ray.t_max) && (tx_max > 0);
  }

  std::string fmt() const { return fmt::format("[{} - {}]", p_min, p_max); }

  Point3<T> p_min, p_max;
};

typedef Bounds3<Float> Bounds3f;
typedef Bounds3<Int> Bounds3i;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Bounds3<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_BOUNDS_BOUNDS3_HPP_
