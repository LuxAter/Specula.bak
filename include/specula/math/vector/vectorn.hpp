#ifndef SPECULA_VECTORN_HPP_
#define SPECULA_VECTORN_HPP_

#include <cmath>
#include <memory>
#include <stdexcept>

#include "../../compiler.hpp"
#include "../../fmt.hpp"
#include "../../types.hpp"

namespace specula {
template <typename T, std::size_t N, class A = std::allocator<T>>
class VectorN {
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
    iterator(const typename VectorN::size_type &i,
             VectorN *base) SPECULA_NOEXCEPT : i(i),
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
    typename VectorN::size_type i;
    VectorN *base;
  };
  class const_iterator {
    typedef typename A::difference_type difference_type;
    typedef typename A::value_type value_type;
    typedef const typename A::reference reference;
    typedef const typename A::pointer pointer;
    typedef std::random_access_iterator_tag iterator_category;

    const_iterator() SPECULA_NOEXCEPT : i(0), base(nullptr) {}
    const_iterator(const typename VectorN::size_type &i,
                   const VectorN *base) SPECULA_NOEXCEPT : i(i),
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
    typename VectorN::size_type i;
    const VectorN *base;
  };
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  VectorN() SPECULA_NOEXCEPT { std::fill(data, data + sizeof(data), T()); }
  template <typename... ARGS> VectorN(const ARGS &... args) SPECULA_NOEXCEPT {
    initialize<0>(args...);
  }
  VectorN(const VectorN &v) SPECULA_NOEXCEPT {
    memcpy(data, v.data, sizeof(data));
  }
  ~VectorN() SPECULA_NOEXCEPT {}

  VectorN &operator=(const VectorN &v) SPECULA_NOEXCEPT {
    memcpy(data, v.data, sizeof(data));
    return *this;
  }

  bool operator==(const VectorN &v) const SPECULA_NOEXCEPT {
    for (const size_type i = 0; i < this->size(); ++i) {
      if (data[i] != v.data[i])
        return false;
    }
    return true;
  }
  bool operator!=(const VectorN &v) const SPECULA_NOEXCEPT {
    for (const size_type i = 0; i < this->size(); ++i) {
      if (data[i] != v.data[i])
        return true;
    }
    return false;
  }

  iterator begin() SPECULA_NOEXCEPT { return iterator(0, this); }
  const_iterator begin() const SPECULA_NOEXCEPT {
    return const_iterator(0, this);
  }
  const_iterator cbegin() const SPECULA_NOEXCEPT {
    return const_iterator(0, this);
  }
  iterator end() SPECULA_NOEXCEPT { return iterator(N, this); }
  const_iterator end() const SPECULA_NOEXCEPT {
    return const_iterator(N, this);
  }
  const_iterator cend() const SPECULA_NOEXCEPT {
    return const_iterator(N, this);
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
  reverse_iterator rend() { return reverse_iterator(N, this); }
  const_reverse_iterator rend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(N, this);
  }
  const_reverse_iterator crend() const SPECULA_NOEXCEPT {
    return const_reverse_iterator(N, this);
  }

  reference front() SPECULA_NOEXCEPT { return data[0]; }
  const_reference front() const SPECULA_NOEXCEPT { return data[0]; }
  reference back() SPECULA_NOEXCEPT { return data[N - 1]; }
  const_reference back() const SPECULA_NOEXCEPT { return data[N - 1]; }
  reference operator[](size_type i) { return data[i]; }
  const_reference operator[](size_type i) const { return data[i]; }
  reference at(size_type i) {
    if (i < 0 || i >= N)
      throw std::out_of_range(
          "specula::VectorN::_M_range_check: __n (which is " + std::to_string(i)
          << ") >= this->size() (which is " + std::to_string(this->size()) +
                 ")");
    return data[i];
  }
  const_reference at(size_type i) const {
    if (i < 0 || i >= N)
      throw std::out_of_range(
          "specula::VectorN::_M_range_check: __n (which is " + std::to_string(i)
          << ") >= this->size() (which is " + std::to_string(this->size()) +
                 ")");
    return data[i];
  }

  void clear() SPECULA_NOEXCEPT { std::fill(data, data + sizeof(data), T()); }

  void swap(VectorN &v) SPECULA_NOEXCEPT { std::swap(data, v.data); }
  SPECULA_CONSTEXPR size_type size() const SPECULA_NOEXCEPT { return N; }
  SPECULA_CONSTEXPR size_type max_size() const SPECULA_NOEXCEPT { return N; }
  SPECULA_CONSTEXPR bool empty() const SPECULA_NOEXCEPT { return false; }

  VectorN<T, N> operator+(const T &s) const SPECULA_NOEXCEPT {
    VectorN<T, N> out;
    for (size_type i = 0; i < this->size(); ++i) {
      out.data[i] = data[i] + s;
    }
    return out;
  }
  VectorN<T, N> operator+(const VectorN<T, N> &v) const SPECULA_NOEXCEPT {
    VectorN<T, N> out;
    for (size_type i = 0; i < this->size(); ++i) {
      out.data[i] = data[i] + v.data[i];
    }
    return out;
  }
  VectorN<T, N> &operator+=(const T &s) SPECULA_NOEXCEPT {
    for (size_type i = 0; i < this->size(); ++i) {
      data[i] += s;
    }
    return *this;
  }
  VectorN<T, N> &operator+=(const VectorN<T, N> &v) SPECULA_NOEXCEPT {
    for (size_type i = 0; i < this->size(); ++i) {
      data[i] += v.data[i];
    }
    return *this;
  }
  VectorN<T, N> operator-(const T &s) const SPECULA_NOEXCEPT {
    VectorN<T, N> out;
    for (size_type i = 0; i < this->size(); ++i) {
      out.data[i] = data[i] - s;
    }
    return out;
  }
  VectorN<T, N> operator-(const VectorN<T, N> &v) const SPECULA_NOEXCEPT {
    VectorN<T, N> out;
    for (size_type i = 0; i < this->size(); ++i) {
      out.data[i] = data[i] - v.data[i];
    }
    return out;
  }
  VectorN<T, N> &operator-=(const T &s) SPECULA_NOEXCEPT {
    for (size_type i = 0; i < this->size(); ++i) {
      data[i] -= s;
    }
    return *this;
  }
  VectorN<T, N> &operator-=(const VectorN<T, N> &v) SPECULA_NOEXCEPT {
    for (size_type i = 0; i < this->size(); ++i) {
      data[i] -= v.data[i];
    }
    return *this;
  }
  VectorN<T, N> operator*(const T &s) const SPECULA_NOEXCEPT {
    VectorN<T, N> out;
    for (size_type i = 0; i < this->size(); ++i) {
      out.data[i] = data[i] * s;
    }
    return out;
  }
  VectorN<T, N> operator*(const VectorN<T, N> &v) const SPECULA_NOEXCEPT {
    VectorN<T, N> out;
    for (size_type i = 0; i < this->size(); ++i) {
      out.data[i] = data[i] * v.data[i];
    }
    return out;
  }
  VectorN<T, N> &operator*=(const T &s) SPECULA_NOEXCEPT {
    for (size_type i = 0; i < this->size(); ++i) {
      data[i] *= s;
    }
    return *this;
  }
  VectorN<T, N> &operator*=(const VectorN<T, N> &v) SPECULA_NOEXCEPT {
    for (size_type i = 0; i < this->size(); ++i) {
      data[i] *= v.data[i];
    }
    return *this;
  }
  VectorN<T, N> operator/(const T &s) const SPECULA_NOEXCEPT {
    VectorN<T, N> out;
    T inv = T(1) / s;
    for (size_type i = 0; i < this->size(); ++i) {
      out.data[i] = data[i] * s;
    }
    return out;
  }
  VectorN<T, N> operator/(const VectorN<T, N> &v) const SPECULA_NOEXCEPT {
    VectorN<T, N> out;
    for (size_type i = 0; i < this->size(); ++i) {
      out.data[i] = data[i] / v.data[i];
    }
    return out;
  }
  VectorN<T, N> &operator/=(const T &s) SPECULA_NOEXCEPT {
    T inv = T(1) / s;
    for (size_type i = 0; i < this->size(); ++i) {
      data[i] *= s;
      ;
    }
    return *this;
  }
  VectorN<T, N> &operator/=(const VectorN<T, N> &v) SPECULA_NOEXCEPT {
    for (size_type i = 0; i < this->size(); ++i) {
      data[i] /= v.data[i];
    }
    return *this;
  }

  std::string fmt() const {
    std::string result = "<";
    for (size_type i = 0; i < N; ++i) {
      result += fmt::format("{}", data[i]) + ((i == N - 1) ? '>' : ',');
    }
    return result;
  }

  T data[N];

private:
  template <std::size_t I>
  typename std::enable_if<(I < N)>::type initialize(const T &v) {
    data[I] = v;
  }
  template <std::size_t I, typename... ARGS>
  typename std::enable_if<(I < N)>::type initialize(const T &v,
                                                    const ARGS &... args) {
    data[I] = v;
    initialize<I + 1>(args...);
  }
};

template <std::size_t N> using VectorNf = VectorN<Float, N>;
template <std::size_t N> using VectorNi = VectorN<Int, N>;

template <typename T, std::size_t N>
std::ostream &operator<<(std::ostream &out, const VectorN<T, N> &v) {
  return out << v.fmt();
}
} // namespace specula

#endif // SPECULA_VECTORN_HPP_
