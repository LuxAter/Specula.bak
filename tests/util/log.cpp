#include "doctest.h"

#include "util/log.hpp"

TEST_CASE("File Output") {
  specula::log::init();
  CHECK(1 == 1);
  specula::log::term();
}
