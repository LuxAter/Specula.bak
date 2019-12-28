#include <iostream>

#include <specula/log.hpp>
#include <specula/primatives.hpp>
#include <specula/specula.hpp>

int main(int argc, char const *argv[]) {

  specula::initalize_logger(10);
  auto [major, minor, patch] = specula::get_version();
  std::cout << "SPECULA: " << major << "." << minor << "." << patch << "\n";

  specula::Scene main = specula::Scene::get();
  auto &red = main.add_material(specula::MaterialBuilder::Diffuse()
                                    .base_color({1.0f, 0.0f, 0.0f})
                                    .build());
  auto &sph = main.add_sphere(1.0f);
  sph.set_material(red);

  specula::render(main, specula::RenderArgsBuilder().build());

  // specula::MaterialBuilder::Diffuse().specular_tint(0.7f).build();

  // specula::Object sph = specula::Sphere(1.0f);
  // std::cout << "GPU SPH:\n" << sph.gen_sdf(1e-5f);
  // specula::Object tor = specula::Torus(2.0f, 0.5f);
  // std::cout << "GPU TOR:\n" << tor.gen_sdf(1e-5f);

  specula::Image img(500, 500);
  return 0;
}
