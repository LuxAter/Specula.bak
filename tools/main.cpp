#include <specula/specula.hpp>

#include <iostream>

#include <specula/math/matrix.hpp>
#include <specula/math/vector.hpp>

int main(int argc, char const *argv[]) {
  specula::initalize_logger(10);

  specula::Vector2f v2(1.0, 2.0);
  specula::Vector3f v3(1.0, 2.0, 3.0);
  specula::Vector4f v4(1.0, 2.0, 3.0, 4.0);
  specula::VectorNf<5> v5(1.0, 2.0, 3.0, 4.0, 5.0);
  std::cout << specula::format("V2: {}", v2) << std::endl;
  std::cout << specula::format("V3: {}", v3) << std::endl;
  std::cout << specula::format("V4: {}", v4) << std::endl;
  std::cout << specula::format("V5: {}", v5) << std::endl;
  specula::Matrix2x2f m22(2.0);
  specula::Matrix3x3f m33(3.0);
  specula::Matrix4x4f m44(4.0);
  specula::MatrixNxNf<5> m55(5.0);
  specula::MatrixNxNf<3> m33b(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  std::cout << specula::format("M2x2: {}", m22) << std::endl;
  std::cout << specula::format("M3x3: {}", m33) << std::endl;
  std::cout << specula::format("M4x4: {}", m44) << std::endl;
  std::cout << specula::format("M5x5: {}", m55) << std::endl;
  std::cout << specula::format("M3x3b: {}", m33b) << std::endl;

  return 0;
}
