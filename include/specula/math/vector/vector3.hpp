#ifndef SPECULA_VECTOR_VECTOR3_HPP_
#define SPECULA_VECTOR_VECTOR3_HPP_

#include <cmath>
#include <memory>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

namespace specula {
template <typename T, class A = std::allocator<T>> class Vector3Base {
public:
  typedef A allocator_type;
  typedef typename A::value_type value_type;
  typedef typename A::reference reference;
  typedef typename A::const_reference const_reference;
  typedef typename A::difference_type difference_type;
  typedef typename A::size_type size_type;

  class iterator {
    typedef typename A::difference_type difference_type;
    typedef typename A::value_type value_type;
    typedef typename A::reference reference;
    typedef typename A::pointer pointer;
    typedef std::random_access_iterator_tag iterator_category;

    iterator() SPECULA_NOEXCEPT : i(0), base(nullptr) {}
    iterator(const typename Vector3Base::size_type &i,
             Vector3Base *base) SPECULA_NOEXCEPT : i(i),
                                               base(base) {}
    iterator(const iterator &other) SPECULA_NOEXCEPT : i(other.i),
                                                       base(other.base) {}
    ~iterator() SPECULA_NOEXCEPT {}

    iterator &operator=(const iterator &other) SPECULA_NOEXCEPT {
      i = other.i;
      base = other.base;
      return *this;
    }

    bool operator==(const iterator &it) const SPECULA_NOEXCEPT {
      return i == it.i && base == it.base;
    }
    bool operator!=(const iterator &it) const SPECULA_NOEXCEPT {
      return i != it.i || base != it.base;
    }

    iterator &operator++() SPECULA_NOEXCEPT {
      ++i;
      return *this;
    }
    iterator operator++(int) SPECULA_NOEXCEPT {
      iterator old = *this;
      ++i;
      return old;
    }
    iterator &operator--() SPECULA_NOEXCEPT {
      --i;
      return *this;
    }
    iterator operator--(int) SPECULA_NOEXCEPT {
      iterator old = *this;
      --i;
      return old;
    }

    reference operator*() const { return base->at(i); }
    pointer operator->() const { return *(base->at(i)); }
    typename Vector3Base::size_type i;
    Vector3Base *base;
  };
  class const_iterator {
    typedef typename A::difference_type difference_type;
    typedef typename A::value_type value_type;
    typedef const typename A::reference reference;
    typedef const typename A::pointer pointer;
    typedef std::random_access_iterator_tag iterator_category;

    const_iterator() SPECULA_NOEXCEPT : i(0), base(nullptr) {}
    const_iterator(const typename Vector3Base::size_type &i,
                   const Vector3Base *base) SPECULA_NOEXCEPT : i(i),
                                                           base(base) {}
    const_iterator(const const_iterator &it) SPECULA_NOEXCEPT : i(it.i),
                                                                base(it.base) {}
    const_iterator(const iterator &it) SPECULA_NOEXCEPT : i(it.i),
                                                          base(it.base) {}
    ~const_iterator() SPECULA_NOEXCEPT {}

    const_iterator &operator=(const const_iterator &it) SPECULA_NOEXCEPT {
      i = it.i;
      base = it.base;
      return *this;
    }
    bool operator==(const const_iterator &it) const SPECULA_NOEXCEPT {
      return i == it.i && base == it.base;
    }
    bool operator!=(const const_iterator &it) const SPECULA_NOEXCEPT {
      return i != it.i || base != it.base;
    }

    const_iterator &operator++() SPECULA_NOEXCEPT {
      ++i;
      return *this;
    }
    const_iterator operator++(int) SPECULA_NOEXCEPT {
      const_iterator old = *this;
      ++i;
      return old;
    }
    const_iterator &operator--() SPECULA_NOEXCEPT {
      --i;
      return *this;
    }
    const_iterator operator--(int) SPECULA_NOEXCEPT {
      const_iterator old = *this;
      --i;
      return old;
    }

    reference operator*() const { return base->at(i); }
    pointer operator->() const { return *(base->at(i)); }
    typename Vector3Base::size_type i;
    const Vector3Base *base;
  };
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  Vector3Base() SPECULA_NOEXCEPT : x(), y(), z() {}
  Vector3Base(const T &x, const T &y, const T &z) SPECULA_NOEXCEPT : x(x),
                                                                 y(y),
                                                                 z(z) {}
  Vector3Base(const Vector3Base &v) SPECULA_NOEXCEPT : x(v.x), y(v.y), z(v.z) {}
  ~Vector3Base() SPECULA_NOEXCEPT {}

  Vector3Base &operator=(const Vector3Base &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  bool operator==(const Vector3Base &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y && z == v.z;
  }
  bool operator!=(const Vector3Base &v) const SPECULA_NOEXCEPT {
    return x != v.x || y != v.y || z != v.z;
  }

  iterator begin() SPECULA_NOEXCEPT { return iterator(0, this); }
  const_iterator begin() const SPECULA_NOEXCEPT {
    return const_iterator(0, this);
  }
  const_iterator cbegin() const SPECULA_NOEXCEPT {
    return const_iterator(0, this);
  }
  iterator end() SPECULA_NOEXCEPT { return iterator(3, this); }
  const_iterator end() const SPECULA_NOEXCEPT {
    return const_iterator(3, this);
  }
  const_iterator cend() const SPECULA_NOEXCEPT {
    return const_iterator(3, this);
  }
  reverse_iterator rbegin() SPECULA_NOEXCEPT {
    return reverse_iterator(0, this);
  }
  const_reverse_iterator rbegin() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(0, this);
  }
  const_reverse_iterator crbegin() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(0, this);
  }
  reverse_iterator rend() { return reverse_iterator(3, this); }
  const_reverse_iterator rend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(3, this);
  }
  const_reverse_iterator crend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(3, this);
  }

  reference front() SPECULA_NOEXCEPT { return x; }
  const_reference front() const SPECULA_NOEXCEPT { return x; }
  reference back() SPECULA_NOEXCEPT { return z; }
  const_reference back() const SPECULA_NOEXCEPT { return z; }
  reference operator[](size_type i) {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::out_of_range(
          "specula::Vector3Base::_M_range_check: __n (which is " + std::to_string(i)
          << ") >= this->size() (which is " + std::to_string(this->size()) +
                 ")");
    }
  }
  const_reference operator[](size_type i) const {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::out_of_range(
          "specula::Vector3Base::_M_range_check: __n (which is " + std::to_string(i)
          << ") >= this->size() (which is " + std::to_string(this->size()) +
                 ")");
    }
  }
  reference at(size_type i) {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::out_of_range(
          "specula::Vector3Base::_M_range_check: __n (which is " + std::to_string(i)
          << ") >= this->size() (which is " + std::to_string(this->size()) +
                 ")");
    }
  }
  const_reference at(size_type i) const {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::out_of_range(
          "specula::Vector3Base::_M_range_check: __n (which is " + std::to_string(i)
          << ") >= this->size() (which is " + std::to_string(this->size()) +
                 ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = z = T(); }

  void swap(Vector3Base &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
    std::swap(z, v.z);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 3; }
  SPECULA_CONSTEXPR size_type max_size() const SPECULA_NOEXCEPT { return 3; }
  SPECULA_CONSTEXPR bool empty() const SPECULA_NOEXCEPT { return false; }

  Vector3Base<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Vector3Base<T>(x + s, y + s, z + s);
  }
  Vector3Base<T> operator+(const Vector3Base<T> &v) const SPECULA_NOEXCEPT {
    return Vector3Base<T>(x + v.x, y + v.y, z + v.z);
  }
  Vector3Base<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    z += s;
    return *this;
  }
  Vector3Base<T> &operator+=(const Vector3Base<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  Vector3Base<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Vector3Base<T>(x - s, y - s, z - s);
  }
  Vector3Base<T> operator-(const Vector3Base<T> &v) const SPECULA_NOEXCEPT {
    return Vector3Base<T>(x - v.x, y - v.y, z - v.z);
  }
  Vector3Base<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    z -= s;
    return *this;
  }
  Vector3Base<T> &operator-=(const Vector3Base<T> &v) SPECULA_NOEXCEPT {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }
  Vector3Base<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Vector3Base<T>(x * s, y * s, z * s);
  }
  Vector3Base<T> operator*(const Vector3Base<T> &v) const SPECULA_NOEXCEPT {
    return Vector3Base<T>(x * v.x, y * v.y, z * v.z);
  }
  Vector3Base<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }
  Vector3Base<T> &operator*=(const Vector3Base<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }
  Vector3Base<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Vector3Base<T>(x * inv, y * inv, z * inv);
  }
  Vector3Base<T> operator/(const Vector3Base<T> &v) const SPECULA_NOEXCEPT {
    return Vector3Base<T>(x / v.x, y / v.y, z / v.z);
  }
  Vector3Base<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }
  Vector3Base<T> &operator/=(const Vector3Base<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  Vector3Base<T> operator-() const SPECULA_NOEXCEPT{
    return Vector3Base<T>(-x, -y, -z);
  }

  std::string fmt() const { return fmt::format("<{},{},{}>", x, y, z); }

  T x, y, z;
};

typedef Vector3Base<Float> Vector3Basef;
typedef Vector3Base<Int> Vector3Basei;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector3Base<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_VECTOR_VECTOR3_HPP_
