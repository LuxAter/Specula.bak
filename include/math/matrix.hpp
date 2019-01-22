#ifndef SPECULA_MATH_MATRIX_HPP_
#define SPECULA_MATH_MATRIX_HPP_

#include <array>
#include <iostream>

#include "vector.hpp"

namespace specula {
namespace math {
  template <typename _T = double>
  class mat2;
  template <typename _T = double>
  class mat3;
  template <typename _T = double>
  class mat4;

  template <typename _T>
  class mat2 {
   public:
    mat2() { data_.fill(_T()); }
    mat2(const _T& v) : data_{{v, _T(), _T(), v}} {}
    mat2(const _T& aa, const _T& ab, const _T& ba, const _T& bb)
        : data_{{aa, ab, ba, bb}} {}
    template <typename _U>
    mat2(const mat2<_U>& v)
        : data_{{_T(v.data_[0]), _T(v.data_[1]), _T(v.data_[2]),
                 _T(v.data_[3])}} {}

    inline _T& operator[](const std::size_t& i) { return data_[i]; }
    inline _T operator[](const std::size_t& i) const { return data_[i]; }
    inline _T& operator()(const std::size_t& r, const std::size_t& c) {
      return data_[r * 2 + c];
    }
    inline _T operator()(const std::size_t& r, const std::size_t& c) const {
      return data_[r * 2 + c];
    }

    void fill(const _T& v) { data_.fill(v); }
    void diagonal(const _T& v) {
      data_[0] = v;
      data_[2] = v;
    }

    template <typename _U>
    inline mat2<_T>& operator+=(const _U& rhs) {
      data_[0] += rhs;
      data_[1] += rhs;
      data_[2] += rhs;
      data_[3] += rhs;
      return *this;
    }
    template <typename _U>
    inline mat2<_T>& operator+=(const mat2<_U>& rhs) {
      data_[0] += rhs[0];
      data_[1] += rhs[1];
      data_[2] += rhs[2];
      data_[3] += rhs[3];
      return *this;
    }
    template <typename _U>
    inline mat2<_T>& operator-=(const _U& rhs) {
      data_[0] -= rhs;
      data_[1] -= rhs;
      data_[2] -= rhs;
      data_[3] -= rhs;
      return *this;
    }
    template <typename _U>
    inline mat2<_T>& operator-=(const mat2<_U>& rhs) {
      data_[0] -= rhs[0];
      data_[1] -= rhs[1];
      data_[2] -= rhs[2];
      data_[3] -= rhs[3];
      return *this;
    }
    template <typename _U>
    inline mat2<_T>& operator*=(const _U& rhs) {
      data_[0] *= rhs;
      data_[1] *= rhs;
      data_[2] *= rhs;
      data_[3] *= rhs;
      return *this;
    }
    template <typename _U>
    inline mat2<_T>& operator*=(const mat2<_U>& rhs) {
      data_[0] *= rhs[0];
      data_[1] *= rhs[1];
      data_[2] *= rhs[2];
      data_[3] *= rhs[3];
      return *this;
    }
    template <typename _U>
    inline mat2<_T>& operator/=(const _U& rhs) {
      data_[0] /= rhs;
      data_[1] /= rhs;
      data_[2] /= rhs;
      data_[3] /= rhs;
      return *this;
    }
    template <typename _U>
    inline mat2<_T>& operator/=(const mat2<_U>& rhs) {
      data_[0] /= rhs[0];
      data_[1] /= rhs[1];
      data_[2] /= rhs[2];
      data_[3] /= rhs[3];
      return *this;
    }

   private:
    std::array<_T, 4> data_;
  };

  template <typename _T>
  class mat3 {
   public:
    mat3() { data_.fill(_T()); }
    mat3(const _T& v) : data_{{v, _T(), _T(), _T(), v, _T(), _T(), _T(), v}} {}
    mat3(const _T& aa, const _T& ab, const _T& ac, const _T& ba, const _T& bb,
         const _T& bc, const _T& ca, const _T& cb, const _T& cc)
        : data_{{aa, ab, ac, ba, bb, bc, ca, cb, cc}} {}
    template <typename _U>
    mat3(const mat3<_U>& v)
        : data_{{_T(v.data_[0]), _T(v.data_[1]), _T(v.data_[2]), _T(v.data_[3]),
                 _T(v.data_[4]), _T(v.data_[5]), _T(v.data_[6]), _T(v.data_[7]),
                 _T(v.data_[8])}} {}

    inline _T& operator[](const std::size_t& i) { return data_[i]; }
    inline _T operator[](const std::size_t& i) const { return data_[i]; }
    inline _T& operator()(const std::size_t& r, const std::size_t& c) {
      return data_[r * 3 + c];
    }
    inline _T operator()(const std::size_t& r, const std::size_t& c) const {
      return data_[r * 3 + c];
    }

    void fill(const _T& v) { data_.fill(v); }
    void diagonal(const _T& v) {
      data_[0] = v;
      data_[4] = v;
      data_[8] = v;
    }

    template <typename _U>
    inline mat3<_T>& operator+=(const _U& rhs) {
      data_[0] += rhs;
      data_[1] += rhs;
      data_[2] += rhs;
      data_[3] += rhs;
      data_[4] += rhs;
      data_[5] += rhs;
      data_[6] += rhs;
      data_[7] += rhs;
      data_[8] += rhs;
      return *this;
    }
    template <typename _U>
    inline mat3<_T>& operator+=(const mat3<_U>& rhs) {
      data_[0] += rhs[0];
      data_[1] += rhs[1];
      data_[2] += rhs[2];
      data_[3] += rhs[3];
      data_[4] += rhs[4];
      data_[5] += rhs[5];
      data_[6] += rhs[6];
      data_[7] += rhs[7];
      data_[8] += rhs[8];
      return *this;
    }
    template <typename _U>
    inline mat3<_T>& operator-=(const _U& rhs) {
      data_[0] -= rhs;
      data_[1] -= rhs;
      data_[2] -= rhs;
      data_[3] -= rhs;
      data_[4] -= rhs;
      data_[5] -= rhs;
      data_[6] -= rhs;
      data_[7] -= rhs;
      data_[8] -= rhs;
      return *this;
    }
    template <typename _U>
    inline mat3<_T>& operator-=(const mat3<_U>& rhs) {
      data_[0] -= rhs[0];
      data_[1] -= rhs[1];
      data_[2] -= rhs[2];
      data_[3] -= rhs[3];
      data_[4] -= rhs[4];
      data_[5] -= rhs[5];
      data_[6] -= rhs[6];
      data_[7] -= rhs[7];
      data_[8] -= rhs[8];
      return *this;
    }
    template <typename _U>
    inline mat3<_T>& operator*=(const _U& rhs) {
      data_[0] *= rhs;
      data_[1] *= rhs;
      data_[2] *= rhs;
      data_[3] *= rhs;
      data_[4] *= rhs;
      data_[5] *= rhs;
      data_[6] *= rhs;
      data_[7] *= rhs;
      data_[8] *= rhs;
      return *this;
    }
    template <typename _U>
    inline mat3<_T>& operator*=(const mat3<_U>& rhs) {
      data_[0] *= rhs[0];
      data_[1] *= rhs[1];
      data_[2] *= rhs[2];
      data_[3] *= rhs[3];
      data_[4] *= rhs[4];
      data_[5] *= rhs[5];
      data_[6] *= rhs[6];
      data_[7] *= rhs[7];
      data_[8] *= rhs[8];
      return *this;
    }
    template <typename _U>
    inline mat3<_T>& operator/=(const _U& rhs) {
      data_[0] /= rhs;
      data_[1] /= rhs;
      data_[2] /= rhs;
      data_[3] /= rhs;
      data_[4] /= rhs;
      data_[5] /= rhs;
      data_[6] /= rhs;
      data_[7] /= rhs;
      data_[8] /= rhs;
      return *this;
    }
    template <typename _U>
    inline mat3<_T>& operator/=(const mat3<_U>& rhs) {
      data_[0] /= rhs[0];
      data_[1] /= rhs[1];
      data_[2] /= rhs[2];
      data_[3] /= rhs[3];
      data_[4] /= rhs[4];
      data_[5] /= rhs[5];
      data_[6] /= rhs[6];
      data_[7] /= rhs[7];
      data_[8] /= rhs[8];
      return *this;
    }

   private:
    std::array<_T, 9> data_;
  };

  template <typename _T>
  class mat4 {
   public:
    mat4() { data_.fill(_T()); }
    mat4(const _T& v)
        : data_{{v, _T(), _T(), _T(), _T(), v, _T(), _T(), _T(), _T(), v, _T(),
                 _T(), _T(), _T(), v}} {}
    mat4(const _T& aa, const _T& ab, const _T& ac, const _T& ad, const _T& ba,
         const _T& bb, const _T& bc, const _T& bd, const _T& ca, const _T& cb,
         const _T& cc, const _T& cd, const _T& da, const _T& db, const _T& dc,
         const _T& dd)
        : data_{{aa, ab, ac, ad, ba, bb, bc, bd, ca, cb, cc, cd, da, db, dc,
                 dd}} {}
    template <typename _U>
    mat4(const mat3<_U>& v)
        : data_{{_T(v.data_[0]), _T(v.data_[1]), _T(v.data_[2]), _T(v.data_[3]),
                 _T(v.data_[4]), _T(v.data_[5]), _T(v.data_[6]), _T(v.data_[7]),
                 _T(v.data_[8]), _T(v.data_[9]), _T(v.data_[10]),
                 _T(v.data_[11]), _T(v.data_[12]), _T(v.data_[13]),
                 _T(v.data_[14]), _T(v.data_[15])}} {}

    inline _T& operator[](const std::size_t& i) { return data_[i]; }
    inline _T operator[](const std::size_t& i) const { return data_[i]; }
    inline _T& operator()(const std::size_t& r, const std::size_t& c) {
      return data_[r * 4 + c];
    }
    inline _T operator()(const std::size_t& r, const std::size_t& c) const {
      return data_[r * 4 + c];
    }

    void fill(const _T& v) { data_.fill(v); }
    void diagonal(const _T& v) {
      data_[0] = v;
      data_[5] = v;
      data_[10] = v;
      data_[15] = v;
    }

    template <typename _U>
    inline mat4<_T>& operator+=(const _U& rhs) {
      data_[0] += rhs;
      data_[1] += rhs;
      data_[2] += rhs;
      data_[3] += rhs;
      data_[4] += rhs;
      data_[5] += rhs;
      data_[6] += rhs;
      data_[7] += rhs;
      data_[8] += rhs;
      data_[9] += rhs;
      data_[10] += rhs;
      data_[11] += rhs;
      data_[12] += rhs;
      data_[13] += rhs;
      data_[14] += rhs;
      data_[15] += rhs;
      return *this;
    }
    template <typename _U>
    inline mat4<_T>& operator+=(const mat3<_U>& rhs) {
      data_[0] += rhs[0];
      data_[1] += rhs[1];
      data_[2] += rhs[2];
      data_[3] += rhs[3];
      data_[4] += rhs[4];
      data_[5] += rhs[5];
      data_[6] += rhs[6];
      data_[7] += rhs[7];
      data_[8] += rhs[8];
      data_[9] += rhs[9];
      data_[10] += rhs[10];
      data_[11] += rhs[11];
      data_[12] += rhs[12];
      data_[13] += rhs[13];
      data_[14] += rhs[14];
      data_[15] += rhs[15];
      return *this;
    }

    template <typename _U>
    inline mat4<_T>& operator-=(const _U& rhs) {
      data_[0] -= rhs;
      data_[1] -= rhs;
      data_[2] -= rhs;
      data_[3] -= rhs;
      data_[4] -= rhs;
      data_[5] -= rhs;
      data_[6] -= rhs;
      data_[7] -= rhs;
      data_[8] -= rhs;
      data_[9] -= rhs;
      data_[10] -= rhs;
      data_[11] -= rhs;
      data_[12] -= rhs;
      data_[13] -= rhs;
      data_[14] -= rhs;
      data_[15] -= rhs;
      return *this;
    }
    template <typename _U>
    inline mat4<_T>& operator-=(const mat3<_U>& rhs) {
      data_[0] -= rhs[0];
      data_[1] -= rhs[1];
      data_[2] -= rhs[2];
      data_[3] -= rhs[3];
      data_[4] -= rhs[4];
      data_[5] -= rhs[5];
      data_[6] -= rhs[6];
      data_[7] -= rhs[7];
      data_[8] -= rhs[8];
      data_[9] -= rhs[9];
      data_[10] -= rhs[10];
      data_[11] -= rhs[11];
      data_[12] -= rhs[12];
      data_[13] -= rhs[13];
      data_[14] -= rhs[14];
      data_[15] -= rhs[15];
      return *this;
    }
    template <typename _U>
    inline mat4<_T>& operator*=(const _U& rhs) {
      data_[0] *= rhs;
      data_[1] *= rhs;
      data_[2] *= rhs;
      data_[3] *= rhs;
      data_[4] *= rhs;
      data_[5] *= rhs;
      data_[6] *= rhs;
      data_[7] *= rhs;
      data_[8] *= rhs;
      data_[9] *= rhs;
      data_[10] *= rhs;
      data_[11] *= rhs;
      data_[12] *= rhs;
      data_[13] *= rhs;
      data_[14] *= rhs;
      data_[15] *= rhs;
      return *this;
    }
    template <typename _U>
    inline mat4<_T>& operator*=(const mat3<_U>& rhs) {
      data_[0] *= rhs[0];
      data_[1] *= rhs[1];
      data_[2] *= rhs[2];
      data_[3] *= rhs[3];
      data_[4] *= rhs[4];
      data_[5] *= rhs[5];
      data_[6] *= rhs[6];
      data_[7] *= rhs[7];
      data_[8] *= rhs[8];
      data_[9] *= rhs[9];
      data_[10] *= rhs[10];
      data_[11] *= rhs[11];
      data_[12] *= rhs[12];
      data_[13] *= rhs[13];
      data_[14] *= rhs[14];
      data_[15] *= rhs[15];
      return *this;
    }
    template <typename _U>
    inline mat4<_T>& operator/=(const _U& rhs) {
      data_[0] /= rhs;
      data_[1] /= rhs;
      data_[2] /= rhs;
      data_[3] /= rhs;
      data_[4] /= rhs;
      data_[5] /= rhs;
      data_[6] /= rhs;
      data_[7] /= rhs;
      data_[8] /= rhs;
      data_[9] /= rhs;
      data_[10] /= rhs;
      data_[11] /= rhs;
      data_[12] /= rhs;
      data_[13] /= rhs;
      data_[14] /= rhs;
      data_[15] /= rhs;
      return *this;
    }
    template <typename _U>
    inline mat4<_T>& operator/=(const mat3<_U>& rhs) {
      data_[0] /= rhs[0];
      data_[1] /= rhs[1];
      data_[2] /= rhs[2];
      data_[3] /= rhs[3];
      data_[4] /= rhs[4];
      data_[5] /= rhs[5];
      data_[6] /= rhs[6];
      data_[7] /= rhs[7];
      data_[8] /= rhs[8];
      data_[9] /= rhs[9];
      data_[10] /= rhs[10];
      data_[11] /= rhs[11];
      data_[12] /= rhs[12];
      data_[13] /= rhs[13];
      data_[14] /= rhs[14];
      data_[15] /= rhs[15];
      return *this;
    }

   private:
    std::array<_T, 16> data_;
  };

  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const mat2<_T>& mat) {
    out << '[' << '[' << mat[0] << ',' << mat[1] << ']' << '[' << mat[2] << ','
        << mat[3] << ']' << ']';
    return out;
  }
  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const mat3<_T>& mat) {
    out << '[' << '[' << mat[0] << ',' << mat[1] << ',' << mat[2] << ']' << '['
        << mat[3] << ',' << mat[4] << ',' << mat[5] << ']' << '[' << mat[6]
        << ',' << mat[7] << ',' << mat[8] << ']' << ']';
    return out;
  }
  template <typename _T>
  inline std::ostream& operator<<(std::ostream& out, const mat4<_T>& mat) {
    out << '[' << '[' << mat[0] << ',' << mat[1] << ',' << mat[2] << ','
        << mat[3] << ']' << '[' << mat[4] << ',' << mat[5] << ',' << mat[6]
        << ',' << mat[7] << ']' << '[' << mat[8] << ',' << mat[9] << ','
        << mat[10] << ',' << mat[11] << ']' << '[' << mat[12] << ',' << mat[13]
        << ',' << mat[14] << ',' << mat[15] << ']' << ']';
    return out;
  }

  template <typename _T>
  inline bool operator==(const mat2<_T>& lhs, const mat2<_T>& rhs) {
    return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] &&
           lhs[3] == rhs[3];
  }
  template <typename _T>
  inline bool operator!=(const mat2<_T>& lhs, const mat2<_T>& rhs) {
    return !(lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] &&
             lhs[3] == rhs[3]);
  }

  template <typename _T>
  inline bool operator==(const mat3<_T>& lhs, const mat3<_T>& rhs) {
    return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] &&
           lhs[3] == rhs[3] && lhs[4] == rhs[4] && lhs[5] == rhs[5] &&
           lhs[6] == rhs[6] && lhs[7] == rhs[7] && lhs[8] == rhs[8];
  }
  template <typename _T>
  inline bool operator!=(const mat3<_T>& lhs, const mat3<_T>& rhs) {
    return !(lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] &&
             lhs[3] == rhs[3] && lhs[4] == rhs[4] && lhs[5] == rhs[5] &&
             lhs[6] == rhs[6] && lhs[7] == rhs[7] && lhs[8] == rhs[8]);
  }

  template <typename _T>
  inline bool operator==(const mat4<_T>& lhs, const mat4<_T>& rhs) {
    return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] &&
           lhs[3] == rhs[3] && lhs[4] == rhs[4] && lhs[5] == rhs[5] &&
           lhs[6] == rhs[6] && lhs[7] == rhs[7] && lhs[8] == rhs[8] &&
           lhs[9] == rhs[9] && lhs[10] == rhs[10] && lhs[11] == rhs[11] &&
           lhs[12] == rhs[12] && lhs[13] == rhs[13] && lhs[14] == rhs[14] &&
           lhs[15] == rhs[15];
  }
  template <typename _T>
  inline bool operator!=(const mat4<_T>& lhs, const mat4<_T>& rhs) {
    return !(lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] &&
             lhs[3] == rhs[3] && lhs[4] == rhs[4] && lhs[5] == rhs[5] &&
             lhs[6] == rhs[6] && lhs[7] == rhs[7] && lhs[8] == rhs[8] &&
             lhs[9] == rhs[9] && lhs[10] == rhs[10] && lhs[11] == rhs[11] &&
             lhs[12] == rhs[12] && lhs[13] == rhs[13] && lhs[14] == rhs[14] &&
             lhs[15] == rhs[15]);
  }

  template <typename _T, typename _U>
  inline mat2<_T> operator+(const mat2<_T>& lhs, const _U& rhs) {
    return mat2<_T>(lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs, lhs[3] + rhs);
  }
  template <typename _T, typename _U>
  inline mat2<_T> operator+(const mat2<_T>& lhs, const mat2<_U>& rhs) {
    return mat2<_T>(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2],
                    lhs[3] + rhs[3]);
  }
  template <typename _T, typename _U>
  inline mat2<_T> operator-(const mat2<_T>& lhs, const _U& rhs) {
    return mat2<_T>(lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs, lhs[3] - rhs);
  }
  template <typename _T, typename _U>
  inline mat2<_T> operator-(const mat2<_T>& lhs, const mat2<_U>& rhs) {
    return mat2<_T>(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2],
                    lhs[3] - rhs[3]);
  }
  template <typename _T, typename _U>
  inline mat2<_T> operator*(const mat2<_T>& lhs, const _U& rhs) {
    return mat2<_T>(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs);
  }
  template <typename _T, typename _U>
  inline mat2<_T> operator*(const _U& lhs, const mat2<_T>& rhs) {
    return mat2<_T>(lhs * rhs[0], lhs * rhs[1], lhs * rhs[2], lhs * rhs[3]);
  }
  template <typename _T, typename _U>
  inline mat2<_T> operator*(const mat2<_T>& lhs, const mat2<_U>& rhs) {
    return mat2<_T>(
        lhs[0] * rhs[0] + lhs[1] * rhs[2], lhs[0] * rhs[1] + lhs[1] * rhs[3],
        lhs[2] * rhs[0] + lhs[3] * rhs[2], lhs[2] * rhs[1] + lhs[3] * rhs[3]);
  }
  template <typename _T, typename _U>
  inline vec2<_T> operator*(const mat2<_T>& lhs, const vec2<_U>& rhs) {
    return vec2<_T>(lhs[0] * rhs.x + lhs[1] * rhs.y,
                    lhs[2] * rhs.x + lhs[3] * rhs.y);
  }
  template <typename _T, typename _U>
  inline mat2<_T> operator/(const mat2<_T>& lhs, const _U& rhs) {
    return mat2<_T>(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs, lhs[3] / rhs);
  }
  template <typename _T, typename _U>
  inline mat2<_T> operator/(const mat2<_T>& lhs, const mat2<_U>& rhs) {
    return mat2<_T>(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2],
                    lhs[3] / rhs[3]);
  }

  template <typename _T, typename _U>
  inline mat3<_T> operator+(const mat3<_T>& lhs, const _U& rhs) {
    return mat3<_T>(lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs, lhs[3] + rhs,
                    lhs[4] + rhs, lhs[5] + rhs, lhs[6] + rhs, lhs[7] + rhs,
                    lhs[8] + rhs);
  }
  template <typename _T, typename _U>
  inline mat3<_T> operator+(const mat3<_T>& lhs, const mat3<_U>& rhs) {
    return mat3<_T>(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2],
                    lhs[3] + rhs[3], lhs[4] + rhs[4], lhs[5] + rhs[5],
                    lhs[6] + rhs[6], lhs[7] + rhs[7], lhs[8] + rhs[8]);
  }
  template <typename _T, typename _U>
  inline mat3<_T> operator-(const mat3<_T>& lhs, const _U& rhs) {
    return mat3<_T>(lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs, lhs[3] - rhs,
                    lhs[4] - rhs, lhs[5] - rhs, lhs[6] - rhs, lhs[7] - rhs,
                    lhs[8] - rhs);
  }
  template <typename _T, typename _U>
  inline mat3<_T> operator-(const mat3<_T>& lhs, const mat3<_U>& rhs) {
    return mat3<_T>(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2],
                    lhs[3] - rhs[3], lhs[4] - rhs[4], lhs[5] - rhs[5],
                    lhs[6] - rhs[6], lhs[7] - rhs[7], lhs[8] - rhs[8]);
  }
  template <typename _T, typename _U>
  inline mat3<_T> operator*(const mat3<_T>& lhs, const _U& rhs) {
    return mat3<_T>(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs,
                    lhs[4] * rhs, lhs[5] * rhs, lhs[6] * rhs, lhs[7] * rhs,
                    lhs[8] * rhs);
  }
  template <typename _T, typename _U>
  inline mat3<_T> operator*(const _U& lhs, const mat3<_U>& rhs) {
    return mat3<_T>(lhs * rhs[0], lhs * rhs[1], lhs * rhs[2], lhs * rhs[3],
                    lhs * rhs[4], lhs * rhs[5], lhs * rhs[6], lhs * rhs[7],
                    lhs * rhs[8]);
  }
  template <typename _T, typename _U>
  inline mat3<_T> operator*(const mat3<_T>& lhs, const mat3<_U>& rhs) {
    return mat3<_T>(lhs[0] * rhs[0] + lhs[1] * rhs[3] + lhs[2] * rhs[6],
                    lhs[0] * rhs[1] + lhs[1] * rhs[4] + lhs[2] * rhs[7],
                    lhs[0] * rhs[2] + lhs[1] * rhs[5] + lhs[2] * rhs[8],
                    lhs[3] * rhs[0] + lhs[4] * rhs[3] + lhs[5] * rhs[6],
                    lhs[3] * rhs[1] + lhs[4] * rhs[4] + lhs[5] * rhs[7],
                    lhs[3] * rhs[2] + lhs[4] * rhs[5] + lhs[5] * rhs[8],
                    lhs[6] * rhs[0] + lhs[7] * rhs[3] + lhs[8] * rhs[6],
                    lhs[6] * rhs[1] + lhs[7] * rhs[4] + lhs[8] * rhs[7],
                    lhs[6] * rhs[2] + lhs[7] * rhs[5] + lhs[8] * rhs[8]);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator*(const mat3<_T>& lhs, const vec2<_U>& rhs) {
    return vec3<_T>(lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2],
                    lhs[3] * rhs.x + lhs[4] * rhs.y + lhs[5],
                    lhs[6] * rhs.x + lhs[7] * rhs.y + lhs[8]);
  }
  template <typename _T, typename _U>
  inline vec3<_T> operator*(const mat3<_T>& lhs, const vec3<_U>& rhs) {
    return vec3<_T>(lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z,
                    lhs[3] * rhs.x + lhs[4] * rhs.y + lhs[5] * rhs.z,
                    lhs[6] * rhs.x + lhs[7] * rhs.y + lhs[8] * rhs.z);
  }
  template <typename _T, typename _U>
  inline mat3<_T> operator/(const mat3<_T>& lhs, const _U& rhs) {
    return mat3<_T>(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs, lhs[3] / rhs,
                    lhs[4] / rhs, lhs[5] / rhs, lhs[6] / rhs, lhs[7] / rhs,
                    lhs[8] / rhs);
  }
  template <typename _T, typename _U>
  inline mat3<_T> operator/(const mat3<_T>& lhs, const mat3<_U>& rhs) {
    return mat3<_T>(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2],
                    lhs[3] / rhs[3], lhs[4] / rhs[4], lhs[5] / rhs[5],
                    lhs[6] / rhs[6], lhs[7] / rhs[7], lhs[8] / rhs[8]);
  }

  template <typename _T, typename _U>
  inline mat4<_T> operator+(const mat4<_T>& lhs, const _U& rhs) {
    return mat4<_T>(lhs[0] + rhs, lhs[1] + rhs, lhs[2] + rhs, lhs[3] + rhs,
                    lhs[4] + rhs, lhs[5] + rhs, lhs[6] + rhs, lhs[7] + rhs,
                    lhs[8] + rhs, lhs[9] + rhs, lhs[10] + rhs, lhs[11] + rhs,
                    lhs[12] + rhs, lhs[13] + rhs, lhs[14] + rhs, lhs[15] + rhs);
  }
  template <typename _T, typename _U>
  inline mat4<_T> operator+(const mat4<_T>& lhs, const mat4<_U>& rhs) {
    return mat4<_T>(lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2],
                    lhs[3] + rhs[3], lhs[4] + rhs[4], lhs[5] + rhs[5],
                    lhs[6] + rhs[6], lhs[7] + rhs[7], lhs[8] + rhs[8],
                    lhs[9] + rhs[9], lhs[10] + rhs[10], lhs[11] + rhs[11],
                    lhs[12] + rhs[12], lhs[13] + rhs[13], lhs[14] + rhs[14],
                    lhs[15] + rhs[15]);
  }
  template <typename _T, typename _U>
  inline mat4<_T> operator-(const mat4<_T>& lhs, const _U& rhs) {
    return mat4<_T>(lhs[0] - rhs, lhs[1] - rhs, lhs[2] - rhs, lhs[3] - rhs,
                    lhs[4] - rhs, lhs[5] - rhs, lhs[6] - rhs, lhs[7] - rhs,
                    lhs[8] - rhs, lhs[9] - rhs, lhs[10] - rhs, lhs[11] - rhs,
                    lhs[12] - rhs, lhs[13] - rhs, lhs[14] - rhs, lhs[15] - rhs);
  }
  template <typename _T, typename _U>
  inline mat4<_T> operator-(const mat4<_T>& lhs, const mat4<_U>& rhs) {
    return mat4<_T>(lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2],
                    lhs[3] - rhs[3], lhs[4] - rhs[4], lhs[5] - rhs[5],
                    lhs[6] - rhs[6], lhs[7] - rhs[7], lhs[8] - rhs[8],
                    lhs[9] - rhs[9], lhs[10] - rhs[10], lhs[11] - rhs[11],
                    lhs[12] - rhs[12], lhs[13] - rhs[13], lhs[14] - rhs[14],
                    lhs[15] - rhs[15]);
  }
  template <typename _T, typename _U>
  inline mat4<_T> operator*(const mat4<_T>& lhs, const _U& rhs) {
    return mat4<_T>(lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs, lhs[3] * rhs,
                    lhs[4] * rhs, lhs[5] * rhs, lhs[6] * rhs, lhs[7] * rhs,
                    lhs[8] * rhs, lhs[9] * rhs, lhs[10] * rhs, lhs[11] * rhs,
                    lhs[12] * rhs, lhs[13] * rhs, lhs[14] * rhs, lhs[15] * rhs);
  }
  template <typename _T, typename _U>
  inline mat4<_T> operator*(const _U& lhs, const mat4<_U>& rhs) {
    return mat4<_T>(lhs * rhs[0], lhs * rhs[1], lhs * rhs[2], lhs * rhs[3],
                    lhs * rhs[4], lhs * rhs[5], lhs * rhs[6], lhs * rhs[7],
                    lhs * rhs[8], lhs * rhs[9], lhs * rhs[10], lhs * rhs[11],
                    lhs * rhs[12], lhs * rhs[13], lhs * rhs[14], lhs * rhs[15]);
  }
  template <typename _T, typename _U>
  inline mat4<_T> operator*(const mat4<_T>& lhs, const mat4<_U>& rhs) {
    return mat4<_T>(
        lhs[0] * rhs[0] + lhs[1] * rhs[4] + lhs[2] * rhs[8] + lhs[3] * rhs[12],
        lhs[0] * rhs[1] + lhs[1] * rhs[5] + lhs[2] * rhs[9] + lhs[3] * rhs[13],
        lhs[0] * rhs[2] + lhs[1] * rhs[6] + lhs[2] * rhs[10] + lhs[3] * rhs[14],
        lhs[0] * rhs[3] + lhs[1] * rhs[7] + lhs[2] * rhs[11] + lhs[3] * rhs[15],
        lhs[4] * rhs[0] + lhs[5] * rhs[4] + lhs[6] * rhs[8] + lhs[7] * rhs[12],
        lhs[4] * rhs[1] + lhs[5] * rhs[5] + lhs[6] * rhs[9] + lhs[7] * rhs[13],
        lhs[4] * rhs[2] + lhs[5] * rhs[6] + lhs[6] * rhs[10] + lhs[7] * rhs[14],
        lhs[4] * rhs[3] + lhs[5] * rhs[7] + lhs[6] * rhs[11] + lhs[7] * rhs[15],
        lhs[8] * rhs[0] + lhs[9] * rhs[4] + lhs[10] * rhs[8] +
            lhs[11] * rhs[12],
        lhs[8] * rhs[1] + lhs[9] * rhs[5] + lhs[10] * rhs[9] +
            lhs[11] * rhs[13],
        lhs[8] * rhs[2] + lhs[9] * rhs[6] + lhs[10] * rhs[10] +
            lhs[11] * rhs[14],
        lhs[8] * rhs[3] + lhs[9] * rhs[7] + lhs[10] * rhs[11] +
            lhs[11] * rhs[15],
        lhs[12] * rhs[0] + lhs[13] * rhs[4] + lhs[14] * rhs[8] +
            lhs[15] * rhs[12],
        lhs[12] * rhs[1] + lhs[13] * rhs[5] + lhs[14] * rhs[9] +
            lhs[15] * rhs[13],
        lhs[12] * rhs[2] + lhs[13] * rhs[6] + lhs[14] * rhs[10] +
            lhs[15] * rhs[14],
        lhs[12] * rhs[3] + lhs[13] * rhs[7] + lhs[14] * rhs[11] +
            lhs[15] * rhs[15]);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator*(const mat4<_T>& lhs, const vec2<_U>& rhs) {
    return vec4<_T>(lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] + lhs[3],
                    lhs[4] * rhs.x + lhs[5] * rhs.y + lhs[6] + lhs[7],
                    lhs[8] * rhs.x + lhs[9] * rhs.y + lhs[10] + lhs[11],
                    lhs[12] * rhs.x + lhs[13] * rhs.y + lhs[14] + lhs[15]);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator*(const mat4<_T>& lhs, const vec3<_U>& rhs) {
    return vec4<_T>(
        lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z + lhs[3],
        lhs[4] * rhs.x + lhs[5] * rhs.y + lhs[6] * rhs.z + lhs[7],
        lhs[8] * rhs.x + lhs[9] * rhs.y + lhs[10] * rhs.z + lhs[11],
        lhs[12] * rhs.x + lhs[13] * rhs.y + lhs[14] * rhs.z + lhs[15]);
  }
  template <typename _T, typename _U>
  inline vec4<_T> operator*(const mat4<_T>& lhs, const vec4<_U>& rhs) {
    return vec4<_T>(
        lhs[0] * rhs.x + lhs[1] * rhs.y + lhs[2] * rhs.z + lhs[3] * rhs.w,
        lhs[4] * rhs.x + lhs[5] * rhs.y + lhs[6] * rhs.z + lhs[7] * rhs.w,
        lhs[8] * rhs.x + lhs[9] * rhs.y + lhs[10] * rhs.z + lhs[11] * rhs.w,
        lhs[12] * rhs.x + lhs[13] * rhs.y + lhs[14] * rhs.z + lhs[15] * rhs.w);
  }
  template <typename _T, typename _U>
  inline mat4<_T> operator/(const mat4<_T>& lhs, const _U& rhs) {
    return mat4<_T>(lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs, lhs[3] / rhs,
                    lhs[4] / rhs, lhs[5] / rhs, lhs[6] / rhs, lhs[7] / rhs,
                    lhs[8] / rhs, lhs[9] / rhs, lhs[10] / rhs, lhs[11] / rhs,
                    lhs[12] / rhs, lhs[13] / rhs, lhs[14] / rhs, lhs[15] / rhs);
  }
  template <typename _T, typename _U>
  inline mat4<_T> operator/(const mat4<_T>& lhs, const mat4<_U>& rhs) {
    return mat4<_T>(lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2],
                    lhs[3] / rhs[3], lhs[4] / rhs[4], lhs[5] / rhs[5],
                    lhs[6] / rhs[6], lhs[7] / rhs[7], lhs[8] / rhs[8],
                    lhs[9] / rhs[9], lhs[10] / rhs[10], lhs[11] / rhs[11],
                    lhs[12] / rhs[12], lhs[13] / rhs[13], lhs[14] / rhs[14],
                    lhs[15] / rhs[15]);
  }

  typedef mat2<bool> bmat2;
  typedef mat2<int> imat2;
  typedef mat2<float> fmat2;
  typedef mat3<bool> bmat3;
  typedef mat3<int> imat3;
  typedef mat3<float> fmat3;
  typedef mat4<bool> bmat4;
  typedef mat4<int> imat4;
  typedef mat4<float> fmat4;

}  // namespace math
}  // namespace specula

#endif  // SPECULA_MATH_MATRIX_HPP_
