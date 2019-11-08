#ifndef SPECULA_MATH_MAT4X4_HPP_
#define SPECULA_MATH_MAT4X4_HPP_

#include "../log.hpp"

namespace specula {
template <typename _T, std::size_t _N> class mat {
public:
  explicit mat(const _T &x) {}
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
          res[i][j] += data_[i][k] * b[k][j];
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
} // namespace specula

#endif // SPECULA_MATH_MAT4X4_HPP_
