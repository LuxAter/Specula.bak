#ifndef SPECULA_FORWARD_DECLARATIONS_HPP_
#define SPECULA_FORWARD_DECLARATIONS_HPP_

#include "math.hpp"

namespace specula {
template <typename T, glm::qualifier Q> class Quaternion;
template <std::size_t N, typename T, glm::qualifier Q> class Vector;
template <std::size_t N, typename T, glm::qualifier Q> class Point;
template <std::size_t N, typename T, glm::qualifier Q> class Normal;
template <std::size_t R, std::size_t C, typename T, glm::qualifier Q>
class Matrix;

template <typename T> class Bounds4;
template <typename T> class Bounds3;
template <typename T> class Bounds2;

class Ray;
class RayDifferential;
} // namespace specula

#endif // SPECULA_FORWARD_DECLARATIONS_HPP_