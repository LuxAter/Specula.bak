#include "specula/primatives/primative.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "specula/log.hpp"

specula::Primative::Primative() : color_({0.0, 0.0, 0.0}), obj_(1.0), inv_(1.0) {}
specula::Primative::Primative(const std::array<double, 3> &c)
    : color_(c), obj_(1.0), inv_(1.0) {}
specula::Primative::Primative(const glm::mat4 &obj, const glm::mat4 &inv)
    : color_({0.0, 0.0, 0.0}), obj_(obj), inv_(inv) {}
float specula::Primative::intersect(const glm::vec3 &o,
                                      const glm::vec3 &d) const {
  return std::numeric_limits<double>::infinity();
}
void specula::Primative::rotate_x(const float &angle) {
  obj_ = glm::rotate(obj_, angle, glm::vec3(1.0, 0.0, 0.0));
  inv_ = glm::rotate(inv_, -angle, glm::vec3(1.0, 0.0, 0.0));
}
void specula::Primative::rotate_y(const float &angle) {
  obj_ = glm::rotate(obj_, angle, glm::vec3(0.0, 1.0, 0.0));
  inv_ = glm::rotate(inv_, -angle, glm::vec3(0.0, 1.0, 0.0));
}
void specula::Primative::rotate_z(const float &angle) {
  obj_ = glm::rotate(obj_, angle, glm::vec3(0.0, 0.0, 1.0));
  inv_ = glm::rotate(inv_, -angle, glm::vec3(0.0, 0.0, 1.0));
}

void specula::Primative::scale(const float &x, const float &y, const float &z) {
  obj_ = glm::scale(obj_, glm::vec3(x, y, z));
  inv_ = glm::scale(inv_, glm::vec3(1.0 / x, 1.0 / y, 1.0 / z));
}
void specula::Primative::translate(const float &x, const float &y,
                                   const float &z) {
  obj_ = glm::translate(obj_, glm::vec3(x, y, z));
  inv_ = glm::translate(inv_, glm::vec3(-x, -y, -z));
}
void specula::Primative::translate(const glm::vec3 &p) {
  obj_ = glm::translate(obj_, p);
  inv_ = glm::translate(inv_, -p);
}
