#include "object/object_class.hpp"

#include <cstdlib>
#include <functional>
#include <memory>
#include <string>

#include "material/material_class.hpp"
#include "math.hpp"
#include "rand.hpp"

specula::ObjectBase::ObjectBase()
    : uuid(urand()), distance_estimator(nullptr), distance_estimator_src(),
      material(nullptr), transform(1.0f), inverse_transform(1.0f) {}
specula::ObjectBase::ObjectBase(
    const std::function<float(const glm::vec3 &)> &distance_function)
    : uuid(urand()), distance_estimator(distance_function),
      distance_estimator_src(), material(nullptr), transform(1.0f),
      inverse_transform(1.0f) {}
specula::ObjectBase::ObjectBase(const std::string &distance_function)
    : uuid(urand()), distance_estimator(nullptr),
      distance_estimator_src(distance_function), material(nullptr),
      transform(1.0f), inverse_transform(1.0f) {}
specula::ObjectBase::ObjectBase(
    const std::function<float(const glm::vec3 &)> &distance_function,
    const std::string &distance_function_src)
    : uuid(urand()), distance_estimator(distance_function),
      distance_estimator_src(distance_function_src), material(nullptr),
      transform(1.0f), inverse_transform(1.0f) {}
