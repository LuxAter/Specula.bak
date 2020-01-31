#define ENABLE_PROF
#define ENABLE_FILE_STREAM
#include <specula/prof.hpp>
#include <specula/specula.hpp>

#include <chrono>
#include <iostream>
#include <thread>

struct MyObj {
  MyObj(int i) : i(i) { specula::prof::event_object_construct(this); }
  ~MyObj() { specula::prof::event_object_destroy(this); }
  int i;
};

void foo() {
  specula::prof::event_begin("void foo()", "time", 100.0f / 1000.0f);
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  specula::prof::event_end();
}

int main(int argc, char const* argv[]) {
  specula::logger::initalize_core_logger();
  specula::prof::event_begin("Testing 1");
  std::size_t j = 0;
  std::vector<MyObj> objs;
  for (std::size_t f = 0; f < 5; ++f) {
    objs.push_back(MyObj(f * 2));
  }
  for (std::size_t f = 0; f < 5; ++f) {
    specula::prof::event_object_snapshot(&(objs[f]), "int", objs[f].i);
    specula::prof::event_begin("Milli");
    for (std::size_t i = 0; i < objs[f].i; ++i) {
      foo();
      specula::prof::event_counter("vals", "rand", rand(), "inc", ++j);
    }
    specula::prof::event_end();
    specula::prof::event_begin("Micro");
    for (std::size_t i = 0; i < objs[f].i; ++i) {
      specula::prof::event_begin("sleep2", "time", 100.0f / 1000000.0f);
      std::this_thread::sleep_for(std::chrono::microseconds(100));
      specula::prof::event_end();
      specula::prof::event_counter("vals", "rand", rand(), "inc", ++j);
    }
    specula::prof::event_end();
    specula::prof::event_instant("Loop", "count", f);
  }
  specula::prof::event_end();
  objs.clear();
  foo();

  return 0;
}
