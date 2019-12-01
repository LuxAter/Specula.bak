#ifndef SPECULA_OBJECT_CLASS_HPP_
#define SPECULA_OBJECT_CLASS_HPP_

#include <cstdlib>
#include <functional>
#include <memory>
#include <string>

#include "../material/material_class.hpp"
#include "../math.hpp"

namespace specula {
class ObjectBase {
public:
  ObjectBase();
  ObjectBase(const std::function<float(const glm::vec3 &)> &distance_function);
  ObjectBase(const std::string &distance_function);
  ObjectBase(const std::function<float(const glm::vec3 &)> &distance_function,
             const std::string &distance_function_src);
  virtual ~ObjectBase() {}

  inline ObjectBase &translate(const float &x, const float &y, const float &z) {
    transform = glm::translate(transform, {x, y, z});
    inverse_transform = glm::translate(inverse_transform, {-x, -y, -z});
    return *this;
  }
  inline ObjectBase &translate(const glm::vec3 &v) {
    transform = glm::translate(transform, v);
    inverse_transform = glm::translate(inverse_transform, -v);
    return *this;
  }
  inline ObjectBase &rotate(const float &angle, const float &x, const float &y,
                            const float &z) {
    const glm::vec3 axis = glm::normalize(glm::vec3{x, y, z});
    transform = glm::rotate(transform, angle, axis);
    inverse_transform = glm::rotate(inverse_transform, -angle, axis);
    return *this;
  }
  inline ObjectBase &rotate(const float &angle, const glm::vec3 &axis) {
    const glm::vec3 axis_norm = glm::normalize(axis);
    transform = glm::rotate(transform, angle, axis_norm);
    inverse_transform = glm::rotate(inverse_transform, -angle, axis_norm);
    return *this;
  }
  inline ObjectBase &scale(const float &x, const float &y, const float &z) {
    transform = glm::scale(transform, {x, y, z});
    inverse_transform =
        glm::scale(inverse_transform, {1.0f / x, 1.0f / y, 1.0f / z});
    return *this;
  }

  std::size_t uuid;
  std::function<float(const glm::vec3 &)> distance_estimator;
  std::string distance_estimator_src;

  std::shared_ptr<Material> material;

  glm::mat4 transform, inverse_transform;
};
} // namespace specula

#endif // SPECULA_OBJECT_CLASS_HPP_
