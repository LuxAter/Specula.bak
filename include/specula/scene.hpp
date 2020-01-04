#ifndef SPECULA_SCENE_HPP_
#define SPECULA_SCENE_HPP_

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "object.hpp"
#include "builder.hpp"
#include "enum.hpp"

namespace specula {
ENUM(Projection, PERSPECTIVE, ORTHOGRAPHIC);
class Scene {
public:
  void set_camera_dir(const glm::vec3 &dir) {
    camera_focus = camera_pos + dir;
  }

  BUILD_PVAR(Scene, Projection, projection, PERSPECTIVE);
  BUILD_PVAR(Scene, glm::vec3, camera_pos, glm::vec3(0.0, 0.0, 0.0));
  BUILD_PVAR(Scene, glm::vec3, camera_focus, glm::vec3(0.0, 0.0, -5.0));
  BUILD_PVAR(Scene, glm::vec3, camera_up, glm::vec3(0.0, 1.0, 0.0));
  BUILD_PVAR(Scene, float, fov, M_PI / 2.0);
  BUILD_PVAR(Scene, glm::vec3, sky, glm::vec3(0.0, 0.0, 0.0));

  inline void add_obj(const std::shared_ptr<Object>& obj) {
    objects.push_back(obj);
  }

  std::vector<std::shared_ptr<Object>> objects;
};
} // namespace specula

#endif // SPECULA_SCENE_HPP_
