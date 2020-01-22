#ifndef SPECULA_VECTOR4_HPP_
#define SPECULA_VECTOR4_HPP_

#include <iostream>
#include <iterator>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

namespace specula {
template <typename T> class Vector4 {
public:
  typedef T value_type;
  typedef T &reference;
  typedef const T &const_reference;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  class iterator {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    typedef std::random_access_iterator_tag iterator_category;

    iterator() SPECULA_NOEXCEPT : i(0), base(nullptr) {}
    iterator(const typename Vector4::size_type &i,
             Vector4 *base) SPECULA_NOEXCEPT : i(i),
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
    typename Vector4::size_type i;
    Vector4 *base;
  };
  class const_iterator {
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T &reference;
    typedef const T *pointer;
    typedef std::random_access_iterator_tag iterator_category;

    const_iterator() SPECULA_NOEXCEPT : i(0), base(nullptr) {}
    const_iterator(const typename Vector4::size_type &i,
                   const Vector4 *base) SPECULA_NOEXCEPT : i(i),
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
    typename Vector4::size_type i;
    const Vector4 *base;
  };
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  Vector4() SPECULA_NOEXCEPT : x(), y(), z(), w() {}
  Vector4(const T &x, const T &y, const T &z, const T &w) SPECULA_NOEXCEPT
      : x(x),
        y(y),
        z(z),
        w(w) {}
  Vector4(const Vector4 &v) SPECULA_NOEXCEPT : x(v.x), y(v.y), z(v.z), w(v.w) {}
  ~Vector4() SPECULA_NOEXCEPT {}

  Vector4 &operator=(const Vector4 &v) SPECULA_NOEXCEPT {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
  }

  bool operator==(const Vector4 &v) const SPECULA_NOEXCEPT {
    return x == v.x && y == v.y && z == v.z && w == v.w;
  }
  bool operator!=(const Vector4 &v) const SPECULA_NOEXCEPT {
    return x != v.x || y != v.y || z != v.z || w != v.w;
  }

  iterator begin() SPECULA_NOEXCEPT { return iterator(0, this); }
  const_iterator begin() const SPECULA_NOEXCEPT {
    return const_iterator(0, this);
  }
  const_iterator cbegin() const SPECULA_NOEXCEPT {
    return const_iterator(0, this);
  }
  iterator end() SPECULA_NOEXCEPT { return iterator(4, this); }
  const_iterator end() const SPECULA_NOEXCEPT {
    return const_iterator(4, this);
  }
  const_iterator cend() const SPECULA_NOEXCEPT {
    return const_iterator(4, this);
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
  reverse_iterator rend() { return reverse_iterator(4, this); }
  const_reverse_iterator rend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(4, this);
  }
  const_reverse_iterator crend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(4, this);
  }

  reference front() SPECULA_NOEXCEPT { return x; }
  const_reference front() const SPECULA_NOEXCEPT { return x; }
  reference back() SPECULA_NOEXCEPT { return w; }
  const_reference back() const SPECULA_NOEXCEPT { return w; }
  reference operator[](size_type i) {
    switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      throw std::out_of_range(
          "specula::Vector4::_M_range_check: __n (which is " + std::to_string(i)
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
    case 3:
      return w;
    default:
      throw std::out_of_range(
          "specula::Vector4::_M_range_check: __n (which is " + std::to_string(i)
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
    case 3:
      return w;
    default:
      throw std::out_of_range(
          "specula::Vector4::_M_range_check: __n (which is " + std::to_string(i)
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
    case 3:
      return w;
    default:
      throw std::out_of_range(
          "specula::Vector4::_M_range_check: __n (which is " + std::to_string(i)
          << ") >= this->size() (which is " + std::to_string(this->size()) +
                 ")");
    }
  }

  void clear() SPECULA_NOEXCEPT { x = y = z = w = T(); }

  void swap(Vector4 &v) SPECULA_NOEXCEPT {
    std::swap(x, v.x);
    std::swap(y, v.y);
    std::swap(z, v.z);
    std::swap(w, v.w);
  }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return 4; }
  SPECULA_CONSTEXPR size_type max_size() const SPECULA_NOEXCEPT { return 4; }
  SPECULA_CONSTEXPR bool empty() const SPECULA_NOEXCEPT { return false; }

  Vector4<T> operator+(const T &s) const SPECULA_NOEXCEPT {
    return Vector4<T>(x + s, y + s, z + s, w + s);
  }
  Vector4<T> operator+(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
  }
  Vector4<T> &operator+=(const T &s) SPECULA_NOEXCEPT {
    x += s;
    y += s;
    z += s;
    w += s;
    return *this;
  }
  Vector4<T> &operator+=(const Vector4<T> &v) SPECULA_NOEXCEPT {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }
  Vector4<T> operator-(const T &s) const SPECULA_NOEXCEPT {
    return Vector4<T>(x - s, y - s, z - s, w - s);
  }
  Vector4<T> operator-(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
  }
  Vector4<T> &operator-=(const T &s) SPECULA_NOEXCEPT {
    x -= s;
    y -= s;
    z -= s;
    w -= s;
    return *this;
  }
  Vector4<T> &operator-=(const Vector4<T> &v) SPECULA_NOEXCEPT {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }
  Vector4<T> operator*(const T &s) const SPECULA_NOEXCEPT {
    return Vector4<T>(x * s, y * s, z * s, w * s);
  }
  Vector4<T> operator*(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
  }
  Vector4<T> &operator*=(const T &s) SPECULA_NOEXCEPT {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }
  Vector4<T> &operator*=(const Vector4<T> &v) SPECULA_NOEXCEPT {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }
  Vector4<T> operator/(const T &s) const SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    return Vector4<T>(x * inv, y * inv, z * inv, w * inv);
  }
  Vector4<T> operator/(const Vector4<T> &v) const SPECULA_NOEXCEPT {
    return Vector4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
  }
  Vector4<T> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
    return *this;
  }
  Vector4<T> &operator/=(const Vector4<T> &v) SPECULA_NOEXCEPT {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
  }

  std::string fmt() const { return fmt::format("<{},{},{},{}>", x, y, z, w); }

  T x, y, z, w;
};

typedef Vector4<Float> Vector4f;
typedef Vector4<Int> Vector4i;

template <typename T>
std::ostream &operator<<(std::ostream &out, const Vector4<T> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_VECTOR4_HPP_
