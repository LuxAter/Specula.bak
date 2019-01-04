#include "specula.hpp"

int fib(int n) {
  for (uint32_t i = 0; i < 1e8; ++i) {
  }
  return 0.0;
}

int main(int argc, char* argv[]) {
  double avg = 0.0;
  specula::util::timer::Start(1);
  std::cout << "0/0\n";
  for (uint64_t i = 0; i < 100; ++i) {
    specula::util::timer::Start();
    fib(i);
    avg += specula::util::timer::Stop();
    std::cout << specula::util::timer::FmtProc(avg / i, 100 - i, 100);
  }
  double sec = specula::util::timer::Stop(1);
  std::cout << "Total: " << specula::util::timer::FmtTime(sec) << "\n";
  return 0;
}
