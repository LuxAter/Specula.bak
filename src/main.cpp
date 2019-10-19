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

  std::size_t ax, ay;
  sscanf(aspect_ratio.c_str(), "%lu:%lu", &ax, &ay);
  res_height = res_width * ay / ax;

  double fov = M_PI / 2.0;

  std::vector<std::shared_ptr<specula::Primative>> objs;
  std::vector<std::shared_ptr<specula::Primative>> *objs_ptr = &objs;
  std::vector<std::shared_ptr<specula::Material>> mats;
  std::vector<std::shared_ptr<specula::Material>> *mats_ptr = &mats;

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
      &specula::LuaPrimative::rotate_zyx, "rotate",
      &specula::LuaPrimative::rotate, "scale", &specula::LuaPrimative::scale,
      "translate", &specula::LuaPrimative::translate,
      sol::meta_function::addition,
      [objs_ptr](const specula::LuaPrimative &lhs,
                 const specula::LuaPrimative &rhs) {
        return specula::LuaUnion(lhs, rhs, objs_ptr);
      });

  lua.set_function("SolidAngle", [objs_ptr](const float &a, const float &b,
                                            const float &ra) mutable {
    return specula::LuaSolidAngle(a, b, ra, objs_ptr);
  });
  lua.set_function("Box", [objs_ptr](const float &w, const float &l,
                                     const float &h) mutable {
    return specula::LuaBox(w, l, h, objs_ptr);
  });
  lua.set_function("RoundBox",
                   [objs_ptr](const float &r, const float &w, const float &l,
                              const float &h) mutable {
                     return specula::LuaRoundBox(w, l, h, r, objs_ptr);
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
  lua.set_function("Cone", [objs_ptr](const float &r1, const float &r2,
                                      const float &h) mutable {
    return specula::LuaCone(h, r1, r2, objs_ptr);
  });
  lua.set_function("InfiniteCone", [objs_ptr](const float &alpha) mutable {
    return specula::LuaInfiniteCone(alpha, objs_ptr);
  });
  lua.set_function("Cylinder",
                   [objs_ptr](const float &h, const float &r) mutable {
                     return specula::LuaCylinder(h, r, objs_ptr);
                   });
  lua.set_function(
      "RoundedCylinder",
      [objs_ptr](const float &ra, const float &rb, const float &h) mutable {
        return specula::LuaRoundedCylinder(ra, rb, h, objs_ptr);
      });
  lua.set_function("InfiniteCylinder", [objs_ptr](const float &r) mutable {
    return specula::LuaInfiniteCylinder(r, objs_ptr);
  });
  lua.set_function("Link", [objs_ptr](const float &len, const float &r_outer,
                                      const float &r_inner) mutable {
    return specula::LuaLink(len, r_outer, r_inner, objs_ptr);
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

  lua.script_file(lua_source);

  specula::render(objs, mats, 256, fov, res_width, res_height, output, 0,
                  false);
  return 0;
}
