#ifndef SPECULA_CORE_GEOMETRY_BOUNDS_HPP_
#define SPECULA_CORE_GEOMETRY_BOUNDS_HPP_

#include "specula/global.hpp"
#include <iterator>

#include "point.hpp"
#include "ray.hpp"
#include "vector.hpp"

namespace specula {
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Bounds {
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
};

template <typename T, typename> class Bounds2 : public Bounds<T> {
public:
  class iterator {
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Point2<T> value_type;
    typedef Vector2<T> difference_type;
    typedef Point2<T> *pointer;
    typedef Point2<T> &reference;

    iterator(const Bounds2<T> &b, const Point2<T> &pt) : p(pt), bounds(&b) {}
    iterator(const Bounds2<T> *b, const Point2<T> &pt) : p(pt), bounds(b) {}
    iterator &operator++() {
      advance();
      return *this;
    }
    iterator &operator++(int) {
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

  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;

  Bounds2()
      : p_min(std::numeric_limits<T>::max()),
        p_max(std::numeric_limits<T>::lowest()) {}
  explicit Bounds2(const Point2<T> &p) : p_min(p), p_max(p) {}
  Bounds2(const Point2<T> &p1, const Point2<T> &p2)
      : p_min(std::min(p1.x, p2.x), std::min(p1.y, p2.y)),
        p_max(std::max(p1.x, p2.x), std::max(p1.y, p2.y)) {}
  template <typename U>
  Bounds2(const Bounds2<U> &b) : p_min(b.p_min), p_max(b.p_max) {}

  Vector2<T> diagonal() const SPECULA_NOEXCEPT { return p_max - p_min; }
  T area() const SPECULA_NOEXCEPT {
    Vector2<T> d = p_max - p_min;
    return (d.x * d.y);
  }
  size_type maximum_extent() const SPECULA_NOEXCEPT {
    Vector2<T> d = p_max - p_min;
    if (d.x > d.y)
      return 0;
    return 1;
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
  void bounding_sphere(Point2<T> *c, Float *rad) const {
    *c = (p_min + p_max) / 2;
    *rad = inside(*c, *this) ? distance(*c, p_max) : 0;
  }

  inline bool operator==(const Bounds2<T> &b) const {
    return p_min == b.p_min && p_max == b.p_max;
  }
  inline bool operator!=(const Bounds2<T> &b) const {
    return p_min != b.p_min || p_max != b.p_max;
  }

  Point2<T> &operator[](int i) {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return p_min;
    return p_max;
  }
  SPECULA_CONSTEXPR const Point2<T> &operator[](int i) const {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return p_min;
    return p_max;
  }

  inline iterator begin() const { return iterator(this, p_min); }
  inline iterator end() const {
    Point2<T> p_end(p_min.x, p_max.y);
    if (p_min.x >= p_max.x || p_min.y >= p_max.y)
      p_end = p_min;
    return iterator(this, end);
  }

  inline std::string fmt() const {
    return fmt::format("[{} - {}]", p_min, p_max);
  }

  Point2<T> p_min, p_max;
};

template <typename T, typename> class Bounds3 : public Bounds<T> {
public:
  class iterator {
  public:
    typedef std::forward_iterator_tag iterator_category;
    typedef Point3<T> value_type;
    typedef Vector3<T> difference_type;
    typedef Point3<T> *pointer;
    typedef Point3<T> &reference;

    iterator(const Bounds3<T> &b, const Point3<T> &pt) : p(pt), bounds(&b) {}
    iterator(const Bounds3<T> *b, const Point3<T> &pt) : p(pt), bounds(b) {}
    iterator &operator++() {
      advance();
      return *this;
    }
    iterator &operator++(int) {
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

  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;

  Bounds3()
      : p_min(std::numeric_limits<T>::max()),
        p_max(std::numeric_limits<T>::lowest()) {}
  explicit Bounds3(const Point3<T> &p) : p_min(p), p_max(p) {}
  Bounds3(const Point3<T> &p1, const Point3<T> &p2)
      : p_min(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)),
        p_max(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
              std::max(p1.z, p2.z)) {}
  template <typename U>
  Bounds3(const Bounds3<U> &b) : p_min(b.p_min), p_max(b.p_max) {}

  T area() const SPECULA_NOEXCEPT {
    Vector3<T> d = p_max - p_min;
    return (d.x * d.y * d.z);
  }
  Point3<T> corner(size_type corner) const {
    CHECK(corner >= 0 && corner < 8);
    return Point3<T>(at((corner & 1)).x, at((corner & 2) ? 1 : 0).y,
                     at((corner & 4) ? 1 : 0).z);
  }
  Vector3<T> diagonal() const SPECULA_NOEXCEPT { return p_max - p_min; }
  size_type maximum_extent() const {
    Vector3<T> d = p_max - p_min;
    if (d.x > d.y && d.x > d.z)
      return 0;
    else if (d.y > d.z)
      return 1;
    return 2;
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
  void bounding_sphere(Point3<T> *c, Float *rad) const {
    *c = (p_min + p_max) / 2;
    *rad = inside(*c, *this) ? distance(*c, p_max) : 0;
  }

  inline bool intersect_p(const Ray &ray, Float *hitt0 = nullptr,
                          Float *hitt1 = nullptr) const {
    Float t0 = 0, t1 = ray.t_max;
    for (size_type i = 0; i < 3; ++i) {
      Float inv_ray_dir = 1 / ray.d[i];
      Float t_near = (p_min[i] - ray.o[i]) * inv_ray_dir;
      Float t_far = (p_max[i] - ray.o[i]) * inv_ray_dir;
      if (t_near > t_far)
        std::swap(t_near, t_far);
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
  inline bool intersect_p(const Ray &ray, const Vector3f &inv_dir,
                          const int dir_is_neg[3]) const {
    Float t_min = (at(dir_is_neg[0]).x - ray.o.x) * inv_dir.x;
    Float t_max = (at(1 - dir_is_neg[0]).x - ray.o.x) * inv_dir.x;
    Float ty_min = (at(dir_is_neg[0]).y - ray.o.y) * inv_dir.y;
    Float ty_max = (at(1 - dir_is_neg[0]).y - ray.o.y) * inv_dir.y;

    t_max *= 1 + 2 * gamma(3);
    ty_max *= 1 + 2 * gamma(3);
    if (t_min > ty_max || ty_min > t_max)
      return false;
    if (ty_min > t_min)
      t_min = ty_min;
    if (ty_max < t_max)
      t_max = ty_max;

    Float tz_min = (at(dir_is_neg[0]).z - ray.o.z) * inv_dir.z;
    Float tz_max = (at(1 - dir_is_neg[0]).z - ray.o.z) * inv_dir.z;

    tz_max *= 1 + 2 * gamma(3);
    if (t_min > tz_max || tz_min > t_max)
      return false;
    if (tz_min > t_min)
      t_min = tz_min;
    if (tz_max < t_max)
      t_max = tz_max;
    return (t_min < ray.t_max) && (t_max > 0);
  }

  inline bool operator==(const Bounds3<T> &b) const {
    return p_min == b.p_min && p_max == b.p_max;
  }
  inline bool operator!=(const Bounds3<T> &b) const {
    return p_min != b.p_min || p_max != b.p_max;
  }

  Point3<T> &at(size_type i) {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return p_min;
    return p_max;
  }
  SPECULA_CONSTEXPR const Point3<T> &at(size_type i) const {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return p_min;
    return p_max;
  }
  Point3<T> &operator[](size_type i) {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return p_min;
    return p_max;
  }
  SPECULA_CONSTEXPR const Point3<T> &operator[](size_type i) const {
    CHECK(i >= 0 && i <= 1);
    if (i == 0)
      return p_min;
    return p_max;
  }

  inline iterator begin() const { return iterator(this, p_min); }
  inline iterator end() const {
    Point3<T> p_end(p_min.x, p_min.y, p_max.z);
    if (p_min.x >= p_max.x || p_min.y >= p_max.y || p_min.z >= p_max.z)
      p_end = p_min;
    return iterator(this, end);
  }

  inline std::string fmt() const {
    return fmt::format("[{} - {}]", p_min, p_max);
  }

  Point3<T> p_min, p_max;
};

typedef Bounds2<Float> Bounds2f;
typedef Bounds3<Float> Bounds3f;

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_BOUNDS_HPP_
