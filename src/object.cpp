#include "specula/object.hpp"

#include <functional>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

#include "specula/rand.hpp"

specula::Object::Object(
    const std::function<float(const Object *, const glm::vec3 &)> &sdf_func)
    : uuid(size_rand()), material(nullptr), mat(1.0f), inv(1.0f), rot(1.0f),
      trans(0.0f), sdf(sdf_func) {}
specula::Object::Object(
    const std::function<float(const Object *, const glm::vec3 &)> &sdf_func,
    const std::unordered_map<std::string, std::variant<float, glm::vec3>> &vars)
    : uuid(size_rand()), material(nullptr), mat(1.0f), inv(1.0f), rot(1.0f),
      trans(0.0f), sdf(sdf_func), variables(vars) {}
