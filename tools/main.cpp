#include <specula/prof.hpp>
#include <specula/specula.hpp>

#include <iostream>

int main(int argc, char const* argv[]) {
  specula::logger::initalize_core_logger();
  specula::prof::push_scope("Sleep Test");
  for (std::size_t f = 00; f < 1000; ++f) {
    specula::prof::push_scope("Milli");
    for (std::size_t i = 00; i < 100; ++i) {
      specula::prof::push_scope("Sleep 1");
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      specula::prof::pop_scope();
    }
    specula::prof::pop_scope();
    specula::prof::push_scope("Micro");
    for (std::size_t i = 00; i < 100; ++i) {
      specula::prof::push_scope("Sleep 2");
      std::this_thread::sleep_for(std::chrono::microseconds(100));
      specula::prof::pop_scope();
    }
    specula::prof::pop_scope();
  }
  specula::prof::pop_scope();

  specula::prof::print_report();

  return 0;
}
