#ifndef SPECULA_SCENE_HPP_
#define SPECULA_SCENE_HPP_

#include <limits>
#include <vector>

#include "light/light.hpp"
#include "math/math.hpp"
#include "object/object.hpp"

namespace specula {
struct DistEst {
  double dist;
  std::size_t id;
};
class Scene {
 public:
  DistEst Distance(const math::vec3<double>& p) const;

  inline void prepend(const object::Object& obj) {
    objects.insert(objects.begin(), obj);
  }
  inline void append(const object::Object& obj) { objects.push_back(obj); }
  inline void insert(const std::size_t i, const object::Object& obj) {
    objects.insert(objects.begin() + i, obj);
  }
  inline void prepend(const light::Light& obj) {
    lights.insert(lights.begin(), obj);
  }
  inline void append(const light::Light& obj) { lights.push_back(obj); }
  inline void insert(const std::size_t i, const light::Light& obj) {
    lights.insert(lights.begin() + i, obj);
  }

  inline light::Light& LastLight() {return lights.back();}
  inline object::Object& LastObject() {return objects.back();}
  inline light::Light& ll() {return lights.back();}
  inline object::Object& lo() {return objects.back();}

  inline light::Light& Light(const std::size_t i) { return lights[i]; }
  inline object::Object& Object(const std::size_t i) { return objects[i]; }
  inline light::Light& l(const std::size_t i) { return lights[i]; }
  inline object::Object& o(const std::size_t i) { return objects[i]; }

  std::vector<light::Light> lights;
  std::vector<object::Object> objects;

 private:
};
}  // namespace specula

#endif  // SPECULA_SCENE_HPP_
