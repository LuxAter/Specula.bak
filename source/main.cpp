#include "specula.hpp"

#define MAX_STEPS 500
#define EPSILON 0.01

float MinDist(
    const specula::math::Vec3d& p,
    const std::vector<specula::object::Object>& objs) {
  double dist = std::numeric_limits<double>::infinity();
  for (auto& it : objs) {
    // dist = std::min(dist, it.DE(p));
  }
  return dist;
}

specula::Color RayCast(
    const specula::math::Vec3d& origin, const specula::math::Vec3d& dir,
    const std::vector<specula::object::Object>& objs) {
  double depth = 0;
  for (unsigned i = 0; i < MAX_STEPS; ++i) {
    double dist = MinDist(origin + (dir * depth), objs);
    if (dist < EPSILON) {
      auto p = origin + (dir * depth);
      return specula::Color(0.0, std::fabs(p.x), std::fabs(p.y));
    }
    depth += dist;
    if (depth >= 100) {
      return specula::Color(0.0);
    }
  }
  return specula::Color(0.0);
}

int main(int argc, char* argv[]) {
  std::vector<specula::object::Object> objs;
  // objs.push_back(specula::object::Sphere(1.0, {0.0, 0.0, 10.0}));
  // objs.push_back(
  //     specula::object::Plane({0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}));
  // objs.push_back(
  //     specula::object::Plane({0.0, 5.0, 0.0}, {0.0, -1.0, 0.0}));
  // objs.push_back(
  //     specula::object::Plane({-5.0, 0.0, 0.0}, {1.0, 0.0, 0.0}));
  // objs.push_back(
  //     specula::object::Plane({5.0, 0.0, 0.0}, {-1.0, 0.0, 0.0}));
  // objs.push_back(
  //     specula::object::Plane({0.0, 0.0, 20.0}, {0.0, 0.0, -1.0}));
  //
  specula::image::Image img(std::size_t(500), std::size_t(500));
  double invwidth = 1.0 / img.Width();
  double invheight = 1.0 / img.Height();
  double fov = 45.0, aspectratio = img.Width() / (double)img.Height();
  double angle = std::tan(M_PI * 0.5 * fov / 180.0);
  for (std::size_t y = 0; y < img.Height(); ++y) {
    for (std::size_t x = 0; x < img.Width(); ++x) {
      double xx = (2.0 * (((double)x + 0.5) * invwidth) - 1.0) * angle * aspectratio;
      double yy = (1.0 - 2.0 * (((double)y + 0.5) * invheight)) * angle;
      specula::math::Vec3d ray(xx, yy, 1);
      ray = specula::math::normalize(ray);
      img.Pixel(x, y, RayCast({0,0,0}, ray, objs).rgb());
    }
  }
  img.WritePng("test.png");

  return 0;
}
