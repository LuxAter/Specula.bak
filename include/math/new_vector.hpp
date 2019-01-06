#ifndef SPECULA_MATH_VECTOR_HPP_
#define SPECULA_MATH_VECTOR_HPP_

#include <array>
#include <cmath>
#include <functional>
#include <iostream>

namespace specula {
namespace math {
  template <typename _T, std::size_t _N>
  class vec {
   public:
    vec() { data_.fill(_T()); }
    template <std::size_t _M>
    vec(const vec<_T, _M>& copy, typename std::enable_if < _M<_N>::type* = 0) {
      data_.fill(_T());
      std::copy(copy.begin(), copy.end(), data_.begin());
    }
    vec(const std::initializer_list<_T>& init) {
      data_.fill(_T());
      std::copy(init.begin(), init.end(), data_.begin());
    }
    template <typename... _ARGS>
    vec(const _ARGS&... args) {
      data_.fill(_T());
      constructor<0>(args...);
    }
    vec(const vec<_T, _N>& copy) : data_(copy.data_) {}

    template <std::size_t _M>
        inline typename std::enable_if <
        _M<_N, vec<_T, _N>&>::type operator=(const vec<_T, _M>& vec) {
      data_.fill(_T());
      std::copy(vec.begin(), vec.end(), data_.begin());
    }
    inline vec<_T, _N>& operator=(const std::initializer_list<_T>& init) {
      data_.fill(_T());
      std::copy(init.begin(), init.end(), data_.begin());
      return *this;
    }
    template <typename... _ARGS>
    inline vec<_T, _N>& operator=(const _ARGS&... args) {
      data_.fill(_T());
      constructor<0>(args...);
      return *this;
    }
    inline vec<_T, _N>& operator=(const vec<_T, _N>& vec) {
      std::copy(vec.begin(), vec.end(), data_.begin());
      return *this;
    }

    inline _T& operator[](std::size_t i) { return data_[i]; }
    inline const _T& operator[](std::size_t i) const { return data_[i]; }

    template <typename _U>
    inline vec<_T, _N>& operator+=(const _U& rhs) {
      for (std::size_t i = 0; i < _N; ++i) {
        data_[i] += rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline vec<_T, _N>& operator+=(const vec<_U, _M>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        data_[i] += rhs[i];
      }
      return *this;
    }
    template <typename _U>
    inline vec<_T, _N>& operator-=(const _U& rhs) {
      for (std::size_t i = 0; i < _N; ++i) {
        data_[i] -= rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline vec<_T, _N>& operator-=(const vec<_U, _M>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        data_[i] -= rhs[i];
      }
      return *this;
    }
    template <typename _U>
    inline vec<_T, _N>& operator*=(const _U& rhs) {
      for (std::size_t i = 0; i < _N; ++i) {
        data_[i] *= rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline vec<_T, _N>& operator*=(const vec<_U, _M>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        data_[i] *= rhs[i];
      }
      return *this;
    }
    template <typename _U>
    inline vec<_T, _N>& operator/=(const _U& rhs) {
      for (std::size_t i = 0; i < _N; ++i) {
        data_[i] /= rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _M>
    inline vec<_T, _N>& operator/=(const vec<_U, _M>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        data_[i] /= rhs[i];
      }
      return *this;
    }
    inline vec<_T, _N>& operator-() {
      for (std::size_t i = 0; i < _N; ++i) {
        data_[i] = -data_[i];
      }
      return *this;
    }

    inline _T& swizzel(std::size_t a) { return data_[a]; }
    inline vec<_T*, 2> swizzel(std::size_t a, std::size_t b) {
      return vec<_T*, 2>(&data_[a], &data_[b]);
    }

    inline typename std::array<_T, _N>::iterator begin() {
      return data_.begin();
    }
    inline typename std::array<_T, _N>::const_iterator begin() const {
      return data_.cbegin();
    }
    inline typename std::array<_T, _N>::const_iterator cbegin() const {
      return data_.cbegin();
    }

    inline typename std::array<_T, _N>::iterator end() { return data_.end(); }
    inline typename std::array<_T, _N>::const_iterator end() const {
      return data_.cend();
    }
    inline typename std::array<_T, _N>::const_iterator cend() const {
      return data_.cend();
    }

   private:
    template <std::size_t _I, typename... _ARGS>
        typename std::enable_if <
        _I<_N, void>::type constructor(_T t, _ARGS... args) {
      data_[_I] = t;
      constructor<_I + 1>(args...);
    }
    template <std::size_t _I>
        typename std::enable_if <
        _I<_N && _I != 0, void>::type constructor(_T t) {
      data_[_I] = t;
    }
    template <std::size_t _I>
    typename std::enable_if<_I == 0, void>::type constructor(_T t) {
      data_.fill(t);
    }

    std::array<_T, _N> data_;
  };
  template <typename _T, std::size_t _N>
  std::ostream& operator<<(std::ostream& out, const vec<_T, _N>& vec) {
    out << '<';
    for (std::size_t i = 0; i < _N - 1; ++i) {
      out << vec[i] << ',';
    }
    out << vec[_N - 1] << '>';
    return out;
  }

  template <typename _T, std::size_t _N>
  inline vec<_T, _N> component_func(const vec<_T, _N>& lhs,
                                    const _T (*func)(const _T&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < _N; ++i) {
      ret[i] = func(lhs[i]);
    }
    return ret;
  }
  template <typename _T, std::size_t _N, typename _U, std::size_t _M>
  inline vec<_T, _N> component_func(const vec<_T, _N>& lhs,
                                    const vec<_T, _N>& rhs,
                                    const _T (*func)(const _T&, const _U&)) {
    vec<_T, _N> ret;
    for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
      ret[i] = func(lhs[i], rhs[i]);
    }
    return ret;
  }

  typedef vec<float, 2> vec2;
  typedef vec<float, 3> vec3;
  typedef vec<float, 4> vec4;
  typedef vec<float, 8> vec8;
  typedef vec<float, 16> vec16;
}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_VECTOR_HPP_
