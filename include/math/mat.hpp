#ifndef SPECULA_MATH_MAT_HPP_
#define SPECULA_MATH_MAT_HPP_

#include <cstdlib>
#include <array>

namespace specula {
template <typename _T, std::size_t _N> class mat {
public:
  explicit mat(const _T &x) {
    for (std::size_t i = 0; i < _N; ++i) {
      data_[i][i] = x;
    }
  }
  template <typename... ARGS>
  mat(ARGS &&... vals) : data_{std::forward<ARGS>(vals)...} {
    static_assert(sizeof...(ARGS) == (_N * _N), "Expected _N arguments");
  }
  mat(const mat<_T, _N> &copy) : data_(copy.data_) {}

  inline mat<_T, _N> &operator=(const mat<_T, _N> &other) {
    data_ = other.data_;
    return *this;
  }

  inline mat<_T, _N> &operator+=(const mat<_T, _N> &other) {
    for (std::size_t i = 0; i < _N; ++i) {
      for (std::size_t j = 0; j < _N; ++j) {
        data_[i][j] += other.data_[i][j];
      }
    }
    return *this;
  }
  inline mat<_T, _N> &operator-=(const mat<_T, _N> &other) {
    for (std::size_t i = 0; i < _N; ++i) {
      for (std::size_t j = 0; j < _N; ++j) {
        data_[i][j] -= other.data_[i][j];
      }
    }
    return *this;
  }
  inline mat<_T, _N> &operator*=(const _T &v) {
    for (std::size_t i = 0; i < _N; ++i) {
      for (std::size_t j = 0; j < _N; ++j) {
        data_[i][j] *= v;
      }
    }
    return *this;
  }
  inline mat<_T, _N> &operator*=(const mat<_T, _N> &other) {
    std::array<std::array<_T, _N>, _N> res;
    for (std::size_t i = 0; i < _N; ++i) {
      for (std::size_t j = 0; j < _N; ++j) {
        for (std::size_t k = 0; j < _N; ++k) {
          res[i][j] += data_[i][k] * other.data_[k][j];
        }
      }
    }
    data_ = res;
    return *this;
  }
  inline mat<_T, _N> &operator/=(const mat<_T, _N> &other) {
    for (std::size_t i = 0; i < _N; ++i) {
      for (std::size_t j = 0; j < _N; ++j) {
        data_[i][j] /= other.data_[i][j];
      }
    }
    return *this;
  }

  std::array<std::array<_T, _N>, _N> data_;
};

template <typename _T>
using mat4x4 = mat<_T, 4>;
typedef mat<float, 4> mat4;

} // namespace specula

#endif // SPECULA_MATH_MAT_HPP_
