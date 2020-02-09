// #include <specula/specula.hpp>

#include <iostream>

#include <specula/core/geometry/common.hpp>
#include <specula/core/geometry/noise.hpp>
#include <specula/core/geometry/vector.hpp>

int main(int argc, char const *argv[]) {
  // specula::logger::initialize_core_logger();

  specula::Vector<2, float> v1(1.0, -7);
  specula::Vector3f v2(-2.3, -v1);

  std::cout << v1 << "->" << specula::abs(v1) << "\n";
  std::cout << v2 << "->" << specula::abs(v2) << "\n";
  std::cout << v1 << "->" << specula::perlin(v1) << "->" << specula::simplex(v1)
            << '\n';
  std::cout << v2 << "->" << specula::perlin(v2) << "->" << specula::simplex(v2)
            << '\n';

  return 0;
}
