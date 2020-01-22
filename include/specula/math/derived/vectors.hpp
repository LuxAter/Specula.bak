#ifndef SPECULA_VECTORS_HPP_
#define SPECULA_VECTORS_HPP_

#include <cmath>

#include "../vector/vector2.hpp"
#include "../vector/vector3.hpp"
#include "../vector/vector4.hpp"

namespace specula {
template <typename T> class Vector2 : public Vector2Base<T> {
  T length_squared() const { return this->x * this->x + this->y * this->y; }
  T length() const { return std::sqrt(this->length_squared()); }
};
template <typename T> class Vector3 : public Vector3Base<T> {
  T length_squared() const {
    return this->x * this->x + this->y * this->y + this->z * this->z;
  }
  T length() const { return std::sqrt(this->length_squared()); }
};
template <typename T> class Vector4 : public Vector4Base<T> {
  T length_squared() const {
    return this->x * this->x + this->y * this->y + this->z * this->z +
           this->w * this->w;
  }
  T length() const { return std::sqrt(this->length_squared()); }
};
} // namespace specula

#endif // SPECULA_VECTORS_HPP_
