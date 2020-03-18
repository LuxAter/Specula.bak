#include "specula/dev/log.hpp"
#include "specula/dev/progress.hpp"
#include "specula/global/rand.hpp"
#include "specula/version.hpp"
#include <specula/specula.hpp>

#include <chrono>
#include <thread>

#include "progress.hpp"

int main(int argc, char *argv[]) {
  specula::logger::register_sink<specula::logger::DailyFileSink>("logs/log", 03,
                                                                 00);
  specula::logger::register_sink<specula::logger::StderrColorSink>();
  specula::logger::initialize_core_logger();
  specula::logger::initialize_logger("CLI");

  LINFO("Specula Version {}.{}.{}", SPECULA_VERSION_MAJOR,
        SPECULA_VERSION_MINOR, SPECULA_VERSION_PATCH);
  LCINFO("CLI", "Specula-CLI Version {}.{}.{}", 0, 0, 0);

  std::size_t frames = 360;
  std::size_t pixels = 25000000;

  progress::MultiBar reporter;
  specula::progress_reporter_register_default(reporter.callback());

  // specula::progress_reporter_register_default([](const std::size_t &uuid,
  // const std::string_view &desc,
  // const std::string_view &unit,
  // const std::size_t &n,
  // const std::size_t &total,
  // const float &el) {
  // std::printf(
  // "%s\n",
  // progress::format(desc, unit, n, total, el, "K.WCCcW..B").c_str());
  // });
  for (specula::ProgressReporter pbf("Animation", "f", frames, 1);
       !pbf.is_done(); ++pbf) {
    for (specula::ProgressReporter pbp("Frame", "px", pixels, 5000);
         !pbp.is_done(); ++pbp) {
      // std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  }

  return 0;
}
