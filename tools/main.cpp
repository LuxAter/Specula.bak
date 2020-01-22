#include <specula/specula.hpp>

#include <iostream>

#include <specula/math/vector.hpp>

int main(int argc, char const *argv[]) {
  specula::initalize_logger(10);

  specula::Vector4f v4(1.0, 2.0, 3.0, 4.0);
  std::cout << specula::format("Hello {}!", v4) << std::endl;
  return 0;
}
