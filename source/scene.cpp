#include "scene.hpp"

#include <limits>
#include <vector>

#include "light/light.hpp"
#include "object/object.hpp"

specula::DistEst specula::Scene::Distance(const math::vec3<double>& p) const {
  DistEst ret{std::numeric_limits<double>::infinity(), 0};
  for (std::size_t i = 0; i < objects.size(); ++i) {
    double dist = objects[i].DE(p);
    if (dist < ret.dist) {
      ret.dist = dist;
      ret.id = i;
    }
  }
  return ret;
}
