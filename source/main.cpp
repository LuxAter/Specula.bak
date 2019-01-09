#include <iostream>
#include "specula.hpp"

#define MAX_STEPS 500
#define EPSILON 0.01
#define RES 500

using namespace specula;

Color RayCast(const math::vec3<double>& origin, const math::vec3<double>& dir,
              const Scene& scene) {
  double depth = 0;
  for (unsigned i = 0; i < MAX_STEPS; ++i) {
    DistEst dist = scene.Distance(origin + (dir * depth));
    if (dist.dist < EPSILON) {
      return scene.objects[dist.id].mat.base_color;
    }
    depth += dist.dist;
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
  Scene scene;

  scene.append(object::Object(object::Sphere(1.0), Color(0.0, 1.0, 0.0)));
  // scene.lo().Translate({-2.0, 0.0, 10.0});
  scene.append(
      object::Object(object::Torus({1.0, 0.25}), Color(1.0, 0.0, 0.0)));
  scene.lo().RotateX(M_PI / 2.0);
  scene.lo().RotateY(M_PI / 4.0);
  scene.lo().Translate({2.0, 0.0, 10.0});

  scene.append(light::Light(light::POINT_LIGHT, math::vec3{0.0, 4.0, 10.0}));

  image::Image img(std::size_t(RES), std::size_t(RES));
  double invwidth = 1.0 / img.Width();
  double invheight = 1.0 / img.Height();
  double fov = 45.0, aspectratio = img.Width() / (double)img.Height();
  double angle = std::tan(M_PI * 0.5 * fov / 180.0);
  math::Spline sp(math::Spline::LINEAR_INTERPOLATION, 50);
  sp.append({-2.0, 0.0, 10.0});
  sp.append({-2.0, -2.0, 10.0});
  sp.append({2.0, -2.0, 15.0});
  sp.append({2.0, 2.0, 15.0});
  sp.append({-2.0, 0.0, 10.0});
  for (std::size_t i = 0; i < sp.Frames(); ++i) {
    util::timer::Start();
    scene.o(0).Translate(sp(i));
    for (std::size_t y = 0; y < img.Height(); ++y) {
      for (std::size_t x = 0; x < img.Width(); ++x) {
        double xx =
            (2.0 * (((double)x + 0.5) * invwidth) - 1.0) * angle * aspectratio;
        double yy = (1.0 - 2.0 * (((double)y + 0.5) * invheight)) * angle;
        math::vec3<double> ray(xx, yy, 1);
        ray = math::normalize(ray);
        img.Pixel(x, y, RayCast({0, 0, 0}, ray, scene).rgb());
      }
    }
    scene.o(0).Translate(-sp(i));
    double stop = util::timer::Stop();
    std::cout << "TIME: " << util::timer::FmtTime(stop) << '\n';
    img.WritePng("lin/" + std::to_string(i) + ".png");
  }

  return 0;
}
