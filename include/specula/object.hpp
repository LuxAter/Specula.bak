#ifndef SPECULA_OBJECT_HPP_
#define SPECULA_OBJECT_HPP_

#include <functional>
#include <memory>
#include <unordered_map>
#include <variant>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "log.hpp"

namespace specula {
class Object : public std::enable_shared_from_this<Object> {
public:
  typedef std::unordered_map<std::string, std::variant<float, glm::vec3>>
      variables_type;
  Object(
      const std::function<float(const Object *, const glm::vec3 &)> &sdf_func);
  Object(
      const std::function<float(const Object *, const glm::vec3 &)> &sdf_func,
      const std::unordered_map<std::string, std::variant<float, glm::vec3>>
          &vars);

  inline float distance(const glm::vec3 &p) {
    return this->sdf(this, glm::vec3(this->inv * glm::vec4(p, 1.0f)));
  }

  inline void set(const std::string &key,
                  const std::variant<float, glm::vec3> &val) {
    variables[key] = val;
  }
  inline float &getf(const std::string &key) {
    return std::get<float>(variables[key]);
  }
  inline const float &getf(const std::string &key) const {
    return std::get<float>(variables.at(key));
  }
  inline glm::vec3 &get3(const std::string &key) {
    return std::get<glm::vec3>(variables[key]);
  }
  inline const glm::vec3 &get3(const std::string &key) const {
    return std::get<glm::vec3>(variables.at(key));
  }

  inline std::shared_ptr<Object> rotate(const float &angle,
                                        const glm::vec3 &axis) {
    rot = glm::rotate(rot, angle, axis);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> translate(const glm::vec3 &xyz) {
    trans += xyz;
    return shared_from_this();
  }
  inline std::shared_ptr<Object> translate(const float &x, const float &y,
                                           const float &z) {
    trans += glm::vec3{x, y, z};
    return shared_from_this();
  }
  inline void construct() {
    mat = glm::translate(rot, trans);
    inv = glm::translate(glm::inverse(rot), -trans);
  }
  std::size_t uuid;

private:
  glm::mat4 mat, inv;
  glm::mat4 rot;
  glm::vec3 trans;
  std::function<float(const Object *, const glm::vec3 &)> sdf;
  std::unordered_map<std::string, std::variant<float, glm::vec3>> variables;
};
} // namespace specula

#endif // SPECULA_OBJECT_HPP_
