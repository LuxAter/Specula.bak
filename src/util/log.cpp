#include "log.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

static const char* type_string[5] = {"FATAL  ", "ERROR  ", "WARNING", "INFO   ",
                                     "VERSION"};
static const char* type_color[5] = {"\033[1;31m", "\033[1;31m", "\033[1;33m",
                                    "\033[1;37m", "\033[1;33m"};

namespace specula::log {
FILE* file_ = NULL;
bool verbose_ = false;
bool color_ = true;
}  // namespace specula::log

void specula::log::init() {
  char buff[255];
#ifdef DEBUG
  snprintf(buff, 255, "log.log");
#else
  snprintf(buff, 255, "%ld.log", time(NULL));
#endif
  file_ = std::fopen(buff, "w");
}

void specula::log::log(const LogType& type, const char* msg, const char* file,
                       const char* func, size_t line, ...) {
  va_list args;
  va_start(args, line);
  char body[255];
  vsnprintf(body, 255, msg, args);
  va_end(args);
  std::time_t raw_time = time(NULL);
  std::tm* current_tm = std::localtime(&raw_time);
  char message[512];
#ifdef DEBUG
  snprintf(message, 512, "[%s] <%d:%d:%d> (%s:%s:%lu) %s\n", type_string[type],
           current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec, file,
           func, line, body);
#else
  snprintf(message, 512, "[%s] <%d:%d:%d> (%s:%lu) %s\n", type_string[type],
           current_tm->tm_hour, current_tm->tm_min, current_tm->tm_sec, func,
           line, body);
#endif
  if (verbose_ == true || type == FATAL || type == ERROR) {
    if (color_ == true) {
      printf("%s%s\033[0m", type_color[type], message);
    } else {
      printf("%s", message);
    }
  }
  fprintf(file_, "%s", message);
  if (type == FATAL || type == ERROR) {
    fflush(file_);
  }
}

void specula::log::term() { std::fclose(file_); }
