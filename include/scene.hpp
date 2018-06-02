#ifndef SPECULA_SCENE_HPP_
#define SPECULA_SCENE_HPP_

#include <vector>
#include "object.hpp"

#include "basic/vector.hpp"

namespace specula {
class Scene {
  public:
  // const std::vector<std::unique_ptr<Light>> lights;
  std::vector<std::unique_ptr<Object>> objects;

  bool Trace(const estl::base::Vec3d& start, const estl::base::Vec3d& dir,
             IntersectData& inter) const;
};
}  // namespace specula

#endif  // SPECULA_SCENE_HPP_
