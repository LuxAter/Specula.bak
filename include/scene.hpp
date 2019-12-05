#ifndef SPECULA_SCENE_HPP_
#define SPECULA_SCENE_HPP_

#include <memory>
#include <vector>

#include "math.hpp"
#include "object/object.hpp"

#define ObjectConstructor(OBJ)                                                 \
  template <typename... ARGS>                                                  \
  inline std::shared_ptr<object::OBJ> OBJ(const ARGS &... args) {              \
    scene::get()->objects.push_back(std::make_shared<object::OBJ>(args...));   \
    return std::dynamic_pointer_cast<object::OBJ>(                             \
        scene::get()->objects.back());                                         \
  }

namespace specula {
class scene {
  scene() {}

public:
  inline static scene *get() {
    if (instance == nullptr) {
      instance = new scene();
    }
    return instance;
  }
  std::vector<std::shared_ptr<ObjectBase>> get_visible();

  float fov;
  glm::vec3 camera_pos, camera_center, camera_up;
  std::vector<std::shared_ptr<ObjectBase>> objects;

private:
  static scene *instance;
};

void set_camera_fov(const float &v);
void set_camera_pos(const glm::vec3 &p);
void set_camera_pos(const float &x, const float &y, const float &z);
void set_camera_center(const glm::vec3 &c);
void set_camera_center(const float &x, const float &y, const float &z);
void set_camera_direction(const glm::vec3 &c);
void set_camera_direction(const float &x, const float &y, const float &z);
void set_camera_up(const glm::vec3 &up);
void set_camera_up(const float &x, const float &y, const float &z);

ObjectConstructor(Sphere);
ObjectConstructor(Plane);
} // namespace specula

#endif // SPECULA_SCENE_HPP_
