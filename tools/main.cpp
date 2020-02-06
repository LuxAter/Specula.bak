#include <specula/specula.hpp>

#include "argparse.hpp"

int main(int argc, char* argv[]) {
  specula::initialize();
  args::parse_args(argc, argv);

  return 0;
}
