#ifndef SPECULA_SCENE_HPP_
#define SPECULA_SCENE_HPP_

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "builder.hpp"
#include "enum.hpp"

namespace specula {
ENUM(Projection, PERSPECTIVE, ORTHOGRAPHIC);
class Scene {
public:
  void set_camera_dir(const glm::vec3 &dir) {
    camera_focus_ = camera_pos_ + dir;
  }

  BUILD_PVAR(Scene, Projection, projection, PERSPECTIVE);
  BUILD_PVAR(Scene, glm::vec3, camera_pos, glm::vec3(0.0, 0.0, 0.0));
  BUILD_PVAR(Scene, glm::vec3, camera_focus, glm::vec3(0.0, 0.0, -5.0));
  BUILD_PVAR(Scene, glm::vec3, camera_up, glm::vec3(0.0, 1.0, 0.0));
  BUILD_PVAR(Scene, float, fov, M_PI / 2.0);
  BUILD_PVAR(Scene, glm::vec3, sky, glm::vec3(0.0, 0.0, 0.0));

  std::vector<std::shared_ptr<Objects>> objects;
};
} // namespace specula

#endif // SPECULA_SCENE_HPP_
