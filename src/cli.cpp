#include "cli.hpp"

#include <regex>
#include <string>
#include <thread>
#ifdef __APPLE__
#include <cli/cli.hpp>
#else
#include <CLI/CLI.hpp>
#endif

namespace CLI {
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
} // namespace CLI

args_t parse_args(int argc, char *argv[]) {
  args_t args;
  args.valid = true;
  args.script_path = "";
  args.output_path = "out.png";
  args.verbosity = 0;
  args.spp = 32;
  args.min_bounces = 10;
  args.tile_size = 32;
  args.threads = std::thread::hardware_concurrency();
  args.res_width = 1000;
  args.res_height = 1000;
  args.render_albido = false;
  args.render_normal = false;
  args.render_depth = false;
  args.denoise = false;
  args.fov = M_PI / 4.0f;

  std::string aspect_ratio = "1:1";
  std::size_t pix_width;

  CLI::App app{"Specula"};
  app.add_option("source", args.script_path, "Scene definition script")
      ->required()
      ->check(CLI::ExistingFile)
      ->check(CLI::RegexValidator(".*\\.(lua)"));
  app.add_flag("-v", args.verbosity, "Verbosity of the terminal output");

  auto renderer = app.add_option_group("Renderer");
  renderer
      ->add_option("-b,--bounces", args.min_bounces,
                   "Minimum number of bounces each ray will make")
      ->check(CLI::PositiveNumber);
  renderer->add_option("-d,--denoise", args.denoise,
                       "Enable AI denoiser (Not Yet Implemented)");
  renderer->add_option("-f,--fov", args.fov, "Renderer FOV")
      ->check(CLI::PositiveNumber);
  renderer->add_option("-s,--spp", args.spp, "Samples per pixel")
      ->check(CLI::PositiveNumber);
  renderer
      ->add_option("-j,--threads", args.threads,
                   "Number of threads to use for concurrency")
      ->check(CLI::PositiveNumber);
  renderer->add_option("-t,--tile", args.tile_size, "Size of each render tile")
      ->check(CLI::PositiveNumber);

  auto output = app.add_option_group("Output");
  output->add_option("--aspect", aspect_ratio, "Output image aspect ratio")
      ->check(CLI::RegexValidator("\\d+[:x]\\d+"));
  output->add_option(
      "-a,--albido", args.render_albido,
      "Render image containing just the albido map of the objects");
  output->add_option(
      "-d,--depth", args.render_depth,
      "Render image containing just the depth map of the objects");
  output->add_option(
      "-n,--normal", args.render_normal,
      "Render image containing just the normal map of the objects");
  output->add_option("-o,--output", args.output_path, "Output file/directory")
      ->check(CLI::RegexValidator(".*\\.(png|jpeg|bmp)"));
  output
      ->add_option("-r,--res,--resolution", pix_width,
                   "Output image resolution")
      ->check(CLI::PositiveNumber);

  try {
    app.parse(argc, argv);
  } catch (const CLI::CallForHelp &e) {
    app.exit(e);
    args.valid = false;
  } catch (const CLI::ParseError &e) {
    app.exit(e);
    args.valid = false;
  }

  float aspect_width = 0.0f, aspect_height = 0.0f;
  if (aspect_ratio.find(':') != std::string::npos) {
    sscanf(aspect_ratio.c_str(), "%f:%f", &aspect_width, &aspect_height);
  } else {
    sscanf(aspect_ratio.c_str(), "%fx%f", &aspect_width, &aspect_height);
  }

  args.res_width = pix_width;
  args.res_height = static_cast<std::size_t>(static_cast<float>(pix_width) *
                                             aspect_height / aspect_width);

  return args;
};
