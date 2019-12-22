#include "specula/specula.hpp"

#include <array>

#include "specula/version.hpp"

std::array<unsigned, 3> specula::get_version() {
  return {SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR, SPECULA_VERSION_PATCH};
}