#include "specula/dev/log.hpp"
#include "specula/version.hpp"
#include <specula/specula.hpp>

int main(int argc, char *argv[]) {
  specula::logger::register_sink<specula::logger::DailyFileSink>("logs/log",
                                                                 03, 00);
  specula::logger::register_sink<specula::logger::StderrColorSink>();
  specula::logger::initialize_core_logger();
  specula::logger::initialize_logger("CLI");

  LINFO("Specula Version {}.{}.{}", SPECULA_VERSION_MAJOR,
        SPECULA_VERSION_MINOR, SPECULA_VERSION_PATCH);
  LCINFO("CLI", "Specula-CLI Version {}.{}.{}", 0, 0, 0);

  return 0;
}
