#include <iostream>

#include <specula/specula.hpp>

int main(int argc, char const *argv[]) {
  auto [major, minor, patch] = specula::get_version();
  std::cout << "SPECULA: " << major << "." << minor << "." << patch << "\n";

  specula::Image img(500, 500);
  return 0;
}
