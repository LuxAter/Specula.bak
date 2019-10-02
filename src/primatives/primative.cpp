#include "specula/primatives/primative.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "specula/log.hpp"

specula::Primative::Primative()
    : color_({0.0, 0.0, 0.0}), obj_(1.0), inv_(1.0) {}
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
void specula::Primative::rotate_xy(const float &x, const float &y) {
  rotate_x(x);
  rotate_y(y);
}
void specula::Primative::rotate_xy(const glm::vec2 &a) {
  rotate_x(a.x);
  rotate_y(a.y);
}
void specula::Primative::rotate_xz(const float &x, const float &z) {
  rotate_x(x);
  rotate_z(z);
}
void specula::Primative::rotate_xz(const glm::vec2 &a) {
  rotate_x(a.x);
  rotate_z(a.y);
}
void specula::Primative::rotate_yx(const float &y, const float &x) {
  rotate_y(y);
  rotate_x(x);
}
void specula::Primative::rotate_yx(const glm::vec2 &a) {
  rotate_y(a.x);
  rotate_x(a.y);
}
void specula::Primative::rotate_yz(const float &y, const float &z) {
  rotate_y(y);
  rotate_z(z);
}
void specula::Primative::rotate_yz(const glm::vec2 &a) {
  rotate_y(a.x);
  rotate_z(a.y);
}
void specula::Primative::rotate_zx(const float &z, const float &x) {
  rotate_z(z);
  rotate_x(x);
}
void specula::Primative::rotate_zx(const glm::vec2 &a) {
  rotate_z(a.x);
  rotate_x(a.y);
}
void specula::Primative::rotate_zy(const float &z, const float &y) {
  rotate_z(z);
  rotate_y(y);
}
void specula::Primative::rotate_zy(const glm::vec2 &a) {
  rotate_z(a.x);
  rotate_y(a.y);
}
void specula::Primative::rotate_xyz(const float &x, const float &y,
                                    const float &z) {
  rotate_x(x);
  rotate_y(y);
  rotate_z(z);
}
void specula::Primative::rotate_xyz(const glm::vec3 &a) {
  rotate_x(a.x);
  rotate_y(a.y);
  rotate_z(a.z);
}
void specula::Primative::rotate_xzy(const float &x, const float &z,
                                    const float &y) {
  rotate_x(x);
  rotate_z(z);
  rotate_y(y);
}
void specula::Primative::rotate_xzy(const glm::vec3 &a) {
  rotate_x(a.x);
  rotate_z(a.y);
  rotate_y(a.z);
}
void specula::Primative::rotate_yxz(const float &y, const float &x,
                                    const float &z) {
  rotate_y(y);
  rotate_x(x);
  rotate_z(z);
}
void specula::Primative::rotate_yxz(const glm::vec3 &a) {
  rotate_y(a.x);
  rotate_x(a.y);
  rotate_z(a.z);
}
void specula::Primative::rotate_yzx(const float &y, const float &z,
                                    const float &x) {
  rotate_y(y);
  rotate_z(z);
  rotate_x(x);
}
void specula::Primative::rotate_yzx(const glm::vec3 &a) {
  rotate_y(a.x);
  rotate_z(a.y);
  rotate_z(a.z);
}
void specula::Primative::rotate_zxy(const float &z, const float &x,
                                    const float &y) {
  rotate_z(z);
  rotate_x(x);
  rotate_y(y);
}
void specula::Primative::rotate_zxy(const glm::vec3 &a) {
  rotate_z(a.x);
  rotate_x(a.y);
  rotate_y(a.x);
}
void specula::Primative::rotate_zyx(const float &z, const float &y,
                                    const float &x) {
  rotate_z(z);
  rotate_y(y);
  rotate_x(x);
}
void specula::Primative::rotate_zyx(const glm::vec3 &a) {
  rotate_z(a.x);
  rotate_y(a.y);
  rotate_x(a.z);
}

void specula::Primative::scale(const float &x, const float &y, const float &z) {
  obj_ = glm::scale(obj_, glm::vec3(x, y, z));
  inv_ = glm::scale(inv_, glm::vec3(1.0 / x, 1.0 / y, 1.0 / z));
}
void specula::Primative::scale(const glm::vec3 &s){
  obj_ = glm::scale(obj_, s);
  inv_ = glm::scale(inv_, glm::vec3(1.0 / s.x, 1.0 / s.y, 1.0 / s.z));
}

void specula::Primative::translate(const float &x, const float &y,
                                   const float &z) {
  obj_ = glm::translate(obj_, glm::vec3(x, y, z));
  inv_ = glm::translate(inv_, glm::vec3(-x, -y, -z));
}
void specula::Primative::translate(const glm::vec3 &t) {
  obj_ = glm::translate(obj_, t);
  inv_ = glm::translate(inv_, -t);
}
