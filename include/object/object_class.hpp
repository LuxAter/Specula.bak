#ifndef SPECULA_OBJECT_CLASS_HPP_
#define SPECULA_OBJECT_CLASS_HPP_

#include <cstdlib>
#include <functional>
#include <map>
#include <memory>
#include <string>

#include "../math.hpp"
#include "../shader/material.hpp"
#include "../variant.hpp"

#define ObjectOperators(OBJ)                                                   \
  template <typename... ARGS>                                                  \
  inline std::shared_ptr<OBJ> set_material(const ARGS &... args) {             \
    this->__set_material(args...);                                             \
    return shared_from_this();                                                 \
  }                                                                            \
  template <typename... ARGS>                                                  \
  inline std::shared_ptr<OBJ> translate(const ARGS &... args) {                \
    this->__translate(args...);                                                \
    return shared_from_this();                                                 \
  }                                                                            \
  template <typename... ARGS>                                                  \
  inline std::shared_ptr<OBJ> rotate(const ARGS &... args) {                   \
    this->__rotate(args...);                                                   \
    return shared_from_this();                                                 \
  }                                                                            \
  template <typename... ARGS>                                                  \
  inline std::shared_ptr<OBJ> scale(const ARGS &... args) {                    \
    this->__scale(args...);                                                    \
    return shared_from_this();                                                 \
  }

namespace specula {
class ObjectBase {
public:
  ObjectBase();
  ObjectBase(const std::function<float(const glm::vec3 &)> &distance_function);
  ObjectBase(const std::string &distance_function);
  ObjectBase(const std::function<float(const glm::vec3 &)> &distance_function,
             const std::string &distance_function_src);
  ObjectBase(
      const std::function<float(const glm::vec3 &)> &distance_function,
      const std::map<std::string,
                     variant<float *, glm::vec2 *, glm::vec3 *, glm::vec4 *>>
          &variables);
  ObjectBase(
      const std::string &distance_function,
      const std::map<std::string,
                     variant<float *, glm::vec2 *, glm::vec3 *, glm::vec4 *>>
          &variables);
  ObjectBase(
      const std::function<float(const glm::vec3 &)> &distance_function,
      const std::string &distance_function_src,
      const std::map<std::string,
                     variant<float *, glm::vec2 *, glm::vec3 *, glm::vec4 *>>
          &variables);
  virtual ~ObjectBase() {}

  inline bool gpu_enabled() const {
    return distance_estimator_src.length() != 0;
  }
  inline bool cpu_enabled() const { return distance_estimator != nullptr; }

  inline float &get_float(const std::string &name) {
    return *std::get<float *>(variables.at(name));
  }
  inline const float &get_float(const std::string &name) const {
    return *std::get<float *>(variables.at(name));
  }

  inline void __set_material(const Material &mat) {
    this->material = std::make_shared<Material>(mat);
  }

  inline void __translate(const float &x, const float &y, const float &z) {
    this->transform = glm::translate(this->transform, {x, y, z});
    this->inverse_transform =
        glm::translate(this->inverse_transform, {-x, -y, -z});
  }
  inline void __translate(const glm::vec3 &v) {
    this->transform = glm::translate(this->transform, v);
    this->inverse_transform = glm::translate(this->inverse_transform, -v);
  }
  inline void __rotate(const float &angle, const float &x, const float &y,
                       const float &z) {
    const glm::vec3 axis = glm::normalize(glm::vec3{x, y, z});
    this->transform = glm::rotate(this->transform, angle, axis);
    this->inverse_transform =
        glm::rotate(this->inverse_transform, -angle, axis);
  }
  inline void __rotate(const float &angle, const glm::vec3 &axis) {
    const glm::vec3 axis_norm = glm::normalize(axis);
    this->transform = glm::rotate(this->transform, angle, axis_norm);
    this->inverse_transform =
        glm::rotate(this->inverse_transform, -angle, axis_norm);
  }
  inline void __scale(const float &x, const float &y, const float &z) {
    this->transform = glm::scale(this->transform, {x, y, z});
    this->inverse_transform =
        glm::scale(this->inverse_transform, {1.0f / x, 1.0f / y, 1.0f / z});
  }

  std::size_t uuid;
  std::function<float(const glm::vec3 &)> distance_estimator;
  std::string distance_estimator_src;
  std::map<std::string, variant<float *, glm::vec2 *, glm::vec3 *, glm::vec4 *>>
      variables;

  std::shared_ptr<Material> material;

  glm::mat4 transform, inverse_transform;
};
} // namespace specula

#endif // SPECULA_OBJECT_CLASS_HPP_
