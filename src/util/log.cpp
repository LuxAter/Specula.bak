#include "util/log.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

namespace specula::log {
FILE *file_ = NULL;
#ifdef DEBUG
unsigned verbose_ = 10;
#else
unsigned verbose_ = 2;
#endif
bool color_ = true;
} // namespace specula::log

bool specula::log::init() {
  char buff[255];
#ifdef DEBUG
  snprintf(buff, 255, "log.log");
#else
  snprintf(buff, 255, "%ld.log", time(NULL));
#endif
  file_ = std::fopen(buff, "w");
  if (file_)
    return true;
  return false;
}

bool specula::log::term() {
  if (file_) {
    std::fclose(file_);
    return true;
  }
  return false;
}
