#include <iostream>
#include <limits>
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
int main(int argc, char *argv[]) {
  srand(time(NULL));
  CLI::App app{"Lua controled graphics rendering engine"};
  std::string lua_source;
  std::string render_method = "pathTrace";
  std::string output = "out.png";
  std::size_t res_width = 500, res_height = 1080;
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
  specula::lversion("Specula v.%lu.%lu.%lu", SPECULA_VERSION_MAJOR,
                    SPECULA_VERSION_MINOR, SPECULA_VERSION_PATCH);

  specula::opencl::log_info();
  // return 1;

  std::size_t ax, ay;
  sscanf(aspect_ratio.c_str(), "%lu:%lu", &ax, &ay);
  res_height = res_width * ay / ax;

  double half = M_PI / 4.0;
  double film_z = (res_width / 2.0) / std::tan(half);

  std::vector<std::shared_ptr<specula::Primative>> objs;
  std::vector<std::shared_ptr<specula::Primative>> *objs_ptr = &objs;

  sol::state lua;
  lua.open_libraries();
  auto obj = lua["obj"].get_or_create<sol::table>();
  obj.new_usertype<specula::LuaPrimative>(
      "Object", "rotate_x", &specula::LuaPrimative::rotate_x, "rotate_y",
      &specula::LuaPrimative::rotate_y, "rotate_z",
      &specula::LuaPrimative::rotate_z, "rotate_xy",
      &specula::LuaPrimative::rotate_xy, "rotate_xz",
      &specula::LuaPrimative::rotate_xz, "rotate_yx",
      &specula::LuaPrimative::rotate_yx, "rotate_yz",
      &specula::LuaPrimative::rotate_yz, "rotate_zx",
      &specula::LuaPrimative::rotate_zx, "rotate_zy",
      &specula::LuaPrimative::rotate_zy, "rotate_xyz",
      &specula::LuaPrimative::rotate_xyz, "rotate_xzy",
      &specula::LuaPrimative::rotate_xzy, "rotate_yxz",
      &specula::LuaPrimative::rotate_yxz, "rotate_yzx",
      &specula::LuaPrimative::rotate_yzx, "rotate_zxy",
      &specula::LuaPrimative::rotate_zxy, "rotate_zyx",
      &specula::LuaPrimative::rotate, "rotate",
      &specula::LuaPrimative::rotate_zyx, "scale",
      &specula::LuaPrimative::scale, "translate",
      &specula::LuaPrimative::translate);

  lua.set_function("Sphere", [objs_ptr](const float &r) mutable {
    return specula::LuaSphere(r, objs_ptr);
  });
  lua.set_function(
      "Torus", [objs_ptr](const float &r_big, const float &r_small) mutable {
        return specula::LuaTorus(r_big, r_small, objs_ptr);
      });
  lua.set_function(
      "CappedTorus", [objs_ptr](const float &r_big, const float &r_small,
                                const float &ra, const float &rb) mutable {
        return specula::LuaCappedTorus(r_big, r_small, ra, rb, objs_ptr);
      });
  lua.set_function("Box", [objs_ptr](const float &w, const float &l,
                                     const float &h) mutable {
    return specula::LuaBox(w, l, h, objs_ptr);
  });
  lua.set_function("RoundBox",
                   [objs_ptr](const float &r, const float &w, const float &l,
                              const float &h) mutable {
                     return specula::LuaRoundBox(r, w, l, h, objs_ptr);
                   });
  lua.set_function("Link", [objs_ptr](const float &len, const float &r_outer,
                                      const float &r_inner) mutable {
    return specula::LuaLink(len, r_outer, r_inner, objs_ptr);
  });
  lua.set_function("Cylinder", [objs_ptr](const float &r) mutable {
    return specula::LuaCylinder(r, objs_ptr);
  });
  lua.set_function("Cone", [objs_ptr](const float &alpha) mutable {
    return specula::LuaCone(alpha, objs_ptr);
  });
  lua.set_function("Plane", [objs_ptr](const float &x, const float &y,
                                       const float &z, const float &w) mutable {
    return specula::LuaPlane(x, y, z, w, objs_ptr);
  });
  lua.set_function("HexagonalPrism",
                   [objs_ptr](const float &a, const float &b) mutable {
                     return specula::LuaHexagonalPrism(a, b, objs_ptr);
                   });
  lua.set_function("TriangularPrism",
                   [objs_ptr](const float &a, const float &b) mutable {
                     return specula::LuaTriangularPrism(a, b, objs_ptr);
                   });
  lua.set_function("Capsule", [objs_ptr](const float &x1, const float &y1,
                                         const float &z1, const float &x2,
                                         const float &y2, const float &z2,
                                         const float &r) {
    return specula::LuaCapsule(x1, y1, z1, x2, y2, z2, r, objs_ptr);
  });
  lua.set_function("VerticalCapsule",
                   [objs_ptr](const float &h, const float &r) mutable {
                     return specula::LuaVerticalCapsule(h, r, objs_ptr);
                   });
  lua.set_function("CappedCylinder",
                   [objs_ptr](const float &h, const float &r) mutable {
                     return specula::LuaCappedCylinder(h, r, objs_ptr);
                   });
  lua.set_function(
      "RoundedCylinder",
      [objs_ptr](const float &ra, const float &rb, const float &h) mutable {
        return specula::LuaRoundedCylinder(ra, rb, h, objs_ptr);
      });
  lua.set_function("CappedCone", [objs_ptr](const float &r1, const float &r2,
                                            const float &h) mutable {
    return specula::LuaCappedCone(r1, r2, h, objs_ptr);
  });
  lua.set_function("SolidAngle", [objs_ptr](const float &a, const float &b,
                                            const float &ra) mutable {
    return specula::LuaSolidAngle(a, b, ra, objs_ptr);
  });

  lua.script_file(lua_source);

  specula::linfo("N objs: %lu", objs.size());
  for (std::size_t i = 0; i < objs.size(); ++i) {
    std::cout << "DE:\n" << objs[i]->gen_function() << "\n";
  }

  specula::Image img({res_width, res_height});

  float T_MAX = 1e5f;
  float EPSILON = 1e-5f;

  specula::linfo("FILM: %f", film_z);

  specula::linfo("Compiling scene distance estimator");
  auto func = specula::opencl::generate_function(objs);

  glm::vec3 origin(0.0, 0.0, 0.0);
  std::vector<specula::ray> rays;
  specula::linfo("Computing distances");
  for (std::size_t y = 0; y < res_height; ++y) {
    for (std::size_t x = 0; x < res_width; ++x) {
      glm::vec3 dir(x - (res_width / 2.0), y - (res_height / 2.0), film_z);
      dir = glm::normalize(dir);
      rays.push_back({origin, glm::normalize(dir)});
    }
  }
  specula::linfo("Rendering image");
  std::vector<specula::intersect> intersections = func(rays);
  for (std::size_t y = 0; y < res_height; ++y) {
    for (std::size_t x = 0; x < res_width; ++x) {
      if (intersections[x + res_width * y].obj_index != -1) {
        img(x, y) = std::array<double, 3>{1.0, 1.0, 1.0};
      } else {
        img(x, y) = std::array<double, 3>{0.5, 0.5, 0.6};
      }
    }
  }

  img.write(output);

  return 0;
}
