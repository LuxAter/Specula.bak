#ifndef SPECULA_OBJECT_INTERSECTION_HPP_
#define SPECULA_OBJECT_INTERSECTION_HPP_

#include <string>

#include "../math.hpp"
#include "object_class.hpp"

namespace specula::object {
class Intersection : public ObjectBase, public std::enable_shared_from_this<Intersection> {
public:
  Intersection(const std::shared_ptr<ObjectBase> &a,
        const std::shared_ptr<ObjectBase> &b)
      : ObjectBase([this](const glm::vec3 &p) {
          return std::max(this->a->distance(p), this->b->distance(p));
        }),
        a(a), b(b) {}
  std::shared_ptr<ObjectBase> a, b;

  ObjectOperators(Intersection)
};
} // namespace specula::object

#endif // SPECULA_OBJECT_INTERSECTION_HPP_
