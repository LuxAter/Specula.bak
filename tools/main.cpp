#include <specula/specula.hpp>

#include "argparse.hpp"

int main(int argc, char* argv[]) {
  specula::logger::initialize_core_logger();
  args::parse_args(argc, argv);

  return 0;
}
