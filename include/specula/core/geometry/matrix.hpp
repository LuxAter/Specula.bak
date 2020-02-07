#ifndef SPECULA_CORE_GEOMETRY_MATRIX_HPP_
#define SPECULA_CORE_GEOMETRY_MATRIX_HPP_

#include "../../global.hpp"

namespace specula {
template <std::size_t R, std::size_t C, typename T,
          glm::qualifier Q = glm::defaultp>
class Matrix : public glm::mat<R, C, T, Q> {
public:
  typedef std::size_t size_type;

  template <typename... Args>
  Matrix(const Args &... args) : glm::mat<R, C, T, Q>(args...) {}

  template <std::size_t N = R, std::size_t M = C>
  typename std::enable_if<N == R && M == C && N == 2 && M == 2,
                          std::string>::type
  fmt() const {
    return fmt::format("[[{},{}],[{},{}]]", (*this)[0][0], (*this)[0][1],
                       (*this)[1][0], (*this)[1][1]);
  }
  template <std::size_t N = R, std::size_t M = C>
  typename std::enable_if<N == R && M == C && N == 2 && M == 3,
                          std::string>::type
  fmt() const {
    return fmt::format("[[{},{},{}],[{},{},{}]]", (*this)[0][0], (*this)[0][1],
                       (*this)[0][2], (*this)[1][0], (*this)[1][1],
                       (*this)[1][2]);
  }
  template <std::size_t N = R, std::size_t M = C>
  typename std::enable_if<N == R && M == C && N == 2 && M == 4,
                          std::string>::type
  fmt() const {
    return fmt::format("[[{},{},{},{}],[{},{},{},{}]]", (*this)[0][0],
                       (*this)[0][1], (*this)[0][2], (*this)[0][3],
                       (*this)[1][0], (*this)[1][1], (*this)[1][2],
                       (*this)[1][3]);
  }
  template <std::size_t N = R, std::size_t M = C>
  typename std::enable_if<N == R && M == C && N == 3 && M == 2,
                          std::string>::type
  fmt() const {
    return fmt::format("[[{},{}],[{},{}],[{},{}]]", (*this)[0][0],
                       (*this)[0][1], (*this)[1][0], (*this)[1][1],
                       (*this)[2][0], (*this)[2][1]);
  }
  template <std::size_t N = R, std::size_t M = C>
  typename std::enable_if<N == R && M == C && N == 3 && M == 3,
                          std::string>::type
  fmt() const {
    return fmt::format("[[{},{},{}],[{},{},{}],[{},{},{}]]", (*this)[0][0],
                       (*this)[0][1], (*this)[0][2], (*this)[1][0],
                       (*this)[1][1], (*this)[1][2], (*this)[2][0],
                       (*this)[2][1], (*this)[2][2]);
  }
  template <std::size_t N = R, std::size_t M = C>
  typename std::enable_if<N == R && M == C && N == 3 && M == 4,
                          std::string>::type
  fmt() const {
    return fmt::format("[[{},{},{},{}],[{},{},{},{}],[{},{},{},{}]]",
                       (*this)[0][0], (*this)[0][1], (*this)[0][2],
                       (*this)[0][3], (*this)[1][0], (*this)[1][1],
                       (*this)[1][2], (*this)[1][3], (*this)[2][0],
                       (*this)[2][1], (*this)[2][2], (*this)[2][3]);
  }
  template <std::size_t N = R, std::size_t M = C>
  typename std::enable_if<N == R && M == C && N == 4 && M == 2,
                          std::string>::type
  fmt() const {
    return fmt::format("[[{},{}],[{},{}],[{},{}],[{},{}]]", (*this)[0][0],
                       (*this)[0][1], (*this)[1][0], (*this)[1][1],
                       (*this)[2][0], (*this)[2][1], (*this)[3][0],
                       (*this)[3][1]);
  }
  template <std::size_t N = R, std::size_t M = C>
  typename std::enable_if<N == R && M == C && N == 4 && M == 3,
                          std::string>::type
  fmt() const {
    return fmt::format("[[{},{},{}],[{},{},{}],[{},{},{}],[{},{},{}]]",
                       (*this)[0][0], (*this)[0][1], (*this)[0][2],
                       (*this)[1][0], (*this)[1][1], (*this)[1][2],
                       (*this)[2][0], (*this)[2][1], (*this)[2][2],
                       (*this)[3][0], (*this)[3][1], (*this)[3][2]);
  }
  template <std::size_t N = R, std::size_t M = C>
  typename std::enable_if<N == R && M == C && N == 4 && M == 4,
                          std::string>::type
  fmt() const {
    return fmt::format(
        "[[{},{},{},{}],[{},{},{},{}],[{},{},{},{}],[{},{},{},{}]]",
        (*this)[0][0], (*this)[0][1], (*this)[0][2], (*this)[0][3],
        (*this)[1][0], (*this)[1][1], (*this)[1][2], (*this)[1][3],
        (*this)[2][0], (*this)[2][1], (*this)[2][2], (*this)[2][3],
        (*this)[3][0], (*this)[3][1], (*this)[3][2], (*this)[3][3]);
  }
};

template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix2 = Matrix<2, 2, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix3 = Matrix<3, 3, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix4 = Matrix<4, 4, T, Q>;

template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix2x2 = Matrix<2, 2, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix2x3 = Matrix<2, 3, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix2x4 = Matrix<2, 4, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix3x2 = Matrix<3, 2, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix3x3 = Matrix<3, 3, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix3x4 = Matrix<3, 4, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix4x2 = Matrix<4, 2, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix4x3 = Matrix<4, 3, T, Q>;
template <typename T, glm::qualifier Q = glm::defaultp>
using Matrix4x4 = Matrix<4, 4, T, Q>;

typedef Matrix<2, 2, Float> Matrix2f;
typedef Matrix<3, 3, Float> Matrix3f;
typedef Matrix<4, 4, Float> Matrix4f;
typedef Matrix<2, 2, Float> Matrix2x2f;
typedef Matrix<2, 3, Float> Matrix2x3f;
typedef Matrix<2, 4, Float> Matrix2x4f;
typedef Matrix<3, 2, Float> Matrix3x2f;
typedef Matrix<3, 3, Float> Matrix3x3f;
typedef Matrix<3, 4, Float> Matrix3x4f;
typedef Matrix<4, 2, Float> Matrix4x2f;
typedef Matrix<4, 3, Float> Matrix4x3f;
typedef Matrix<4, 4, Float> Matrix4x4f;
typedef Matrix<2, 2, Int> Matrix2i;
typedef Matrix<3, 3, Int> Matrix3i;
typedef Matrix<4, 4, Int> Matrix4i;
typedef Matrix<2, 2, Int> Matrix2x2i;
typedef Matrix<2, 3, Int> Matrix2x3i;
typedef Matrix<2, 4, Int> Matrix2x4i;
typedef Matrix<3, 2, Int> Matrix3x2i;
typedef Matrix<3, 3, Int> Matrix3x3i;
typedef Matrix<3, 4, Int> Matrix3x4i;
typedef Matrix<4, 2, Int> Matrix4x2i;
typedef Matrix<4, 3, Int> Matrix4x3i;
typedef Matrix<4, 4, Int> Matrix4x4i;

template <std::size_t R, std::size_t C, typename T, glm::qualifier Q>
std::ostream &operator<<(std::ostream &out, const Matrix<R, C, T, Q> &v) {
  return out << v.fmt();
}

} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_MATRIX_HPP_
