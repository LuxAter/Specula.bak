#include "scene.hpp"

#include <limits>
#include <vector>

#include "light/light.hpp"
#include "object/object.hpp"

specula::DistEst specula::Scene::Distance(const math::vec3<double>& p) const {
  DistEst ret{std::numeric_limits<double>::infinity(), 0};
  for (std::size_t i = 0; i < objects.size(); ++i) {
    double dist = objects[i].DE(p);
    if (dist < ret.dist) {
      ret.dist = dist;
      ret.id = i;
    }
  }
  return ret;
}

std::size_t specula::Scene::Frames() const {
  std::size_t frames = 0;
  for (auto& it : light_splines) {
    frames = std::max(frames, it.second.Frames());
  }
  for (auto& it : object_splines) {
    frames = std::max(frames, it.second.Frames());
  }
  return frames;
}

void specula::Scene::SetFrame(const std::size_t& i) {
  for (auto& it : light_splines) {
    lights[it.first].Translate(it.second(i));
  }
  for (auto& it : object_splines) {
    objects[it.first].Translate(it.second(i));
  }
}

void specula::Scene::ResetFrame(const std::size_t& i) {
  for (auto& it : light_splines) {
    lights[it.first].Translate(-it.second(i));
  }
  for (auto& it : object_splines) {
    objects[it.first].Translate(-it.second(i));
  }
}
