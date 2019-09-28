#include <iostream>
#include <string>

#include <CLI/CLI.hpp>

#include "specula/log.hpp"
#include "specula/image/image.hpp"

int main(int argc, char *argv[]) {
  CLI::App app{"Lua controled graphics rendering engine"};
  std::string lua_source;
  std::string render_method = "pathTrace";
  std::string output = "out.png";
  std::size_t res_width = 1920, res_height;
  unsigned verbosity;

  // app.add_option("source", lua_source, "Lua source code")
  //     ->required()
  //     ->check(CLI::ExistingFile);
  // app.add_option("--renderer", render_method, "Rendering algorithm to use")
  //     ->check(CLI::IsMember({"rayTrace", "pathTrace"}));

  app.add_option_group("Output");
  app.add_option("-o,--output", output, "Output file/directory")
      ->check(CLI::NonexistentPath);
  app.add_option("-r,--res,--resolution", res_width, "Output image resolution")
      ->check(CLI::PositiveNumber);
  app.add_flag("-v", verbosity, "Verbosity of the output");

  CLI11_PARSE(app, argc, argv);

  res_height = 9 * res_width / 16;

  if (verbosity != 0)
    specula::log::verbosity(verbosity + 3);

  specula::ldatetime();
  specula::Image img({res_width, res_height});
  img.write(output);
  // specula::linfo("Lua Source: %s", lua_source.c_str());
  // specula::linfo("Render Method: %s", render_method.c_str());

  return 0;
}
