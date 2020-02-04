#include <specula/specula.hpp>

#include "argparse.hpp"

#include <specula/dev/tqdm.hpp>

int main(int argc, char* argv[]) {
  specula::logger::initialize_core_logger();
  args::parse_args(argc, argv);

  specula::ProgressBar <int>pb(1000000);
  pb.set_unit("frame");
  pb.set_unit_scale(true);
  pb.set_color(specula::ProgressBar<int>::Color::BLUE);
  pb.set_bar_chars("[=>-]");
  for(int i = 0; i < pb.size(); ++i) {
    pb.tick();
    pb.display();
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  return 0;
}
