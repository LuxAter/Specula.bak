#include "specula/primatives/sphere.hpp"

#include "specula/primatives/primative.hpp"

#include <array>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>

#include "specula/math.hpp"
#include "specula/log.hpp"

specula::Sphere::Sphere(const float &r, std::array<double, 3>c)
    : Primative(c), radius_(r) {}
specula::Sphere::Sphere(const float &r, const glm::vec3 &p, std::array<double, 3> c)
    : Primative(c), radius_(r) {
  this->translate(p);
}

float specula::Sphere::intersect(const glm::vec3 &o, const glm::vec3 &d) const{
  glm::vec3 origin = glm::vec3(this->inv_ * glm::vec4(o, 1.0));
  glm::vec3 dir = glm::vec3(this->inv_ * glm::vec4(d, 0.0));
  // ldebug("%s->%s", glm::to_string(origin).c_str(), glm::to_string(dir).c_str());
  float a = glm::dot(dir, dir);
  float b = 2 * glm::dot(dir, origin);
  float c = glm::dot(origin, origin) - radius_ * radius_;
  auto soln = quadratic(a, b, c);
  if(!soln) return std::numeric_limits<float>::infinity();
  return std::get<1>(soln.value());
}
