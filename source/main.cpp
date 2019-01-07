#include "specula.hpp"
#include <iostream>

#define MAX_STEPS 500
#define EPSILON 0.01

// std::pair<std::size_t, double> MinDist(
//     const specula::math::Vec3d& p,
//     const std::vector<specula::object::Object>& objs) {
//   double dist = std::numeric_limits<double>::infinity();
//   std::size_t min_i;
//   for (std::size_t i = 0; i < objs.size(); ++i) {
//     double tmp = std::min(dist, objs[i].DE(p));
//     if (tmp < dist) {
//       dist = tmp;
//       min_i = i;
//     }
//   }
//   return {min_i, dist};
// }
//
// specula::Color RayCast(const specula::math::Vec3d& origin,
//                        const specula::math::Vec3d& dir,
//                        const std::vector<specula::object::Object>& objs) {
//   double depth = 0;
//   for (unsigned i = 0; i < MAX_STEPS; ++i) {
//     std::pair<std::size_t, double> dist = MinDist(origin + (dir * depth),
//     objs); if (dist.second < EPSILON) {
//       return objs[dist.first].mat.base_color;
//     }
//     depth += dist.second;
//     if (depth >= 100) {
//       return specula::Color(0.0);
//     }
//   }
//   return specula::Color(0.0);
// }
using namespace specula::math;

int main(int argc, char* argv[]) {
  // std::vector<specula::object::Object> objs;
  // objs.push_back(specula::object::Object(specula::object::Sphere(1.0),
  //                                        specula::Color(0.0, 1.0, 0.0)));
  // objs.back().Translate({-2.0, 0.0, 10.0});
  // // objs.push_back(specula::object::Object(
  // //     specula::object::Cone(
  // //         specula::math::normalize(specula::math::Vec2d(1.0, 0.5))),
  // //     specula::Color(0.0, 0.0, 1.0)));
  // // objs.back().Translate({0.0, 0.0, 10.0});
  // objs.push_back(specula::object::Object(specula::object::Torus({1.0, 0.25}),
  //                                        specula::Color(1.0, 0.0, 0.0)));
  // objs.back().RotateX(M_PI / 2.0);
  // objs.back().RotateY(M_PI / 4.0);
  // objs.back().Translate({2.0, 0.0, 10.0});
  // // objs.push_back(specula::object::Sphere(1.0, {0.0, 0.0, 10.0}));
  // // objs.push_back(
  // //     specula::object::Plane({0.0, -1.0, 0.0}, {0.0, 1.0, 0.0}));
  // // objs.push_back(
  // //     specula::object::Plane({0.0, 5.0, 0.0}, {0.0, -1.0, 0.0}));
  // // objs.push_back(
  // //     specula::object::Plane({-5.0, 0.0, 0.0}, {1.0, 0.0, 0.0}));
  // // objs.push_back(
  // //     specula::object::Plane({5.0, 0.0, 0.0}, {-1.0, 0.0, 0.0}));
  // // objs.push_back(
  // //     specula::object::Plane({0.0, 0.0, 20.0}, {0.0, 0.0, -1.0}));
  // //
  // specula::image::Image img(std::size_t(500), std::size_t(500));
  // double invwidth = 1.0 / img.Width();
  // double invheight = 1.0 / img.Height();
  // double fov = 45.0, aspectratio = img.Width() / (double)img.Height();
  // double angle = std::tan(M_PI * 0.5 * fov / 180.0);
  // specula::util::timer::Start();
  // for (std::size_t y = 0; y < img.Height(); ++y) {
  //   for (std::size_t x = 0; x < img.Width(); ++x) {
  //     double xx =
  //         (2.0 * (((double)x + 0.5) * invwidth) - 1.0) * angle * aspectratio;
  //     double yy = (1.0 - 2.0 * (((double)y + 0.5) * invheight)) * angle;
  //     specula::math::Vec3d ray(xx, yy, 1);
  //     ray = specula::math::normalize(ray);
  //     img.Pixel(x, y, RayCast({0, 0, 0}, ray, objs).rgb());
  //   }
  // }
  // double stop = specula::util::timer::Stop();
  // std::cout << "TIME: " << specula::util::timer::FmtTime(stop) << '\n';
  // img.WritePng("test.png");

  return 0;
}
