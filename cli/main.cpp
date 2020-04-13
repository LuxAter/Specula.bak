#include "specula/dev/prof.hpp"
#include <specula/specula.hpp>

#include <chrono>
#include <thread>

int main(int argc, char *argv[]) {
  PROF_BEGIN("Logging", "Init");
  PROF_COUNT("Test", 0);
  specula::logger::register_sink<specula::logger::DailyFileSink>("logs/log", 03,
                                                                 00);
  specula::logger::register_sink<specula::logger::StderrColorSink>();
  specula::logger::initialize_core_logger();
  specula::logger::initialize_logger("CLI");
  PROF_END();
  PROF_COUNT("Test", 1);

  PROF_BEGIN("Versioning", "Init");
  PROF_COUNT("Test", 2);
  LINFO("Specula Version {}.{}.{}", SPECULA_VERSION_MAJOR,
        SPECULA_VERSION_MINOR, SPECULA_VERSION_PATCH);
  LCINFO("CLI", "Specula-CLI Version {}.{}.{}", 0, 0, 0);
  PROF_COUNT("Test", 3);
  PROF_END();

  return 0;
}
