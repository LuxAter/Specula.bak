#include "object/object_class.hpp"

#include <cstdlib>
#include <functional>
#include <memory>
#include <string>

#include "math.hpp"
#include "rand.hpp"
#include "shader/material.hpp"

specula::ObjectBase::ObjectBase()
    : uuid(urand()), distance_estimator(nullptr), distance_estimator_src(),
      variables(), material(nullptr), transform(1.0f), inverse_transform(1.0f) {
}
specula::ObjectBase::ObjectBase(
    const std::function<float(const glm::vec3 &)> &distance_function)
    : uuid(urand()), distance_estimator(distance_function),
      distance_estimator_src(), variables(), material(nullptr), transform(1.0f),
      inverse_transform(1.0f) {}
specula::ObjectBase::ObjectBase(const std::string &distance_function)
    : uuid(urand()), distance_estimator(nullptr),
      distance_estimator_src(distance_function), variables(), material(nullptr),
      transform(1.0f), inverse_transform(1.0f) {}
specula::ObjectBase::ObjectBase(
    const std::function<float(const glm::vec3 &)> &distance_function,
    const std::string &distance_function_src)
    : uuid(urand()), distance_estimator(distance_function),
      distance_estimator_src(distance_function_src), variables(),
      material(nullptr), transform(1.0f), inverse_transform(1.0f) {}
specula::ObjectBase::ObjectBase(
    const std::function<float(const glm::vec3 &)> &distance_function,
    const std::map<std::string,
                   variant<float *, glm::vec2 *, glm::vec3 *, glm::vec4 *>>
        &variables)
    : uuid(urand()), distance_estimator(distance_function),
      distance_estimator_src(), variables(variables), material(nullptr),
      transform(1.0f), inverse_transform(1.0f) {}
specula::ObjectBase::ObjectBase(
    const std::string &distance_function,
    const std::map<std::string,
                   variant<float *, glm::vec2 *, glm::vec3 *, glm::vec4 *>>
        &variables)
    : uuid(urand()), distance_estimator(nullptr),
      distance_estimator_src(distance_function), variables(variables),
      material(nullptr), transform(1.0f), inverse_transform(1.0f) {}
specula::ObjectBase::ObjectBase(
    const std::function<float(const glm::vec3 &)> &distance_function,
    const std::string &distance_function_src,
    const std::map<std::string,
                   variant<float *, glm::vec2 *, glm::vec3 *, glm::vec4 *>>
        &variables)
    : uuid(urand()), distance_estimator(distance_function),
      distance_estimator_src(distance_function_src), variables(variables),
      material(nullptr), transform(1.0f), inverse_transform(1.0f) {}
