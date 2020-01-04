#include "specula/primatives.hpp"

#include <memory>

#include <glm/glm.hpp>
#include <unordered_map>

#include "specula/object.hpp"

std::shared_ptr<specula::Object> specula::Sphere(const float &radius) {
  return std::make_shared<Object>(
      [](const Object *obj, const glm::vec3 &p) {
        return glm::length(p) - obj->getf("radius");
      },
      specula::Object::variables_type{{"radius", radius}});
}
std::shared_ptr<specula::Object> specula::Box(const glm::vec3 &dims) {
  return std::make_shared<Object>(
      [](const Object *obj, const glm::vec3 &p) {
        const glm::vec3 q = glm::abs(p) - obj->get3("dims");
        return glm::length(glm::max(q, 0.0f)) +
               glm::min(glm::max(q.x, glm::max(q.y, q.z)), 0.0f);
      },
      specula::Object::variables_type{{"dims", dims}});
}
