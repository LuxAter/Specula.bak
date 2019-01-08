#include <iostream>
#include "specula.hpp"

#define MAX_STEPS 500
#define EPSILON 0.01
#define RES 500

using namespace specula;

std::pair<std::size_t, double> MinDist(
    const math::vec3<double>& p, const std::vector<object::Object>& objs) {
  double dist = std::numeric_limits<double>::infinity();
  std::size_t min_i;
  for (std::size_t i = 0; i < objs.size(); ++i) {
    double tmp = std::min(dist, objs[i].DE(p));
    if (tmp < dist) {
      dist = tmp;
      min_i = i;
    }
  }
  return {min_i, dist};
}

Color RayCast(const math::vec3<double>& origin, const math::vec3<double>& dir,
              const std::vector<object::Object>& objs) {
  double depth = 0;
  for (unsigned i = 0; i < MAX_STEPS; ++i) {
    std::pair<std::size_t, double> dist = MinDist(origin + (dir * depth), objs);
    if (dist.second < EPSILON) {
      return objs[dist.first].mat.base_color;
    }
    depth += dist.second;
    if (depth >= 100) {
      return Color(0.0);
    }
  }
  return Color(0.0);
}

double frand() {
  return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

int main(int argc, char* argv[]) {
  std::vector<object::Object> objs;
  std::vector<light::Light> lights;

  objs.push_back(object::Object(object::Sphere(1.0), Color(0.0, 1.0, 0.0)));
  objs.back().Translate({-2.0, 0.0, 10.0});
  objs.push_back(
      object::Object(object::Torus({1.0, 0.25}), Color(1.0, 0.0, 0.0)));
  objs.back().RotateX(M_PI / 2.0);
  objs.back().RotateY(M_PI / 4.0);
  objs.back().Translate({2.0, 0.0, 10.0});

  lights.push_back(
      light::Light(light::POINT_LIGHT, math::vec3{0.0, 5.0, 10.0}));

  image::Image img(std::size_t(RES), std::size_t(RES));
  double invwidth = 1.0 / img.Width();
  double invheight = 1.0 / img.Height();
  double fov = 45.0, aspectratio = img.Width() / (double)img.Height();
  double angle = std::tan(M_PI * 0.5 * fov / 180.0);
  util::timer::Start();
  for (std::size_t y = 0; y < img.Height(); ++y) {
    for (std::size_t x = 0; x < img.Width(); ++x) {
      double xx =
          (2.0 * (((double)x + 0.5) * invwidth) - 1.0) * angle * aspectratio;
      double yy = (1.0 - 2.0 * (((double)y + 0.5) * invheight)) * angle;
      math::vec3<double> ray(xx, yy, 1);
      ray = math::normalize(ray);
      img.Pixel(x, y, RayCast({0, 0, 0}, ray, objs).rgb());
    }
  }
  double stop = util::timer::Stop();
  std::cout << "TIME: " << util::timer::FmtTime(stop) << '\n';
  img.WritePng("test.png");

  return 0;
}
