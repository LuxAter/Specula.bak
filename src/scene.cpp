#include "scene.hpp"

#include <memory>
#include <vector>

#include "math.hpp"
#include "object/object_class.hpp"

namespace specula {
float fov;
glm::vec3 camera_pos, camera_center, camera_up;
std::vector<std::shared_ptr<ObjectBase>> objects;
} // namespace specula

void specula::set_camera_fov(const float &v) { fov = v; }
void specula::set_camera_pos(const glm::vec3 &p) { camera_pos = p; }
void specula::set_camera_pos(const float &x, const float &y, const float &z) {
  camera_pos = {x, y, z};
}
void specula::set_camera_center(const glm::vec3 &c) { camera_center = c; }
void specula::set_camera_center(const float &x, const float &y,
                                const float &z) {
  camera_center = {x, y, z};
}
void specula::set_camera_up(const glm::vec3 &up) { camera_up = up; }
void specula::set_camera_up(const float &x, const float &y, const float &z) {
  camera_up = {x, y, z};
}
