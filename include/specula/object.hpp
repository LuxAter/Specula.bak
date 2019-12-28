#ifndef SPECULA_OBJECT_HPP_
#define SPECULA_OBJECT_HPP_

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <variant>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

#include "shader/material.hpp"

namespace specula {
class Object : public std::enable_shared_from_this<Object> {
public:
  typedef std::variant<float, glm::vec2, glm::vec3, glm::vec4> value_type;
  Object();
  Object(
      const std::function<float(const Object *, const glm::vec3 &)> &sdf_func_,
      std::map<std::string, value_type> vars =
          std::map<std::string, value_type>());
  Object(const std::string &sdf_str_, std::map<std::string, value_type> vars =
                                          std::map<std::string, value_type>());
  Object(
      const std::function<float(const Object *, const glm::vec3 &)> &sdf_func_,
      const std::string &sdf_str_,
      std::map<std::string, value_type> vars =
          std::map<std::string, value_type>());

  inline float sdf(const glm::vec3 &p) const {
    return sdf_func(this, inv * glm::vec4(p, 1.0f));
  }
  std::string gen_sdf(const float &ep) const;

  inline glm::vec3 normal(const glm::vec3 &p, const float &ep) const {
    glm::vec3 obj_p = inv * glm::vec4(p, 1.0f);
    return tran *
           glm::normalize(glm::vec4(
               sdf_func(this, glm::vec3(obj_p.x + ep, obj_p.y, obj_p.z)) -
                   sdf_func(this, glm::vec3(obj_p.x - ep, obj_p.y, obj_p.z)),
               sdf_func(this, glm::vec3(obj_p.x, obj_p.y + ep, obj_p.z)) -
                   sdf_func(this, glm::vec3(obj_p.x, obj_p.y - ep, obj_p.z)),
               sdf_func(this, glm::vec3(obj_p.x, obj_p.y, obj_p.z + ep)) -
                   sdf_func(this, glm::vec3(obj_p.x, obj_p.y, obj_p.z - ep)),
               0.0f));
  }

  inline bool gpu_enabled() const { return sdf_str.size() != 0; }
  inline bool cpu_enabled() const { return sdf_func != nullptr; }

  inline const unsigned long &get_uuid() const { return uuid; }
  inline std::function<float(const Object *, const glm::vec3 &)> &
  get_sdf_func() {
    return sdf_func;
  }
  inline const std::function<float(const Object *, const glm::vec3 &)> &
  get_sdf_func() const {
    return sdf_func;
  }
  inline std::string &get_sdf_str() { return sdf_str; }
  inline const std::string &get_sdf_str() const { return sdf_str; }

  inline value_type &get(const std::string &name) { return variables[name]; }
  inline const value_type &get(const std::string &name) const {
    return variables.at(name);
  }
  inline void set(const std::string &name, const value_type &val) {
    variables[name] = val;
  }
  inline float &getf(const std::string &name) {
    return std::get<float>(variables.at(name));
  }
  inline const float &getf(const std::string &name) const {
    return std::get<float>(variables.at(name));
  }
  inline const glm::vec2 &get2(const std::string &name) const {
    return std::get<glm::vec2>(variables.at(name));
  }
  inline const glm::vec3 &get3(const std::string &name) const {
    return std::get<glm::vec3>(variables.at(name));
  }
  inline const glm::vec4 &get4(const std::string &name) const {
    return std::get<glm::vec4>(variables.at(name));
  }

  inline std::shared_ptr<Object> translate(const float &x, const float &y,
                                           const float &z) {
    this->__translate(x, y, z);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> translate(const glm::vec3 &v) {
    this->__translate(v.x, v.y, v.z);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> rotate(const float &angle, const float &x,
                                        const float &y, const float &z) {
    this->__rotate(angle, x, y, z);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> rotate(const float &angle,
                                        const glm::vec3 &a) {
    this->__rotate(angle, a.x, a.y, a.z);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> rotate_x(const float &angle) {
    this->__rotate(angle, 1.0f, 0.0f, 0.0f);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> rotate_y(const float &angle) {
    this->__rotate(angle, 0.0f, 1.0f, 0.0f);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> rotate_z(const float &angle) {
    this->__rotate(angle, 0.0f, 0.0f, 1.0f);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> scale(const float &x, const float &y,
                                       const float &z) {
    this->__scale(x, y, z);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> scale(const glm::vec3 &s) {
    this->__scale(s.x, s.y, s.z);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> scale_x(const float &s) {
    this->__scale(s, 0.0f, 0.0f);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> scale_y(const float &s) {
    this->__scale(0.0f, s, 0.0f);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> scale_z(const float &s) {
    this->__scale(0.0f, 0.0f, s);
    return shared_from_this();
  }
  inline std::shared_ptr<Object> set_material(Material &mat) {
    this->material = mat.shared_from_this();
    return shared_from_this();
  }
  inline std::shared_ptr<Object>
  set_material(const std::shared_ptr<Material> &mat) {
    this->material = mat;
    return shared_from_this();
  }

  unsigned long uuid;
  std::map<std::string, value_type> variables;
  std::shared_ptr<Material> material;

protected:
  void __translate(const float &x, const float &y, const float &z);
  void __rotate(const float &angle, const float &x, const float &y,
                const float &z);
  void __scale(const float &x, const float &y, const float &z);

  std::string gpu_format(const std::string &key) const;
  static std::string gpu_format(const float &val, const std::string &ext);
  static std::string gpu_format(const glm::vec2 &val, const std::string &ext);
  static std::string gpu_format(const glm::vec3 &val, const std::string &ext);
  static std::string gpu_format(const glm::vec4 &val, const std::string &ext);
  static std::string gpu_matrix(const glm::mat4 &v);

  std::function<float(const Object *, const glm::vec3 &)> sdf_func;
  std::string sdf_str;

  glm::mat4 tran, inv;
};
} // namespace specula

#endif
