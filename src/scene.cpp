#include "scene.hpp"

#include <vector>
#include "object.hpp"

#include "basic/vector.hpp"

bool specula::Scene::Trace(const estl::base::Vec3d& start,
                           const estl::base::Vec3d& dir,
                           IntersectData& inter) const {
  inter.near = INFINITY;
  inter.obj = nullptr;
  IntersectData intersect;
  for (std::size_t index = 0; index < objects.size(); ++index) {
    if (objects.at(index)->Intersect(start, dir, intersect) &&
        intersect.near < inter.near) {
      inter = intersect;
      inter.obj = (objects.at(index)).get();
    }
  }
  return (inter.obj!= nullptr);
}
