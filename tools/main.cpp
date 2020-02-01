#define ENABLE_PROF
#define ENABLE_FILE_STREAM
#include <specula/prof.hpp>
// #include <specula/specula.hpp>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

struct MyObj {
  MyObj(int i) : i(i) { PROF_OBJ_CONSTRUCT(MyObj, this); }
  ~MyObj() { PROF_OBJECT_DESTRUCT(MyObj, this); }
  int i;
};

void foo(int ms) {
  PROF_FUNC_ARGS(ms);
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main(int argc, char const* argv[]) {
  PROF_BEGIN("Testing 1");
  std::size_t j = 0;
  std::vector<MyObj> objs;
  for (std::size_t f = 0; f < 5; ++f) {
    objs.push_back(MyObj(f * 2));
  }
  for (std::size_t f = 0; f < 5; ++f) {
    PROF_SNAPSHOT(MyObj, &(objs[f]), i);
    PROF_BEGIN("Milli");
    for (std::size_t i = 0; i < objs[f].i; ++i) {
      foo(100);
      PROF_COUNT("vals", "rand", rand(), "inc", ++j);
    }
    PROF_END();
    PROF_BEGIN("Micro");
    for (std::size_t i = 0; i < objs[f].i; ++i) {
      PROF_SCOPED("Sleep 2", "time", 100.0f / 1000000.0f);
      std::this_thread::sleep_for(std::chrono::microseconds(100));
      PROF_COUNT("vals", "rand", rand(), "inc", ++j);
    }
    PROF_END();
    PROF_INST("Loop", "count", f);
  }
  PROF_END();
  objs.clear();
  foo(50);

  PROF_CLOSE_STREAM();

  return 0;
}
