#ifndef SPECULA_OBJECT_CLASS_HPP_
#define SPECULA_OBJECT_CLASS_HPP_

#include <functional>

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace specula {
namespace object {
class Object {
public:
  Object(const std::function<float(const glm::vec3 &)> &dst)
      : dst_(dst), trans_(1.0), trans_inv_(1.0) {}

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
  inline Object &translate(const float& x, const float& y, const float& z) {
    trans_ = glm::translate(trans_, glm::vec3(x, y, z));
    trans_inv_ = glm::translate(trans_, glm::vec3(-x, -y, -z));
    return *this;
  }
  inline Object &scale_uniform(const float& s) {
    trans_ = glm::scale(trans_, glm::vec3(s, s, s));
    trans_inv_ = glm::scale(trans_, glm::vec3(1.0 / s, 1.0 / s, 1.0 / s));
  }
  inline Object &scale(const float& x, const float& y, const float& z) {
    trans_ = glm::scale(trans_, glm::vec3(x, y, z));
    trans_inv_ = glm::scale(trans_, glm::vec3(1.0 / x, 1.0 / y, 1.0 / z));
    return *this;
  }

protected:
  std::function<float(const glm::vec3 &)> dst_;
  glm::mat4 trans_, trans_inv_;

private:
};
} // namespace object
} // namespace specula

#endif // SPECULA_OBJECT_CLASS_HPP_
