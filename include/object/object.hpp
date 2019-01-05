#ifndef SPECULA_OBJECT_OBJECT_HPP_
#define SPECULA_OBJECT_OBJECT_HPP_

#include <limits>
#include <memory>

#include "../math/math.hpp"
#include "material.hpp"

namespace specula {
namespace object {
  class Object {
   public:
    Object();
    explicit Object(Material mat);
    virtual ~Object();
    void Translate(const math::Vec3d& pos);

    virtual double DE(const math::Vec3d& p);

    Material material_;
    math::Mat4d mat_, mat_inv_;
  };

  std::unique_ptr<Object> GenerateObject(Material mat = Material());
}  // namespace object
}  // namespace specula

#endif  // SPECULA_OBJECT_OBJECT_HPP_
