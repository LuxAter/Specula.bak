#ifndef SPECULA_MATH_MATRIX_HPP_
#define SPECULA_MATH_MATRIX_HPP_

#include <array>
#include <cmath>
#include <iostream>
#include <memory>

#include "vector.hpp"

namespace specula {
namespace math {
  template <typename _T, std::size_t _N, std::size_t _M>
  struct mat {
   public:
    mat() {
      for (std::size_t i = 0; i < _N * _M; ++i) {
        data_[i] = std::make_shared<_T>(_T());
      }
    }
    mat(const std::initializer_list<std::initializer_list<_T>>& init) {
      for (std::size_t i = 0; i < _N * _M; ++i) {
        data_[i] = std::make_shared<_T>(_T());
      }
      std::size_t r = 0;
      for (auto row = init.begin(); row != init.end() && r < _N; ++row, ++r) {
        std::size_t c = 0;
        for (auto col = row->begin(); col != row->end() && c < _M; ++col, ++c) {
          *data_[r * _M + c] = *col;
        }
      }
    }
    template <typename... _ARGS>
    mat(const _ARGS&... args) {
      for (std::size_t i = 0; i < _N * _M; ++i) {
        data_[i] = std::make_shared<_T>(_T());
      }
      constructor<0>(args...);
    }
    template <typename _U, std::size_t _O, std::size_t _P>
    mat(const mat<_U, _O, _P>& copy,
        typename std::enable_if<_O <= _N && _P <= _M>::type* = 0) {
      for (std::size_t i = 0; i < _N * _M; ++i) {
        data_[i] = std::make_shared<_T>(_T());
      }
      for (std::size_t i0 = 0, i1 = 0; i0 < _O && i1 < _N; ++i0, ++i1) {
        for (std::size_t j0 = 0, j1 = 0; j0 < _P && j1 < _M; ++j0, ++j1) {
          *data_[i1 * _M + j1] = _T(copy[i0 * _P + j0]);
        }
      }
    }

    void fill(const _T& v) {
      for (std::size_t i = 0; i < _N * _M; ++i) {
        *data_[i] = v;
      }
    }
    void diagonal(const _T& v) {
      for (std::size_t i = 0; i < std::min(_N, _M); ++i) {
        *data_[i * _M + i] = v;
      }
    }

    inline _T& operator[](std::size_t i) { return *data_[i]; }
    inline const _T& operator[](std::size_t i) const { return *data_[i]; }
    inline _T operator()(std::size_t r, std::size_t c) {
      return *data_[r * _M + c];
    }
    inline const _T operator()(std::size_t r, std::size_t c) const {
      return *data_[r * _M + c];
    }
    inline _T at(std::size_t r, std::size_t c) { return *data_[r * _M + c]; }
    inline const _T at(std::size_t r, std::size_t c) const {
      return *data_[r * _M + c];
    }
    inline swizzel<_T, _N> c(std::size_t col) {
      std::array<std::shared_ptr<_T>, _N> c_;
      for (std::size_t i = 0; i < _N; ++i) {
        c_[i] = data_[i * _M + col];
      }
      return swizzel<_T, _N>(c_);
    }
    inline swizzel<_T, _N> r(std::size_t row) {
      std::array<std::shared_ptr<_T>, _M> r_;
      for (std::size_t i = 0; i < _M; ++i) {
        r_[i] = data_[row * _M + i];
      }
      return swizzel<_T, _N>(r_);
    }

    template <typename _U>
    inline mat<_T, _N, _M>& operator+=(const _U& rhs) {
      for (std::size_t i = 0; i < _N * _M; ++i) {
        *data_[i] += rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _I, std::size_t _J>
    inline mat<_T, _N, _M>& operator+=(const mat<_U, _I, _J>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
        for (std::size_t j = 0; j < std::min(_M, _J); ++j) {
          *data_[i * _M + j] += rhs[i * _J + j];
        }
      }
      return *this;
    }
    template <typename _U>
    inline mat<_T, _N, _M>& operator-=(const _U& rhs) {
      for (std::size_t i = 0; i < _N * _M; ++i) {
        *data_[i] -= rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _I, std::size_t _J>
    inline mat<_T, _N, _M>& operator-=(const mat<_U, _I, _J>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
        for (std::size_t j = 0; j < std::min(_M, _J); ++j) {
          *data_[i * _M + j] -= rhs[i * _J + j];
        }
      }
      return *this;
    }
    template <typename _U>
    inline mat<_T, _N, _M>& operator*=(const _U& rhs) {
      for (std::size_t i = 0; i < _N * _M; ++i) {
        *data_[i] *= rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _I, std::size_t _J>
    inline mat<_T, _N, _M>& operator*=(const mat<_U, _I, _J>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
        for (std::size_t j = 0; j < std::min(_M, _J); ++j) {
          *data_[i * _M + j] *= rhs[i * _J + j];
        }
      }
      return *this;
    }
    template <typename _U>
    inline mat<_T, _N, _M>& operator/=(const _U& rhs) {
      for (std::size_t i = 0; i < _N * _M; ++i) {
        *data_[i] /= rhs;
      }
      return *this;
    }
    template <typename _U, std::size_t _I, std::size_t _J>
    inline mat<_T, _N, _M>& operator/=(const mat<_U, _I, _J>& rhs) {
      for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
        for (std::size_t j = 0; j < std::min(_M, _J); ++j) {
          *data_[i * _M + j] /= rhs[i * _J + j];
        }
      }
      return *this;
    }

   private:
    template <std::size_t _I, typename... _ARGS>
        typename std::enable_if <
        _I<_N * _M, void>::type constructor(const _T& t, const _ARGS&... args) {
      *data_[_I] = t;
      constructor<_I + 1>(args...);
    }
    template <std::size_t _I, std::size_t _J, typename... _ARGS>
        typename std::enable_if <
        _I<_N * _M, void>::type constructor(const vec<_T, _J>& v,
                                            const _ARGS&... args) {
      for (std::size_t i = 0; i < std::min(_N, _J); ++i) {
        *data_[i * _M + _I] = v[i];
      }
      constructor<_I + 1>(args...);
    }
    template <std::size_t _I, typename... _ARGS>
        typename std::enable_if <
        _I<_N * _M && _I != 0, void>::type constructor(const _T& t) {
      *data_[_I] = t;
    }
    template <std::size_t _I, typename... _ARGS>
    typename std::enable_if<_I == 0, void>::type constructor(const _T& t) {
      for (std::size_t i = 0; i < std::max(_N, _M); ++i) {
        *data_[i * _M + i] = t;
      }
    }
    template <std::size_t _I, std::size_t _J, typename... _ARGS>
        typename std::enable_if <
        _I<_N * _M, void>::type constructor(const vec<_T, _J>& v) {
      for (std::size_t i = 0; i < std::min(_N, _J); ++i) {
        *data_[i * _M + _I] = v[i];
      }
    }

    std::array<std::shared_ptr<_T>, _N * _M> data_;
  };

  template <typename _T, std::size_t _N, std::size_t _M>
  std::ostream& operator<<(std::ostream& out, const mat<_T, _N, _M>& mat) {
    out << '[';
    for (std::size_t i = 0; i < _N - 1; ++i) {
      out << '[';
      for (std::size_t j = 0; j < _M - 1; ++j) {
        out << mat[i * _M + j] << ',';
      }
      out << mat[i * _M + _M - 1] << ']' << ',';
    }
    out << '[';
    for (std::size_t j = 0; j < _M - 1; ++j) {
      out << mat[(_N - 1) * _M + j] << ',';
    }
    out << mat[(_N - 1) * _M + _M - 1] << ']' << ']';
    return out;
  }

  template <typename _T, std::size_t _N, std::size_t _M>
  inline bool operator==(const mat<_T, _N, _M>& lhs,
                         const mat<_T, _N, _M>& rhs) {
    for (std::size_t i = 0; i < _N * _M; ++i) {
      if (lhs[i] != rhs[i]) return false;
    }
    return true;
  }
  template <typename _T, std::size_t _N, std::size_t _M>
  inline bool operator!=(const mat<_T, _N, _M>& lhs,
                         const mat<_T, _N, _M>& rhs) {
    return !(lhs == rhs);
  }

  template <typename _T, std::size_t _N, std::size_t _M, typename _U>
  inline mat<_T, _N, _M> operator+(const mat<_T, _N, _M>& lhs, const _U& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < _N * _M; ++i) {
      res[i] = lhs[i] + rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N, std::size_t _M, typename _U,
            std::size_t _I, std::size_t _J>
  inline mat<_T, _N, _M> operator+(const mat<_T, _N, _M>& lhs,
                                   const mat<_U, _I, _J>& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
      for (std::size_t j = 0; j < std::min(_M, _J); ++j) {
        res[i * _M + j] = lhs[i * _M + j] + rhs[i * _J + j];
      }
    }
    return res;
  }
  template <typename _T, std::size_t _N, std::size_t _M, typename _U,
            std::size_t _I>
  inline mat<_T, _N, _M> operator+(const mat<_T, _N, _M>& lhs,
                                   const vec<_U, _I>& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
      for (std::size_t j = 0; j < _M; ++j) {
        res[i * _M + j] = lhs[i * _M + j] + rhs[i];
      }
    }
    return res;
  }

  template <typename _T, std::size_t _N, std::size_t _M, typename _U>
  inline mat<_T, _N, _M> operator-(const mat<_T, _N, _M>& lhs, const _U& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < _N * _M; ++i) {
      res[i] = lhs[i] - rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N, std::size_t _M, typename _U,
            std::size_t _I, std::size_t _J>
  inline mat<_T, _N, _M> operator-(const mat<_T, _N, _M>& lhs,
                                   const mat<_U, _I, _J>& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
      for (std::size_t j = 0; j < std::min(_M, _J); ++j) {
        res[i * _M + j] = lhs[i * _M + j] - rhs[i * _J + j];
      }
    }
    return res;
  }
  template <typename _T, std::size_t _N, std::size_t _M, typename _U,
            std::size_t _I>
  inline mat<_T, _N, _M> operator-(const mat<_T, _N, _M>& lhs,
                                   const vec<_U, _I>& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
      for (std::size_t j = 0; j < _M; ++j) {
        res[i * _M + j] = lhs[i * _M + j] - rhs[i];
      }
    }
    return res;
  }

  template <typename _T, std::size_t _N, std::size_t _M, typename _U>
  inline mat<_T, _N, _M> operator*(const mat<_T, _N, _M>& lhs, const _U& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < _N * _M; ++i) {
      res[i] = lhs[i] * rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N, std::size_t _M, typename _U>
  inline mat<_T, _N, _M> operator*(const _U& lhs, const mat<_T, _N, _M>& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < _N * _M; ++i) {
      res[i] = lhs * rhs[i];
    }
    return res;
  }
  template <typename _T, typename _U, std::size_t _R, std::size_t _S,
            std::size_t _C>
  inline mat<_T, _R, _C> operator*(const mat<_T, _R, _S>& lhs,
                                   const mat<_U, _S, _C>& rhs) {
    mat<_T, _R, _C> res;
    for (std::size_t i = 0; i < _R; ++i) {
      for (std::size_t j = 0; j < _C; ++j) {
        for (std::size_t k = 0; k < _S; ++k) {
          res[i * _C + j] += (lhs[i * _S + k] * rhs[k * _C + j]);
        }
      }
    }
    return res;
  }

  template <typename _T, std::size_t _N, std::size_t _M, typename _U>
  inline mat<_T, _N, _M> operator/(const mat<_T, _N, _M>& lhs, const _U& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < _N * _M; ++i) {
      res[i] = lhs[i] / rhs;
    }
    return res;
  }
  template <typename _T, std::size_t _N, std::size_t _M, typename _U,
            std::size_t _I, std::size_t _J>
  inline mat<_T, _N, _M> operator/(const mat<_T, _N, _M>& lhs,
                                   const mat<_U, _I, _J>& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
      for (std::size_t j = 0; j < std::min(_M, _J); ++j) {
        res[i * _M + j] = lhs[i * _M + j] / rhs[i * _J + j];
      }
    }
    return res;
  }
  template <typename _T, std::size_t _N, std::size_t _M, typename _U,
            std::size_t _I>
  inline mat<_T, _N, _M> operator/(const mat<_T, _N, _M>& lhs,
                                   const vec<_U, _I>& rhs) {
    mat<_T, _N, _M> res;
    for (std::size_t i = 0; i < std::min(_N, _I); ++i) {
      for (std::size_t j = 0; j < _M; ++j) {
        res[i * _M + j] = lhs[i * _M + j] / rhs[i];
      }
    }
    return res;
  }

  typedef mat<bool, 2, 2> bmat2;
  typedef mat<bool, 3, 3> bmat3;
  typedef mat<bool, 4, 4> bmat4;
  typedef mat<bool, 8, 8> bmat8;
  typedef mat<bool, 16, 16> bmat16;
  typedef mat<bool, 2, 2> bmat2x2;
  typedef mat<bool, 2, 3> bmat2x3;
  typedef mat<bool, 2, 4> bmat2x4;
  typedef mat<bool, 2, 8> bmat2x8;
  typedef mat<bool, 2, 8> bmat2x16;
  typedef mat<bool, 3, 2> bmat3x2;
  typedef mat<bool, 3, 3> bmat3x3;
  typedef mat<bool, 3, 4> bmat3x4;
  typedef mat<bool, 3, 8> bmat3x8;
  typedef mat<bool, 3, 8> bmat3x16;
  typedef mat<bool, 4, 2> bmat4x2;
  typedef mat<bool, 4, 3> bmat4x3;
  typedef mat<bool, 4, 4> bmat4x4;
  typedef mat<bool, 4, 8> bmat4x8;
  typedef mat<bool, 4, 8> bmat4x16;
  typedef mat<bool, 8, 2> bmat8x2;
  typedef mat<bool, 8, 3> bmat8x3;
  typedef mat<bool, 8, 4> bmat8x4;
  typedef mat<bool, 8, 8> bmat8x8;
  typedef mat<bool, 8, 8> bmat8x16;
  typedef mat<bool, 16, 2> bmat16x2;
  typedef mat<bool, 16, 3> bmat16x3;
  typedef mat<bool, 16, 4> bmat16x4;
  typedef mat<bool, 16, 8> bmat16x8;
  typedef mat<bool, 16, 8> bmat16x16;
  typedef mat<int, 2, 2> imat2;
  typedef mat<int, 3, 3> imat3;
  typedef mat<int, 4, 4> imat4;
  typedef mat<int, 8, 8> imat8;
  typedef mat<int, 16, 16> imat16;
  typedef mat<int, 2, 2> imat2x2;
  typedef mat<int, 2, 3> imat2x3;
  typedef mat<int, 2, 4> imat2x4;
  typedef mat<int, 2, 8> imat2x8;
  typedef mat<int, 2, 8> imat2x16;
  typedef mat<int, 3, 2> imat3x2;
  typedef mat<int, 3, 3> imat3x3;
  typedef mat<int, 3, 4> imat3x4;
  typedef mat<int, 3, 8> imat3x8;
  typedef mat<int, 3, 8> imat3x16;
  typedef mat<int, 4, 2> imat4x2;
  typedef mat<int, 4, 3> imat4x3;
  typedef mat<int, 4, 4> imat4x4;
  typedef mat<int, 4, 8> imat4x8;
  typedef mat<int, 4, 8> imat4x16;
  typedef mat<int, 8, 2> imat8x2;
  typedef mat<int, 8, 3> imat8x3;
  typedef mat<int, 8, 4> imat8x4;
  typedef mat<int, 8, 8> imat8x8;
  typedef mat<int, 8, 8> imat8x16;
  typedef mat<int, 16, 2> imat16x2;
  typedef mat<int, 16, 3> imat16x3;
  typedef mat<int, 16, 4> imat16x4;
  typedef mat<int, 16, 8> imat16x8;
  typedef mat<int, 16, 8> imat16x16;
  typedef mat<float, 2, 2> mat2;
  typedef mat<float, 3, 3> mat3;
  typedef mat<float, 4, 4> mat4;
  typedef mat<float, 8, 8> mat8;
  typedef mat<float, 16, 16> mat16;
  typedef mat<float, 2, 2> mat2x2;
  typedef mat<float, 2, 3> mat2x3;
  typedef mat<float, 2, 4> mat2x4;
  typedef mat<float, 2, 8> mat2x8;
  typedef mat<float, 2, 8> mat2x16;
  typedef mat<float, 3, 2> mat3x2;
  typedef mat<float, 3, 3> mat3x3;
  typedef mat<float, 3, 4> mat3x4;
  typedef mat<float, 3, 8> mat3x8;
  typedef mat<float, 3, 8> mat3x16;
  typedef mat<float, 4, 2> mat4x2;
  typedef mat<float, 4, 3> mat4x3;
  typedef mat<float, 4, 4> mat4x4;
  typedef mat<float, 4, 8> mat4x8;
  typedef mat<float, 4, 8> mat4x16;
  typedef mat<float, 8, 2> mat8x2;
  typedef mat<float, 8, 3> mat8x3;
  typedef mat<float, 8, 4> mat8x4;
  typedef mat<float, 8, 8> mat8x8;
  typedef mat<float, 8, 8> mat8x16;
  typedef mat<float, 16, 2> mat16x2;
  typedef mat<float, 16, 3> mat16x3;
  typedef mat<float, 16, 4> mat16x4;
  typedef mat<float, 16, 8> mat16x8;
  typedef mat<float, 16, 8> mat16x16;

}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_MATRIX_HPP_
