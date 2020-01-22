#include <specula/specula.hpp>

#include <iostream>

#include <specula/math/matrix.hpp>
#include <specula/math/vector.hpp>

int main(int argc, char const *argv[]) {
  specula::initalize_logger(10);

  specula::MatrixNxMf<2,3> a(1, 2, 3, 4, 5, 6);
  specula::MatrixNxMf<3,2> b(1, 2, 3, 4, 5, 6);
  std::cout << specula::format("{} * {} = {}", a, b, a * b);

  return 0;
}
