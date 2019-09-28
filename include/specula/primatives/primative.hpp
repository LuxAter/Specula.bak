#ifndef SPECULA_PRIMATIVES_PRIMATIVE_HPP_
#define SPECULA_PRIMATIVES_PRIMATIVE_HPP_

#include <glm/glm.hpp>
#include <array>

namespace specula {
class Primative {
public:
  Primative();
  explicit Primative(const std::array<double, 3>&c);
  Primative(const glm::mat4 &obj, const glm::mat4 &inv);
  virtual float intersect(const glm::vec3 &o, const glm::vec3 &d) const;

  void rotate_x(const float &angle);
  void rotate_y(const float &angle);
  void rotate_z(const float &angle);

  void scale(const float &x, const float &y, const float &z);
  void translate(const float &x, const float &y, const float &z);
  void translate(const glm::vec3& p);

  std::array<double, 3> color_;

protected:
  glm::mat4 obj_, inv_;

private:
};
} // namespace specula

#endif // SPECULA_PRIMATIVES_PRIMATIVE_HPP_
