#include "scene.hpp"

#include <memory>
#include <vector>

#include "math.hpp"
#include "object/object_class.hpp"

namespace specula::scene {
float fov;
glm::vec3 camera_pos, camera_center, camera_up;
std::vector<std::shared_ptr<ObjectBase>> objects;
} // namespace specula::scene

std::vector<std::shared_ptr<ObjectBase>> get_visible() {
  std::vector<std::shared_ptr<ObjectBase>> visible_objects;
  std::copy_if(objects.begin(), objects.end(),
               std::back_inserter(visible_objects),
               [](const std::shared_ptr<ObjectBase> &o) {
                 return o->material != nullptr;
               });
}

void specula::set_camera_fov(const float &v) { scene::fov = v; }
void specula::set_camera_pos(const glm::vec3 &p) { scene::camera_pos = p; }
void specula::set_camera_pos(const float &x, const float &y, const float &z) {
  scene::camera_pos = {x, y, z};
}
void specula::set_camera_center(const glm::vec3 &c) {
  scene::camera_center = c;
}
void specula::set_camera_center(const float &x, const float &y,
                                const float &z) {
  scene::camera_center = {x, y, z};
}
void specula::set_camera_up(const glm::vec3 &up) { scene::camera_up = up; }
void specula::set_camera_up(const float &x, const float &y, const float &z) {
  scene::camera_up = {x, y, z};
}
