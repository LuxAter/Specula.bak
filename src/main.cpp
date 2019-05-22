#include <iostream>

#include "specula.hpp"
#include "util/util.hpp"

int main(int argc, char* argv[]) {
  specula::argparse::add_argument('r', "resolution", 1920,
                                  "resolution of output image");
  specula::argparse::add_argument('t', "threads", 16,
                                  "resolution of output image");
#ifdef DEBUG
  specula::argparse::add_argument('v', "verbose", true,
                                  "enables verbose output");
#else
  specula::argparse::add_argument('v', "verbose", false,
                                  "enables verbose output");
#endif
  specula::argparse::add_argument('o', "output", "out/", "output directory");
  specula::argparse::add_argument('\0', "tol", 1e-5, "ray tolerance");
  specula::time::start(0);
  auto args = specula::argparse::parse(argc, argv);
  std::cout << specula::time::stop(0) << "<<\n";
  for (auto& arg : args) {
    std::cout << arg.first << "::" << arg.second.type << "::";
    if (arg.second.type == specula::argparse::BOOL) {
      std::cout << arg.second.get_bool() << "\n";
    } else if (arg.second.type == specula::argparse::STRING) {
      std::cout << arg.second.get_string() << "\n";
    } else if (arg.second.type == specula::argparse::INT) {
      std::cout << arg.second.get_int() << "\n";
    } else if (arg.second.type == specula::argparse::DOUBLE) {
      std::cout << arg.second.get_double() << "\n";
    }
  }
  specula::log::init();
  specula::log::verbose_ = args["verbose"].get_bool();
  version("Specula V.%u.%u", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR);
  specula::log::term();
}
