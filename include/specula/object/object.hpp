#ifndef SPECULA_OBJECT_HPP_
#define SPECULA_OBJECT_HPP_

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <variant>

#include <glm/glm.hpp>

#define ObjectOps(Obj)                                                         \
  inline virtual std::shared_ptr<Obj> translate(                               \
      const float &x, const float &y, const float &z) {                        \
    this->__translate(x, y, z);                                                \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> translate(const glm::vec3 &v) {          \
    this->__translate(v.x, v.y, v.z);                                          \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> rotate(                                  \
      const float &angle, const float &x, const float &y, const float &z) {    \
    this->__rotate(angle, x, y, z);                                            \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> rotate(const float &angle,               \
                                             const glm::vec3 &a) {             \
    this->__rotate(angle, a.x, a.y, a.z);                                      \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> rotate_x(const float &angle) {           \
    this->__rotate(angle, 1.0f, 0.0f, 0.0f);                                   \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> rotate_y(const float &angle) {           \
    this->__rotate(angle, 0.0f, 1.0f, 0.0f);                                   \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> rotate_z(const float &angle) {           \
    this->__rotate(angle, 0.0f, 0.0f, 1.0f);                                   \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> scale(const float &x, const float &y,    \
                                            const float &z) {                  \
    this->__scale(x, y, z);                                                    \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> scale(const glm::vec3 &s) {              \
    this->__scale(s.x, s.y, s.z);                                              \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> scale_x(const float &s) {                \
    this->__scale(s, 0.0f, 0.0f);                                              \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> scale_y(const float &s) {                \
    this->__scale(0.0f, s, 0.0f);                                              \
    return shared_from_this();                                                 \
  }                                                                            \
  inline virtual std::shared_ptr<Obj> scale_z(const float &s) {                \
    this->__scale(0.0f, 0.0f, s);                                              \
    return shared_from_this();                                                 \
  }

namespace specula {
class Object : public std::enable_shared_from_this<Object> {
public:
  typedef std::variant<float, glm::vec2, glm::vec3, glm::vec4> value_type;
  Object();
  Object(const std::function<float(const glm::vec3 &)> &sdf_func_,
         std::map<std::string, value_type> vars =
             std::map<std::string, value_type>());
  Object(const std::string &sdf_str_, std::map<std::string, value_type> vars =
                                          std::map<std::string, value_type>());
  Object(const std::function<float(const glm::vec3 &)> &sdf_func_,
         const std::string &sdf_str_,
         std::map<std::string, value_type> vars =
             std::map<std::string, value_type>());

  inline float sdf(const glm::vec3 &p) const {
    return sdf_func(inv * glm::vec4(p, 1.0f));
  }
  inline glm::vec3 normal(const glm::vec3 &p, const float &ep) const {
    glm::vec3 obj_p = inv * glm::vec4(p, 1.0f);
    return tran * glm::normalize(glm::vec4(
                      sdf_func(glm::vec3(obj_p.x + ep, obj_p.y, obj_p.z)) -
                          sdf_func(glm::vec3(obj_p.x - ep, obj_p.y, obj_p.z)),
                      sdf_func(glm::vec3(obj_p.x, obj_p.y + ep, obj_p.z)) -
                          sdf_func(glm::vec3(obj_p.x, obj_p.y - ep, obj_p.z)),
                      sdf_func(glm::vec3(obj_p.x, obj_p.y, obj_p.z + ep)) -
                          sdf_func(glm::vec3(obj_p.x, obj_p.y, obj_p.z - ep)),
                      0.0f));
  }

  inline bool gpu_enabled() const { return sdf_str.size() != 0; }
  inline bool cpu_enabled() const { return sdf_func != nullptr; }

  inline const unsigned long &get_uuid() const { return uuid; }
  inline std::function<float(const glm::vec3 &)> &get_sdf_func() {
    return sdf_func;
  }
  inline const std::function<float(const glm::vec3 &)> &get_sdf_func() const {
    return sdf_func;
  }
  inline std::string &get_sdf_str() { return sdf_str; }
  inline const std::string &get_sdf_str() const { return sdf_str; }

  inline value_type &get(const std::string &name) { return variables[name]; }
  inline const value_type &get(const std::string &name) const {
    return variables.at(name);
  }

  ObjectOps(Object);

protected:
  void __translate(const float &x, const float &y, const float &z);
  void __rotate(const float &angle, const float &x, const float &y,
                const float &z);
  void __scale(const float &x, const float &y, const float &z);

  unsigned long uuid;
  std::function<float(const glm::vec3 &)> sdf_func;
  std::string sdf_str;
  std::map<std::string, value_type> variables;

  glm::mat4 tran, inv;
};
} // namespace specula

#endif
