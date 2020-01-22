#include <specula/specula.hpp>

#include <iostream>

#include <specula/math/matrix.hpp>
#include <specula/math/vector.hpp>

int main(int argc, char const *argv[]) {
  specula::initalize_logger(10);

  specula::Matrix4f a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  specula::Matrix4f b(1, 2, 3, 4, 5, 6, 7, 8, 9,10, 11, 12, 13, 14, 15, 16);
  specula::Vector4f c(1, 2, 3, 4);
  std::cout << specula::format("{}", a) << std::endl;
  std::cout << specula::format("{}", b) << std::endl;
  std::cout << specula::format("{}", c) << std::endl;
  std::cout << "==========\n";
  std::cout << specula::format("{} * {} = {}", a, b, a * b) << std::endl;
  std::cout << specula::format("{} * {} = {}", a, c, a * c) << std::endl;
  std::cout << specula::format("{} * {} = {}", a, b, a * b) << std::endl;

  return 0;
}
