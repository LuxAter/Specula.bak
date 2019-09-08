#include "doctest.h"

#include "specula/fmt.hpp"
#include "specula/fs.hpp"
#include "specula/log.hpp"

#include <ctime>
#include <fstream>
#include <string>

TEST_CASE("file logging") {

  if (specula::fs::exists("test_logs/")) {
    specula::fs::remove_all("test_logs/");
  }

  specula::log::Logger::set_prefix("test_logs/");
  specula::log::Logger::console(false);

  specula::lfatal("msg \"%s\", Year: %d", "Hello, World", 2019);

  time_t now = time(nullptr);
  struct tm tstruct = *localtime(&now);

  CHECK(specula::fs::exists(specula::fmt::format(
      "test_logs/%04d.%02d.%02d.log", tstruct.tm_year + 1900,
      tstruct.tm_mon + 1, tstruct.tm_mday)));

  std::ifstream file(specula::fmt::format("test_logs/%04d.%02d.%02d.log",
                                          tstruct.tm_year + 1900,
                                          tstruct.tm_mon + 1, tstruct.tm_mday));
  CHECK(file.is_open());
  std::string line;
  std::getline(file, line);
  CHECK(line == "[FATAL] (Specula/tests/log.cpp:_DOCTEST_ANON_FUNC_2:20) msg "
                "\"Hello, World\", Year: 2019");
  file.close();
}
