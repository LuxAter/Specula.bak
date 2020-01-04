#include "specula/scene.hpp"
#include <specula/specula.hpp>

int main(int argc, char const *argv[]) {
  specula::initalize_logger(10);
  auto [major, minor, patch] = specula::get_version();
  LINFO("Specula v{}.{}.{}", major, minor, patch);

  specula::Settings settings;
  settings.set_pass(specula::OBJECT_INDEX);
  settings.set_width(500);
  settings.set_height(500);
  settings.set_spp(4);
  specula::Scene scene;
  scene.set_projection(specula::ORTHOGRAPHIC);
  scene.set_sky(glm::vec3(0.2f));
  for (std::size_t i = 0; i < 100; ++i) {
    scene.add_obj(specula::Sphere(0.5f * specula::frand())
                      ->translate(4.0f * specula::frand() - 2.0f,
                                  4.0f * specula::frand() - 2.0f,
                                  -5.0f + 2.0f * specula::frand()));
  }
  // scene.add_obj(specula::Sphere(1.0)->translate(0.0, 0.0, -5.0));
  specula::render("out.png", settings, scene);

  return 0;
}
