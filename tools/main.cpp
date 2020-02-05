#include <specula/specula.hpp>

#include "argparse.hpp"

// #include <specula/dev/tqdm.hpp>
#include <specula/iterator.hpp>

int main(int argc, char* argv[]) {
  specula::logger::initialize_core_logger();
  args::parse_args(argc, argv);

  auto a = specula::iter::make_progressbar(360);
  auto b = specula::iter::make_progressbar(64);
  auto c = specula::iter::make_progressbar(128);
  a.set_description("Frames");
  b.set_description("Tiles");
  c.set_description("Samples");
  auto bars = specula::iter::make_multibar(a, b, c);

  for (auto& a_it : bars.get<0>()) {
    for (auto& b_it : bars.get<1>()) {
      for (auto& c_it : bars.get<2>()) {
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    }
  }

  // std::vector<int> iv{1, 3, 5, 7, 9, 9, 1, 5, 3, 11, 3};
  // for (auto& it : specula::iter::ProgressBar<std::vector<int>>(iv)) {
  //   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  // }
  // auto frames = specula::iter::make_progressbar(1000);
  // frames.set_unit("frames").set_unit_scale(true);
  // for (auto& it : frames) {
  // }
  // specula::iter::ProgressBar<std::size_t> bar(1000);
  // for(std::size_t i = 0; i < bar.size(); ++i) {
  //   bar.next();
  //   std::this_thread::sleep_for(std::chrono::seconds(1));
  // }

  // for (auto& it : specula::iter::Iterator<std::vector<int>>(
  //          iv, [](const specula::iter::IterData& data) {
  //            std::cout << "  " << data.n << "/" << data.total << ":"
  //                      << data.elapsed << "\n";
  //          })) {
  //   std::cout << "HI: " << it << "\n";
  //   std::this_thread::sleep_for(std::chrono::milliseconds(10));
  // }

  // specula::ProgressBar <int>pb(1000000);
  // pb.set_unit("frame");
  // pb.set_unit_scale(true);
  // pb.set_color(specula::ProgressBar<int>::Color::BLUE);
  // pb.set_bar_chars("[=>-]");
  // for(int i = 0; i < pb.size(); ++i) {
  //   pb.tick();
  //   pb.display();
  //   // std::this_thread::sleep_for(std::chrono::milliseconds(10));
  // }

  return 0;
}
