#define ENABLE_PROF
#include <specula/prof.hpp>
#include <specula/specula.hpp>

#include <iostream>
#include <thread>
#include <chrono>

void foo() {
  PROF_FUNC();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

int main(int argc, char const* argv[]) {
  specula::logger::initalize_core_logger();
  PROF_FUNC();
  for (std::size_t f = 0; f < 2; ++f) {
    PROF_BEGIN("Milli", 0xff0000);
    for (std::size_t i = 0; i < 10; ++i) {
      PROF_SCOPED("Sleep 1");
      foo();
    }
    PROF_END();
    PROF_BEGIN("Micro", 0x00ff00);
    for (std::size_t i = 0; i < 10; ++i) {
      PROF_SCOPED("Sleep 2");
      std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
    PROF_END();
  }

  specula::prof::write_to_file("specula.prof.txt");
  specula::prof::write_to_file("specula.prof.csv");
  specula::prof::write_to_file("specula.prof.json");
  specula::prof::print_report();

  return 0;
}
