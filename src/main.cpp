#include <iostream>
#include <string>

#include <CLI/CLI.hpp>

#include "specula/log.hpp"

int main(int argc, char *argv[]) {
  CLI::App app{"Lua controled graphics rendering engine"};
  std::string lua_source;
  std::string render_method = "pathTrace";
  unsigned verbosity;

  app.add_option("source", lua_source, "Lua source code")
      ->required()
      ->check(CLI::ExistingFile);
  app.add_option("--renderer", render_method, "Rendering algorithm to use")
      ->check(CLI::IsMember({"rayTrace", "pathTrace"}));

  app.add_flag("-v", verbosity, "Verbosity of the output");

  CLI11_PARSE(app, argc, argv);

  if (verbosity != 0)
    specula::log::verbosity(verbosity + 3);

  specula::ldatetime();
  specula::linfo("Lua Source: %s", lua_source.c_str());
  specula::linfo("Render Method: %s", render_method.c_str());

  return 0;
}
