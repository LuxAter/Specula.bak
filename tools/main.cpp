#include <iostream>

#include <specula/primatives.hpp>
#include <specula/specula.hpp>

int main(int argc, char const *argv[]) {
  auto [major, minor, patch] = specula::get_version();
  std::cout << "SPECULA: " << major << "." << minor << "." << patch << "\n";

  specula::Object sph = specula::Sphere(1.0f);
  std::cout << "GPU SPH:\n" << sph.gen_sdf(1e-5f);
  specula::Object tor = specula::Torus(2.0f, 0.5f);
  std::cout << "GPU TOR:\n" << tor.gen_sdf(1e-5f);

  specula::Image img(500, 500);
  return 0;
}
