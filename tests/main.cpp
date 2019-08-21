#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "specula/specula.hpp"

TEST_CASE("version") {
  unsigned major = 0, minor = 0, patch = 0;
  specula::version(major, minor, patch);
  CHECK(major == SPECULA_VERSION_MAJOR);
  CHECK(minor == SPECULA_VERSION_MINOR);
  CHECK(patch == SPECULA_VERSION_PATCH);
}
