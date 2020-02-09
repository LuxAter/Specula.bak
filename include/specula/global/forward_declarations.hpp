#ifndef SPECULA_FORWARD_DECLARATIONS_HPP_
#define SPECULA_FORWARD_DECLARATIONS_HPP_

namespace specula {

template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Vector2;
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Vector3;
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Point2;
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Point3;
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Normal2;
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Normal3;

template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Matrix4x4;

template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Bounds2;
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
class Bounds3;

class Ray;
class RayDifferential;
class Medium;
} // namespace specula

#endif // SPECULA_FORWARD_DECLARATIONS_HPP_
