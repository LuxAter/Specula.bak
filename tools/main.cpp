#include <specula/specula.hpp>

#include "argparse.hpp"

int main(int argc, char* argv[]) {
  specula::logger::initialize_core_logger();
  args::parse_args(argc, argv);
  specula::fs::Watcher watcher(
      "**/*.(cl|gpu|lua)",
      [](const specula::fs::path& p, const specula::fs::Watcher::Event& event) {
        switch (event) {
        case specula::fs::Watcher::Event::MODIFIED:
          std::cout << "FILE MODIFIED: " << p << "\n";
          break;
        case specula::fs::Watcher::Event::CREATED:
          std::cout << "FILE CREATED: " << p << "\n";
          break;
        case specula::fs::Watcher::Event::DELETED:
          std::cout << "FILE DELETED: " << p << "\n";
          break;
        }
      });
  std::this_thread::sleep_for(std::chrono::seconds(120));
  return 0;
}
