/* Copyright (C)
 * 2019 - Arden Rasmussen
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */
#include "cli/argparse.hpp"

#include <regex>
#include <string>

#ifdef __APPLE__
#include <cli/cli.hpp>
#else
#include <CLI/CLI.hpp>
#endif

#include "math/vec2.hpp"

namespace specula::cli {
std::string script_source = "";
std::string output_path = "out.png";
std::size_t verbosity = 0;
vec2<std::size_t> resolution = {100, 100};
} // namespace specula::cli

class RegexValidator : public CLI::Validator {
public:
  explicit RegexValidator(const std::string &pattern) {
    const std::regex pattern_regex(pattern);
    func_ = [pattern, pattern_regex](const std::string &str) {
      if (std::regex_match(str, pattern_regex)) {
        return std::string();
      }
      return "Value " + str + " does not match " + pattern;
    };
  }
};

int specula::cli::parse_args(int argc, char *argv[]) {
  std::size_t pix_width = 500;
  std::string aspect_ratio = "1:1";
  CLI::App app{"PBR"};
  app.add_option("source", script_source, "Script source file")
      ->required()
      ->check(CLI::ExistingFile)
      ->check(RegexValidator(".*\\.(chai)"));
  app.add_flag("-v", verbosity, "Verbosity of the output");
  auto output = app.add_option_group("Output");
  output->add_option("-o,--output", output_path, "Output file/directory")
      ->check(RegexValidator(".*\\.(png|jpeg|bmp)"));
  output
      ->add_option("-r,--res,--resolution", pix_width,
                   "Output image resolution")
      ->check(CLI::PositiveNumber);
  output->add_option("-a,--aspect", aspect_ratio, "Output image aspect ratio")
      ->check(RegexValidator("\\d+[:x]\\d+"));

  try {
    app.parse(argc, argv);
  } catch (const CLI::CallForHelp &e) {
    app.exit(e);
    return -1;
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  vec2<double> aspect{0.0, 0.0};
  if (aspect_ratio.find(':') != std::string::npos)
    sscanf(aspect_ratio.c_str(), "%lf:%lf", &aspect.x, &aspect.y);
  else
    sscanf(aspect_ratio.c_str(), "%lfx%lf", &aspect.x, &aspect.y);
  resolution = {pix_width,
                static_cast<std::size_t>(static_cast<double>(pix_width) *
                                         aspect.y / aspect.x)};
#ifdef DEBUG
  if (verbosity == 0)
    verbosity = 6;
#endif
  verbosity = 6 - verbosity;

  return 0;
}
