#include <specula/color.hpp>
#include <specula/specula.hpp>

int main(int argc, char const *argv[]) {
  specula::initalize_logger(10);
  auto [major, minor, patch] = specula::get_version();
  LINFO("Specula v{}.{}.{}", major, minor, patch);

  specula::Settings settings;
  specula::Scene scene;
  scene.set_sky({1.0f, 2.0f, 1.5f});
  settings.set_pass(specula::OBJECT_INDEX);
  specula::render("out.png", settings, scene);

  return 0;
}
