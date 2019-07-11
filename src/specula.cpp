#include "specula.hpp"

#include "util.hpp"
#include "version.hpp"

bool specula::init() {
  bool success = true;
  success &= log::init();
  version("Specula v%d.%d.%d", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR,
          SPECULA_VERSION_PATCH);
  return success;
}
bool specula::term() {
  bool success = true;
  success &= log::term();
  return success;
}
