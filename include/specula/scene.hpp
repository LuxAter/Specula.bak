#ifndef SCENE_HPP_E5DE6LPV
#define SCENE_HPP_E5DE6LPV

#include <map>
#include <memory>
#include <vector>

#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>

#include "object.hpp"
#include "primatives.hpp"
#include "shader/material.hpp"

#define ADD_PRIMATIVE(name, class)                                             \
  template <typename... ARGS>                                                  \
  inline Object &add_##name(const ARGS &... args) {                            \
    objects.push_back(std::make_shared<Object>(class(args...)));               \
    return *(objects.back());                                                  \
  }

namespace specula {
class Scene {
public:
  static inline Scene &get() { return *instance; }

  inline Object &add_object(const Object &obj) {
    objects.push_back(std::make_shared<Object>(obj));
    return *(objects.back());
  }
  inline Object &add_object(const std::shared_ptr<Object> &obj) {
    objects.push_back(obj);
    return *(objects.back());
  }

  inline Material &add_material(const Material &mat) {
    materials.push_back(std::make_shared<Material>(mat));
    return *(materials.back());
  }
  inline Material &add_material(const std::shared_ptr<Material> &mat) {
    materials.push_back(mat);
    return *(materials.back());
  }

  inline void set_sky(const glm::vec3 &color) { sky_color = color; }

  inline void set_camera_pos(const glm::vec3 &pos) { camera_pos = pos; }
  inline void set_camera_focus(const glm::vec3 &focus) { camera_focus = focus; }
  inline void set_camera_up(const glm::vec3 &up) { camera_up = up; }
  inline void set_camera_dir(const glm::vec3 &dir) {
    camera_focus = camera_pos + dir;
  }
  inline void set_camera_fov(const float &fov) { camera_fov = fov; }

  ADD_PRIMATIVE(sphere, Sphere);
  ADD_PRIMATIVE(torus, Torus);

  inline std::vector<std::shared_ptr<Object>> &get_objects() { return objects; }
  inline const std::vector<std::shared_ptr<Object>> &get_objects() const {
    return objects;
  }
  inline std::vector<std::shared_ptr<Material>> &get_materials() {
    return materials;
  }
  inline const std::vector<std::shared_ptr<Material>> &get_materials() const {
    return materials;
  }

  inline glm::vec3 &get_sky_color() { return sky_color; }
  inline const glm::vec3 &get_sky_color() const { return sky_color; }

  inline glm::vec3 &get_camera_pos() { return camera_pos; }
  inline const glm::vec3 &get_camera_pos() const { return camera_pos; }
  inline glm::vec3 &get_camera_focus() { return camera_focus; }
  inline const glm::vec3 &get_camera_focus() const { return camera_focus; }
  inline glm::vec3 &get_camera_up() { return camera_pos; }
  inline const glm::vec3 &get_camera_up() const { return camera_pos; }
  inline float &get_camera_fov() { return camera_fov; }
  inline const float &get_camera_fov() const { return camera_fov; }

  std::map<unsigned long, unsigned long> get_material_map() const;
  std::map<unsigned long, unsigned long> get_visible_map() const;

  std::vector<std::shared_ptr<Object>> get_visible() const;

private:
  std::vector<std::shared_ptr<Object>> objects;
  std::vector<std::shared_ptr<Material>> materials;

  glm::vec3 sky_color;

  glm::vec3 camera_pos, camera_focus, camera_up;
  float camera_fov;

  static Scene *instance;
};
} // namespace specula

#endif /* end of include guard: SCENE_HPP_E5DE6LPV */
