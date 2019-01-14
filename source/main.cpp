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

  scene.append(object::Object(object::Sphere(1.0), Color(1.0, 0.0, 0.0)));
  scene.SplineObject(0, math::Spline(math::Spline::CUBIC_INTERPOLATION, 40));
  scene.os(0).append({-3.0, 0.0, 10.0});
  scene.os(0).append({0.0, -3.0, 10.0});
  scene.os(0).append({3.0, 0.0, 10.0});
  scene.os(0).append({0.0, 3.0, 10.0});
  scene.os(0).ToggleLoop();
  scene.append(object::Object(object::Sphere(1.0), Color(0.0, 1.0, 0.0)));
  scene.SplineObject(1, math::Spline(math::Spline::CUBIC_INTERPOLATION, 20));
  scene.os(1).append({-3.0, 0.0, 15.0});
  scene.os(1).append({0.0, -3.0, 15.0});
  scene.os(1).append({3.0, 0.0, 15.0});
  scene.os(1).append({0.0, 3.0, 15.0});
  scene.os(1).ToggleLoop();
  scene.append(object::Object(object::Sphere(1.0), Color(0.0, 0.0, 1.0)));
  scene.SplineObject(2, math::Spline(math::Spline::CUBIC_INTERPOLATION, 10));
  scene.os(2).append({-3.0, 0.0, 20.0});
  scene.os(2).append({0.0, -3.0, 20.0});
  scene.os(2).append({3.0, 0.0, 20.0});
  scene.os(2).append({0.0, 3.0, 20.0});
  scene.os(2).ToggleLoop();

  image::Image img(std::size_t(RES), std::size_t(RES));
  double invwidth = 1.0 / img.Width();
  double invheight = 1.0 / img.Height();
  double fov = 45.0, aspectratio = img.Width() / (double)img.Height();
  double angle = std::tan(M_PI * 0.5 * fov / 180.0);
  double avg = 0.0;
  std::cout << "\n\n";
  for (std::size_t i = 0; i < scene.Frames(); ++i) {
    util::timer::Start();
    scene.SetFrame(i);
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
    scene.ResetFrame(i);
    avg += util::timer::Stop();
    std::cout << util::timer::FmtProc(avg, i, scene.Frames());
    img.WritePng("images/" + std::to_string(i) + ".png");
  }

  return 0;
}
