#ifndef SPECULA_CORE_GEOMETRY_MATRIX_HPP_
#define SPECULA_CORE_GEOMETRY_MATRIX_HPP_

#include "specula/global.hpp"

#include <array>

namespace specula {
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Matrix {
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;
};

template <typename T> class Matrix4x4 : public Matrix<T> {
public:
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;
  typedef const T &const_reference;
  typedef const T *const_pointer;
  typedef std::size_t size_type;

  Matrix4x4()
      : data({std::array<Float, 4>{1.0, 0.0, 0.0, 0.0},
              std::array<Float, 4>{0.0, 1.0, 0.0, 0.0},
              std::array<Float, 4>{0.0, 0.0, 1.0, 0.0},
              std::array<Float, 4>{0.0, 0.0, 0.0, 1.0}}) {}
  Matrix4x4(const T mat[4][4])
      : data({std::array<Float, 4>{mat[0][0], mat[0][1], mat[0][2], mat[0][3]},
              std::array<Float, 4>{mat[1][0], mat[1][1], mat[1][2], mat[1][3]},
              std::array<Float, 4>{mat[2][0], mat[2][1], mat[2][2], mat[2][3]},
              std::array<Float, 4>{mat[3][0], mat[3][1], mat[3][2],
                                   mat[3][3]}}) {}
  Matrix4x4(const T &m00, const T &m01, const T &m02, const T &m03,
            const T &m10, const T &m11, const T &m12, const T &m13,
            const T &m20, const T &m21, const T &m22, const T &m23,
            const T &m30, const T &m31, const T &m32, const T &m33)
      : data({std::array<Float, 4>{m00, m01, m02, m03},
              std::array<Float, 4>{m10, m11, m12, m13},
              std::array<Float, 4>{m20, m21, m22, m23},
              std::array<Float, 4>{m30, m31, m32, m33}}) {}

  bool operator==(const Matrix4x4 &m) const {
    for (size_type i = 0; i < 4; ++i) {
      for (size_type j = 0; j < 4; ++j) {
        if (data[i][j] != m.data[i][j])
          return false;
      }
    }
    return true;
  }
  bool operator!=(const Matrix4x4 &m) const {
    for (size_type i = 0; i < 4; ++i) {
      for (size_type j = 0; j < 4; ++j) {
        if (data[i][j] != m.data[i][j])
          return true;
      }
    }
    return false;
  }

  Matrix4x4 operator*(const Matrix4x4<T> &m) const {
    Matrix4x4 r;
    for (size_type i = 0; i < 4; ++i) {
      for (size_type j = 0; j < 4; ++j) {
        r.data[i][j] = data[i][0] * m.data[0][j] + data[i][1] * m.data[1][j] +
                       data[i][2] * m.data[2][j] + data[i][3] * m.data[3][j];
      }
    }
    return r;
  }

  inline std::string fmt() const {
    return fmt::format("[[{}, {}, {}, {}], [{}, {}, {}, {}], [{}, {}, {}, {}], "
                       "[{}, {}, {}, {}]]",
                       data[0][0], data[0][1], data[0][2], data[0][3],
                       data[1][0], data[1][1], data[1][2], data[1][3],
                       data[2][0], data[2][1], data[2][2], data[2][3],
                       data[3][0], data[3][1], data[3][2], data[3][3]);
  }

  std::array<std::array<T, 4>, 4> data;
};

template <typename T> Matrix4x4<T> transpose(const Matrix4x4<T> &m) {
  return Matrix4x4<T>(m.data[0][0], m.data[1][0], m.data[2][0], m.data[3][0],
                      m.data[0][1], m.data[1][1], m.data[2][1], m.data[3][1],
                      m.data[0][2], m.data[1][2], m.data[2][2], m.data[3][2],
                      m.data[0][3], m.data[1][3], m.data[2][3], m.data[3][3]);
}

template <typename T> Matrix4x4<T> inverse(const Matrix4x4<T> &m) {
  typename Matrix4x4<T>::size_type indxc[4], indxr[4];
  typename Matrix4x4<T>::size_type ipiv[4] = {0, 0, 0, 0};
  T minv[4][4];
  memcpy(minv, reinterpret_cast<const void *>(m.data.data()->data()),
         4 * 4 * sizeof(T));
  for (typename Matrix4x4<T>::size_type i = 0; i < 4; i++) {
    typename Matrix4x4<T>::size_type irow = 0, icol = 0;
    T big = 0.f;
    // Choose pivot
    for (typename Matrix4x4<T>::size_type j = 0; j < 4; j++) {
      if (ipiv[j] != 1) {
        for (typename Matrix4x4<T>::size_type k = 0; k < 4; k++) {
          if (ipiv[k] == 0) {
            if (std::abs(minv[j][k]) >= big) {
              big = T(std::abs(minv[j][k]));
              irow = j;
              icol = k;
            }
          } else if (ipiv[k] > 1)
            LERROR("Singular matrix in MatrixInvert");
        }
      }
    }
    ++ipiv[icol];
    // Swap rows _irow_ and _icol_ for pivot
    if (irow != icol) {
      for (typename Matrix4x4<T>::size_type k = 0; k < 4; ++k)
        std::swap(minv[irow][k], minv[icol][k]);
    }
    indxr[i] = irow;
    indxc[i] = icol;
    if (minv[icol][icol] == 0.f)
      LERROR("Singular matrix in MatrixInvert");

    // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
    T pivinv = 1. / minv[icol][icol];
    minv[icol][icol] = 1.;
    for (typename Matrix4x4<T>::size_type j = 0; j < 4; j++)
      minv[icol][j] *= pivinv;

    // Subtract this row from others to zero out their columns
    for (typename Matrix4x4<T>::size_type j = 0; j < 4; j++) {
      if (j != icol) {
        T save = minv[j][icol];
        minv[j][icol] = 0;
        for (typename Matrix4x4<T>::size_type k = 0; k < 4; k++)
          minv[j][k] -= minv[icol][k] * save;
      }
    }
  }
  // Swap columns to reflect permutation
  for (int j = 3; j >= 0; j--) {
    if (indxr[j] != indxc[j]) {
      for (typename Matrix4x4<T>::size_type k = 0; k < 4; k++)
        std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
    }
  }
  return Matrix4x4<T>(minv);
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix4x4<T> &m) {
  return out << m.fmt();
}

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_MATRIX_HPP_
