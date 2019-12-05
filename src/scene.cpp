#include "scene.hpp"

#include <memory>
#include <vector>

#include "math.hpp"
#include "object/object_class.hpp"

specula::scene *specula::scene::instance = nullptr;
std::vector<std::shared_ptr<specula::ObjectBase>>
specula::scene::get_visible() {
  std::vector<std::shared_ptr<ObjectBase>> visible_objects;
  std::copy_if(objects.begin(), objects.end(),
               std::back_inserter(visible_objects),
               [](const std::shared_ptr<ObjectBase> &o) {
                 return o->material != nullptr;
               });
  return visible_objects;
}

void specula::set_camera_fov(const float &v) { scene::get()->fov = v; }
void specula::set_camera_pos(const glm::vec3 &p) {
  scene::get()->camera_pos = p;
}
void specula::set_camera_pos(const float &x, const float &y, const float &z) {
  scene::get()->camera_pos = {x, y, z};
}
void specula::set_camera_center(const glm::vec3 &c) {
  scene::get()->camera_center = c;
}
void specula::set_camera_center(const float &x, const float &y,
                                const float &z) {
  scene::get()->camera_center = {x, y, z};
}
void specula::set_camera_direction(const glm::vec3 &c) {
  scene::get()->camera_center = scene::get()->camera_pos + c;
}
void specula::set_camera_direction(const float &x, const float &y,
                                   const float &z) {
  scene::get()->camera_center = scene::get()->camera_pos + glm::vec3(x, y, z);
}
void specula::set_camera_up(const glm::vec3 &up) {
  scene::get()->camera_up = up;
}
void specula::set_camera_up(const float &x, const float &y, const float &z) {
  scene::get()->camera_up = {x, y, z};
}
