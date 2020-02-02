#include <specula/specula.hpp>

#include "argparse.hpp"

int main(int argc, char* argv[]) {
  args::parse_args(argc, argv);
  specula::fs::FileWatch::watch("./resources/*.cl", [](const specula::fs::path& p) {
      std::cout << "PATH CHANGED: " << p << "\n";
  });
  std::this_thread::sleep_for(std::chrono::seconds(60));
  return 0;
}
