#include "specula/scene.hpp"
#include "specula/settings.hpp"
#include <specula/specula.hpp>

int main(int argc, char const *argv[]) {
  specula::initalize_logger(10);
  auto [major, minor, patch] = specula::get_version();
  LINFO("Specula v{}.{}.{}", major, minor, patch);

  specula::Settings settings;
  settings.set_width(500);
  settings.set_height(500);
  settings.set_spp(1);
  settings.set_sampler(specula::NONE);
  specula::Scene scene;
  scene.set_sky(glm::vec3(0.2f));
  for (std::size_t i = 0; i < 50; ++i) {
    scene.add_obj(specula::Sphere(0.5f * specula::frand())
                      ->translate(4.0f * specula::frand() - 2.0f,
                                  4.0f * specula::frand() - 2.0f,
                                  -5.0f + 2.0f * specula::frand()));
    scene.objects.back()->material = specula::Diffuse(
        {specula::frand(), specula::frand(), specula::frand()});
  }
  settings.set_pass(specula::ALBEDO);
  specula::render("out.png", settings, scene);

  return 0;
}
