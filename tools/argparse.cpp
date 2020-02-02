#include "argparse.hpp"

#include <specula/dev.hpp>

#include <memory>

#include <cxxopts.hpp>

namespace args {
std::unique_ptr<cxxopts::ParseResult> result;
} // namespace args

void args::parse_args(int argc, char* argv[]) {
  PROF_FUNC();
  cxxopts::Options options("Specula", "Ray Marching Path Tracer");
  options.allow_unrecognised_options();
  options.add_options()("h,help", "Display help message");
  try {
    result = std::unique_ptr<cxxopts::ParseResult>(
        new cxxopts::ParseResult(options.parse(argc, argv)));
    if (result->count("help")) {
      std::cout << options.help() << std::endl;
      exit(0);
    }
  } catch (const cxxopts::OptionException& e) {
    std::cerr << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}
