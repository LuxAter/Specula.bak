#include <iostream>
#include <memory>
#include <regex>
#include <string>

#include <CLI/CLI.hpp>
#include <sol/sol.hpp>

#include "specula/specula.hpp"

class RegexValidator : public CLI::Validator {
public:
  RegexValidator(const std::string &pattern) {
    const std::regex pattern_regex(pattern);
    func_ = [pattern, pattern_regex](const std::string &str) {
      if (std::regex_match(str, pattern_regex)) {
        return std::string();
      }
      return "Value " + str + " does not match " + pattern;
    };
  }
};

struct LuaSphere {
  public:
    void translate(double x, double y, double z) {
      pos_ = {pos_.x + x, pos_.y + y, pos_.z + z};
    }
    glm::vec3 pos_;
  private:
};

int main(int argc, char *argv[]) {
  CLI::App app{"Lua controled graphics rendering engine"};
  std::string lua_source;
  std::string render_method = "pathTrace";
  std::string output = "out.png";
  std::size_t res_width = 100, res_height = 1080;
  std::string aspect_ratio = "1:1";
  unsigned verbosity;

  app.add_option("source", lua_source, "Lua source code")
      ->required()
      ->check(CLI::ExistingFile);

  app.add_option_group("Output");
  app.add_option("-o,--output", output, "Output file/directory")
      ->check(CLI::NonexistentPath);
  app.add_option("-r,--res,--resolution", res_width,
                 "Output image x resolution")
      ->check(CLI::PositiveNumber);
  app.add_option("--aspect", aspect_ratio, "Output image aspect ratio")
      ->check(RegexValidator("\\d+:\\d+"));
  app.add_flag("-v", verbosity, "Verbosity of the output");

  CLI11_PARSE(app, argc, argv);

  if (verbosity != 0)
    specula::log::verbosity(verbosity + 3);

  specula::ldatetime();

  std::size_t ax, ay;
  sscanf(aspect_ratio.c_str(), "%lu:%lu", &ax, &ay);
  res_height = res_width * ay / ax;

  double half = M_PI / 4.0;
  double film_z = (res_width / 2.0) / std::tan(half);

  std::vector<std::shared_ptr<specula::Primative>> objs;

  sol::state lua;
  lua.open_libraries();
  auto obj = lua["obj"].get_or_create<sol::table>();
  obj.new_usertype<LuaSphere>("Sphere", "translate", &LuaSphere::translate);

  // objs.push_back(std::make_shared<specula::Sphere>(
  //     specula::Sphere(1.0, {+1.0, -1.0, 3.0}, {1.0, 0.0, 0.0})));
  // objs.push_back(std::make_shared<specula::Sphere>(
  //     specula::Sphere(1.0, {-1.0, -1.0, 3.0}, {0.0, 1.0, 0.0})));
  // objs.push_back(std::make_shared<specula::Sphere>(
  //     specula::Sphere(1.0, {0.0, 1.0, 3.0}, {0.0, 0.0, 1.0})));

  specula::Image img({res_width, res_height});

  glm::vec3 origin(0.0, 0.0, 0.0);
  specula::linfo("FILM: %f", film_z);
  for (std::size_t y = 0; y < res_height; ++y) {
    for (std::size_t x = 0; x < res_width; ++x) {
      glm::vec3 dir(x - (res_width / 2.0), y - (res_height / 2.0), film_z);
      dir = glm::normalize(dir);
      int obj_index = -1;
      float min_t = std::numeric_limits<float>::infinity();
      for (std::size_t i = 0; i < objs.size(); ++i) {
        float t = objs[i]->intersect(origin, dir);
        if (t < min_t) {
          min_t = t;
          obj_index = i;
        }
      }
      if (obj_index != -1) {
        img(x, y) = objs[obj_index]->color_;
      } else {
        img(x, y) = std::array<double, 3>{0.5, 0.5, 0.6};
      }
    }
  }

  img.write(output);

  return 0;
}
