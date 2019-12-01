#ifndef SPECULA_OBJECT_CLASS_HPP_
#define SPECULA_OBJECT_CLASS_HPP_

#include <functional>
#include <map>
#include <string>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../log.hpp"
#include "../material/material.hpp"
#include "../rand.hpp"
#include "../ray.hpp"
#include "../variant.hpp"

namespace specula {
namespace object {
class Object {
public:
  Object(const std::function<float(const glm::vec3 &p)> &dst,
         const std::string &src)
      : mat_(nullptr), vars_(), dst_(dst), src_(src), trans_(1.0f),
        trans_inv_(1.0f), uuid_(rand::urand()) {}
  Object(const std::function<float(const glm::vec3 &p)> &dst,
         const std::string &src,
         const std::map<std::string,
                        variant<float *, glm::vec2 *, glm::vec3 *, glm::vec4 *>>
             &vars)
      : mat_(nullptr), vars_(vars), dst_(dst), src_(src), trans_(1.0f),
        trans_inv_(1.0f), uuid_(rand::urand()) {}

  virtual ~Object() {}

  inline float distance(const glm::vec3 &p) const {
    return this->dst_(glm::vec3(this->trans_inv_ * p));
  }
  inline glm::vec3 calculate_normal(const glm::vec4 &p, const float &ep) const {
    glm::vec3 obj_p = this->trans_inv_ * p;
    return this->trans_ *
           glm::normalize(glm::vec3(
               this->dst_(glm::vec3(obj_p.x + ep, obj_p.y, obj_p.z)) -
                   this->dst_(glm::vec3(obj_p.x - ep, obj_p.y, obj_p.z)),
               this->dst_(glm::vec3(obj_p.x, obj_p.y + ep, obj_p.z)) -
                   this->dst_(glm::vec3(obj_p.x, obj_p.y - ep, obj_p.z)),
               this->dst_(glm::vec3(obj_p.x, obj_p.y, obj_p.z + ep)) -
                   this->dst_(glm::vec3(obj_p.x, obj_p.y, obj_p.z - ep))));
  }
  inline std::string construct_kernel() const {
    return "float distance_" + std::to_string(uuid_) +
           "(const float3& pt) { const float3 p = (float3)(" +
           std::to_string(this->trans_inv_[0][0]) + "*pt.x+" +
           std::to_string(this->trans_inv_[1][0]) + "*pt.y+" +
           std::to_string(this->trans_inv_[2][0]) + "*pt.z+" +
           std::to_string(this->trans_inv_[3][0]) + "," +
           std::to_string(this->trans_inv_[0][1]) + "*pt.x+" +
           std::to_string(this->trans_inv_[1][1]) + "*pt.y+" +
           std::to_string(this->trans_inv_[2][1]) + "*pt.z+" +
           std::to_string(this->trans_inv_[3][1]) + "," +
           std::to_string(this->trans_inv_[0][2]) + "*pt.x+" +
           std::to_string(this->trans_inv_[1][2]) + "*pt.y+" +
           std::to_string(this->trans_inv_[2][2]) + "*pt.z+" +
           std::to_string(this->trans_inv_[3][2]) + ");" +
           this->construct_func() + " }\n";
  }

  virtual inline std::string construct_func() const {
    std::string res = src_;
    for (auto &it : vars_) {
      std::size_t pos = std::string::npos;
      while ((pos = res.find("{{ " + it.first + " }}")) != std::string::npos) {
        res.replace(
            pos, it.first.size() + 6,
            visit(
                [](auto &&arg) {
                  using T = std::decay_t<decltype(arg)>;
                  if constexpr (std::is_same_v<T, float *>)
                    return std::to_string(*arg);
                  else if constexpr (std::is_same_v<T, glm::vec2 *>)
                    return fmt::format("(float2)({},{})", (*arg).x, (*arg).y);
                  else if constexpr (std::is_same_v<T, glm::vec3 *>)
                    return fmt::format("(float3)({},{},{})", (*arg).x, (*arg).y,
                                       (*arg).z);
                  else if constexpr (std::is_same_v<T, glm::vec4 *>)
                    return fmt::format("(float4)({},{},{},{})", (*arg).x,
                                       (*arg).y, (*arg).z, (*arg).w);
                },
                it.second));
      }
    }
    return res;
  }

  inline void set(const std::string &name, const float &v) {
    *(std::get<float *>(vars_[name])) = v;
  }
  inline void set(const std::string &name, const glm::vec2 &v) {
    *(std::get<glm::vec2 *>(vars_[name])) = v;
  }
  inline void set(const std::string &name, const glm::vec3 &v) {
    *(std::get<glm::vec3 *>(vars_[name])) = v;
  }
  inline void set(const std::string &name, const glm::vec4 &v) {
    *(std::get<glm::vec4 *>(vars_[name])) = v;
  }
  inline float get_float_v(const std::string &name) {
    return *std::get<float *>(vars_[name]);
  }
  inline glm::vec2 get_vec2_v(const std::string &name) {
    return *std::get<glm::vec2 *>(vars_[name]);
  }
  inline glm::vec3 get_vec3_v(const std::string &name) {
    return *std::get<glm::vec3 *>(vars_[name]);
  }
  inline glm::vec4 get_vec4_v(const std::string &name) {
    return *std::get<glm::vec4 *>(vars_[name]);
  }

  inline Object &set_material(const material::Material &mat) {
    mat_ = std::make_shared<material::Material>(mat.type, mat.base_color,
                                                mat.emission, mat.ior);
    return *this;
  }

  inline Object &rotate_x(const float &angle) {
    trans_ = glm::rotate(trans_, angle, glm::vec3(1.0, 0.0, 0.0));
    trans_inv_ = glm::rotate(trans_inv_, -angle, glm::vec3(1.0, 0.0, 0.0));
    return *this;
  }
  inline Object &rotate_y(const float &angle) {
    trans_ = glm::rotate(trans_, angle, glm::vec3(0.0, 1.0, 0.0));
    trans_inv_ = glm::rotate(trans_inv_, -angle, glm::vec3(0.0, 1.0, 0.0));
    return *this;
  }
  inline Object &rotate_z(const float &angle) {
    trans_ = glm::rotate(trans_, angle, glm::vec3(0.0, 0.0, 1.0));
    trans_inv_ = glm::rotate(trans_inv_, -angle, glm::vec3(0.0, 0.0, 1.0));
    return *this;
  }
  inline Object &translate(const float &x, const float &y, const float &z) {
    trans_ = glm::translate(trans_, glm::vec3(-x, -y, -z));
    trans_inv_ = glm::translate(trans_inv_, glm::vec3(x, y, z));
    return *this;
  }
  inline Object &scale_uniform(const float &s) {
    trans_ = glm::scale(trans_, glm::vec3(s, s, s));
    trans_inv_ = glm::scale(trans_inv_, glm::vec3(1.0 / s, 1.0 / s, 1.0 / s));
    return *this;
  }
  inline Object &scale(const float &x, const float &y, const float &z) {
    trans_ = glm::scale(trans_, glm::vec3(x, y, z));
    trans_inv_ = glm::scale(trans_inv_, glm::vec3(1.0 / x, 1.0 / y, 1.0 / z));
    return *this;
  }

  std::shared_ptr<material::Material> mat_;

  std::map<std::string, variant<float *, glm::vec2 *, glm::vec3 *, glm::vec4 *>>
      vars_;

private:
  std::function<float(const glm::vec3 &p)> dst_;
  std::string src_;

  glm::mat4 trans_, trans_inv_;
  std::size_t uuid_;
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_CLASS_HPP_
