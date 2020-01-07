#include "specula/specula.hpp"

#include "specula/version.hpp"

void get_version(unsigned &major, unsigned &minor, unsigned &patch) {
  major = SPECULA_VERSION_MAJOR;
  minor = SPECULA_VERSION_MINOR;
  patch = SPECULA_VERSION_PATCH;
}