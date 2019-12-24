#include "specula/object/object.hpp"

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <variant>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "specula/rand.hpp"

specula::Object::Object()
    : uuid(ulrand()), sdf_func(nullptr), sdf_str(), variables(), tran(1.0f),
      inv(1.0f) {}

specula::Object::Object(
    const std::function<float(const glm::vec3 &)> &sdf_func_,
    std::map<std::string, value_type> vars)
    : uuid(ulrand()), sdf_func(sdf_func_), sdf_str(), variables(vars),
      tran(1.0f), inv(1.0f) {}
specula::Object::Object(const std::string &sdf_str_,
                        std::map<std::string, value_type> vars)
    : uuid(ulrand()), sdf_func(nullptr), sdf_str(sdf_str_), variables(vars),
      tran(1.0f), inv(1.0f) {}
specula::Object::Object(
    const std::function<float(const glm::vec3 &)> &sdf_func_,
    const std::string &sdf_str_, std::map<std::string, value_type> vars)
    : uuid(ulrand()), sdf_func(sdf_func_), sdf_str(sdf_str_), variables(vars),
      tran(1.0f), inv(1.0f) {}
void specula::Object::__translate(const float &x, const float &y,
                                 const float &z) {
  tran = glm::translate(tran, {x, y, z});
  inv = glm::translate(inv, {-x, -y, -z});
}
void specula::Object::__rotate(const float &angle, const float &x,
                               const float &y, const float &z) {
  glm::vec3 axis = glm::normalize(glm::vec3{x, y, z});
  tran = glm::rotate(tran, angle, axis);
  inv = glm::rotate(inv, -angle, axis);
}
void specula::Object::__scale(const float &x, const float &y, const float &z) {
  tran = glm::scale(tran, {x, y, z});
  inv = glm::scale(tran, {1.0f / x, 1.0f / y, 1.0f / z});
}
