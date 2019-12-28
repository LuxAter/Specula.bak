#include "specula/object.hpp"

#include <functional>
#include <map>
#include <memory>
#include <regex>
#include <stdexcept>
#include <string>
#include <variant>

#include <fmt/format.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "specula/log.hpp"
#include "specula/rand.hpp"

#include "kernels.hpp"

specula::Object::Object()
    : uuid(ulrand()), variables(), material(nullptr), sdf_func(nullptr),
      sdf_str(), tran(1.0f), inv(1.0f) {}
specula::Object::Object(
    const std::function<float(const Object *, const glm::vec3 &)> &sdf_func_,
    std::map<std::string, value_type> vars)
    : uuid(ulrand()), variables(vars), material(nullptr), sdf_func(sdf_func_),
      sdf_str(), tran(1.0f), inv(1.0f) {}
specula::Object::Object(const std::string &sdf_str_,
                        std::map<std::string, value_type> vars)
    : uuid(ulrand()), variables(vars), material(nullptr), sdf_func(nullptr),
      sdf_str(sdf_str_), tran(1.0f), inv(1.0f) {}
specula::Object::Object(
    const std::function<float(const Object *, const glm::vec3 &)> &sdf_func_,
    const std::string &sdf_str_, std::map<std::string, value_type> vars)
    : uuid(ulrand()), variables(vars), material(nullptr), sdf_func(sdf_func_),
      sdf_str(sdf_str_), tran(1.0f), inv(1.0f) {}

std::string specula::Object::gen_sdf(const float &ep) const {
  std::string sdf_src = this->sdf_str;
  while (sdf_src.find("{{") != std::string::npos) {
    std::string::size_type start = sdf_src.find("{{");
    std::string::size_type len = sdf_src.find("}}") - start;
    sdf_src.replace(sdf_src.begin() + start, sdf_src.begin() + start + len + 2,
                    gpu_format(sdf_src.substr(start + 2, len - 2)));
  }
  std::string gpu_sdf =
      fmt::format(gpu_sdf_kernel, this->uuid, gpu_matrix(this->inv), sdf_src);
  std::string gpu_norm =
      fmt::format(gpu_normal_kernel, this->uuid, gpu_matrix(this->inv),
                  gpu_matrix(this->tran), ep);
  return gpu_sdf + gpu_norm;
}

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

std::string specula::Object::gpu_format(const std::string &key) const {
  std::string::size_type start = key.find_first_not_of(' ');
  std::string::size_type end = key.find_last_not_of(' ') + 1;
  std::string::size_type sep =
      ((key.find_last_of('.') != std::string::npos) ? key.find_last_of('.')
                                                    : end);
  std::string name = key.substr(start, sep - start);
  std::string ext = key.substr(sep + 1, end - sep);
  std::map<std::string, value_type>::const_iterator it;
  if ((it = variables.find(name)) != variables.end()) {
    if (std::holds_alternative<float>(it->second)) {
      return gpu_format(std::get<float>(it->second), ext);
    } else if (std::holds_alternative<glm::vec2>(it->second)) {
      return gpu_format(std::get<glm::vec2>(it->second), ext);
    } else if (std::holds_alternative<glm::vec3>(it->second)) {
      return gpu_format(std::get<glm::vec3>(it->second), ext);
    } else if (std::holds_alternative<glm::vec4>(it->second)) {
      return gpu_format(std::get<glm::vec4>(it->second), ext);
    }
  } else {
    throw std::domain_error("Key: " + name + " is not a declared variable");
  }
  return "";
}
std::string specula::Object::gpu_format(const float &val,
                                        const std::string &ext) {
  if (ext.size() != 0) {
    throw std::domain_error("float type cannot swizzle");
  } else {
    return fmt::format("{}", val);
  }
}
std::string specula::Object::gpu_format(const glm::vec2 &val,
                                        const std::string &ext) {
  if (ext.size() != 0) {
    return fmt::format("(float2)({}, {}).{}", val.x, val.y, ext);
  } else {
    return fmt::format("(float2)({}, {})", val.x, val.y);
  }
}
std::string specula::Object::gpu_format(const glm::vec3 &val,
                                        const std::string &ext) {
  if (ext.size() != 0) {
    return fmt::format("(float3)({}, {}, {}).{}", val.x, val.y, val.z, ext);
  } else {
    return fmt::format("(float3)({}, {}, {})", val.x, val.y, val.z);
  }
}
std::string specula::Object::gpu_format(const glm::vec4 &val,
                                        const std::string &ext) {
  if (ext.size() != 0) {
    return fmt::format("(float4)({}, {}, {}, {}).{}", val.x, val.y, val.z,
                       val.w, ext);
  } else {
    return fmt::format("(float4)({}, {}, {}, {})", val.x, val.y, val.z, val.w);
  }
}
std::string specula::Object::gpu_matrix(const glm::mat4 &v) {
  return fmt::format("(float16)({}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, "
                     "{}, {}, {}, {}, {})",
                     v[0][0], v[0][1], v[0][2], v[0][3], v[1][0], v[1][1],
                     v[1][2], v[1][3], v[2][0], v[2][1], v[2][2], v[2][3],
                     v[3][0], v[3][1], v[3][2], v[3][3]);
}
