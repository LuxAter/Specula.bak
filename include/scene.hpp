#ifndef SPECULA_SCENE_HPP_
#define SPECULA_SCENE_HPP_

#include <limits>
#include <map>
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
  std::size_t Frames() const;
  void SetFrame(const std::size_t& i);
  void ResetFrame(const std::size_t& i);

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

  inline void SplineObject(const std::size_t& id, const math::Spline& sp) {
    object_splines[id] = sp;
  }
  inline void SplineLight(const std::size_t& id, const math::Spline& sp) {
    light_splines[id] = sp;
  }

  inline light::Light& LastLight() { return lights.back(); }
  inline object::Object& LastObject() { return objects.back(); }
  inline light::Light& ll() { return lights.back(); }
  inline object::Object& lo() { return objects.back(); }

  inline light::Light& Light(const std::size_t i) { return lights[i]; }
  inline object::Object& Object(const std::size_t i) { return objects[i]; }
  inline light::Light& l(const std::size_t i) { return lights[i]; }
  inline object::Object& o(const std::size_t i) { return objects[i]; }
  inline math::Spline& ls(const std::size_t i) { return light_splines[i]; }
  inline math::Spline& os(const std::size_t i) { return object_splines[i]; }

  std::vector<light::Light> lights;
  std::vector<object::Object> objects;
  std::map<std::size_t, math::Spline> object_splines;
  std::map<std::size_t, math::Spline> light_splines;

 private:
};
}  // namespace specula

#endif  // SPECULA_SCENE_HPP_
