#ifndef SPECULA_ARGPARSE_HPP_
#define SPECULA_ARGPARSE_HPP_

#include <memory>

#include <cxxopts.hpp>

namespace args {
extern std::unique_ptr<cxxopts::ParseResult> result;
void parse_args(int argc, char* argv[]);
} // namespace args

#endif // SPECULA_ARGPARSE_HPP_