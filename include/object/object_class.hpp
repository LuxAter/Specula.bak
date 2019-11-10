#ifndef SPECULA_OBJECT_CLASS_HPP_
#define SPECULA_OBJECT_CLASS_HPP_

#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../log.hpp"
#include "../material/material.hpp"

namespace specula {
namespace object {
class Object {
public:
  Object(const std::function<float(const glm::vec3 &)> &dst)
      : mat_(nullptr), dst_(dst), trans_(1.0f), trans_inv_(1.0f) {}

  virtual ~Object() {}

  inline float distance(const glm::vec3 &p) const {
    return this->dst_(glm::vec3(this->trans_inv_ * glm::vec4(p, 1.0f)));
  }
  inline glm::vec3 normal(const glm::vec3 &p, const float &ep) const {
    glm::vec3 obj_p = this->trans_inv_ * glm::vec4(p, 1.0f);
    return glm::normalize(
        glm::vec3(this->dst_(glm::vec3(obj_p.x + ep, obj_p.y, obj_p.z)) -
                      this->dst_(glm::vec3(obj_p.x - ep, obj_p.y, obj_p.z)),
                  this->dst_(glm::vec3(obj_p.x, obj_p.y + ep, obj_p.z)) -
                      this->dst_(glm::vec3(obj_p.x, obj_p.y - ep, obj_p.z)),
                  this->dst_(glm::vec3(obj_p.x, obj_p.y, obj_p.z + ep)) -
                      this->dst_(glm::vec3(obj_p.x, obj_p.y, obj_p.z - ep))));
  }

  // inline Object &set_material(const std::shared_ptr<material::Material> &mat)
  // {
  //   mat_ = mat;
  //   return *this;
  // }
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
    trans_ = glm::translate(trans_, glm::vec3(x, y, z));
    trans_inv_ = glm::translate(trans_inv_, glm::vec3(-x, -y, -z));
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

protected:
  std::function<float(const glm::vec3 &)> dst_;
  glm::mat4 trans_, trans_inv_;

private:
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_CLASS_HPP_
