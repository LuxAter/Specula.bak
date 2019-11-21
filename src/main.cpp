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

#include "cli/cli.hpp"
#include "image/image.hpp"
#include "log.hpp"
#include "material/material.hpp"
#include "object/object.hpp"
#include "renderer.hpp"
#include "version.hpp"

#include <glm/glm.hpp>
#include <sol/sol.hpp>

struct Camera {
  glm::vec3 eye_{0.0, 0.0, -1.0}, center_{0.0, 0.0, 0.0}, up_{0.0, 1.0, 0.0};
  inline Camera &eye(const float &x, const float &y, const float &z) {
    eye_ = {x, y, z};
    return *this;
  }
  inline Camera &center(const float &x, const float &y, const float &z) {
    center_ = {x, y, z};
    return *this;
  }
  inline Camera &up(const float &x, const float &y, const float &z) {
    up_ = {x, y, z};
    return *this;
  }
  inline Camera &direction(const float &x, const float &y, const float &z) {
    center_ = eye_ + glm::vec3(x, y, z);
    return *this;
  }
};

int main(int argc, char *argv[]) {
  int ret = 0;
  if ((ret = specula::cli::parse_args(argc, argv)) > 0) {
    return ret;
  } else if (ret == -1) {
    return 0;
  }
  specula::logger::initalize_logger(specula::cli::verbosity);
  LINFO("Specula v{}.{}.{}", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR,
        SPECULA_VERSION_PATCH);

  std::vector<std::shared_ptr<specula::object::Object>> objs;
  std::vector<std::shared_ptr<specula::object::Object>> *objs_ptr = &objs;
  std::size_t render_calls = 0;
  std::size_t *render_calls_ptr = &render_calls;

  sol::state lua;
  lua.open_libraries();

  lua.new_usertype<glm::vec2>("vec2", "x", &glm::vec2::x, "y", &glm::vec2::y);
  lua.new_usertype<glm::vec3>("vec3", "x", &glm::vec3::x, "y", &glm::vec3::y,
                              "z", &glm::vec3::z);
  lua.new_usertype<glm::vec4>("vec4", "x", &glm::vec4::x, "y", &glm::vec4::y,
                              "z", &glm::vec4::z, "w", &glm::vec4::w);

  lua.new_usertype<specula::material::Material>(
      "Material", "new",
      [](const float &r, const float &g, const float &b) {
        return specula::material::Material(specula::material::DIFFUSE,
                                           glm::vec3{r, g, b}, 0.0f, 1.0f);
      },
      "color", &specula::material::Material::base_color, "type",
      &specula::material::Material::type, "emission",
      &specula::material::Material::emission, "ior",
      &specula::material::Material::ior, "set_color",
      &specula::material::Material::set_color, "set_emission",
      &specula::material::Material::set_emission, "set_ior",
      &specula::material::Material::set_ior, "set_type",
      &specula::material::Material::set_type, "get_r",
      &specula::material::Material::get_r, "get_g",
      &specula::material::Material::get_g, "get_b",
      &specula::material::Material::get_b);
  lua["Material"]["Type"] =
      lua.create_table_with("DIFFUSE", specula::material::Type::DIFFUSE,
                            "SPECULAR", specula::material::Type::SPECULAR,
                            "REFRACTIVE", specula::material::Type::REFRACTIVE);

  lua.new_usertype<specula::object::Object>(
      "Object", "translate", &specula::object::Object::translate, "rotate_x",
      &specula::object::Object::rotate_x, "rotate_y",
      &specula::object::Object::rotate_y, "rotate_z",
      &specula::object::Object::rotate_z, "scale",
      &specula::object::Object::scale, "set_material",
      &specula::object::Object::set_material);

  lua.new_usertype<specula::object::Sphere>(
      "Sphere", "new", sol::factories([objs_ptr](const float &radius) {
        objs_ptr->push_back(std::make_shared<specula::object::Sphere>(radius));
        return std::dynamic_pointer_cast<specula::object::Sphere>(
            objs_ptr->back());
      }),
      "radius", &specula::object::Sphere::radius, sol::base_classes,
      sol::bases<specula::object::Object>());
  lua.new_usertype<specula::object::Box>(
      "Box", "new",
      sol::factories([objs_ptr](const float &w, const float &h,
                                const float &l) {
        objs_ptr->push_back(std::make_shared<specula::object::Box>(w, h, l));
        return std::dynamic_pointer_cast<specula::object::Box>(
            objs_ptr->back());
      }),
      "box", &specula::object::Box::box, sol::base_classes,
      sol::bases<specula::object::Object>());
  lua.new_usertype<specula::object::Cone>(
      "Cone", "new",
      sol::factories([objs_ptr](const float &h, const float &rb,
                                const float &rt) {
        objs_ptr->push_back(std::make_shared<specula::object::Cone>(h, rb, rt));
        return std::dynamic_pointer_cast<specula::object::Cone>(
            objs_ptr->back());
      }),
      "height", &specula::object::Cone::height, "radius_bottom",
      &specula::object::Cone::radius_bottom, "radius_top",
      &specula::object::Cone::radius_top, sol::base_classes,
      sol::bases<specula::object::Object>());
  lua.new_usertype<specula::object::Cylinder>(
      "Cylinder", "new",
      sol::factories([objs_ptr](const float &h, const float &r) {
        objs_ptr->push_back(std::make_shared<specula::object::Cylinder>(h, r));
        return std::dynamic_pointer_cast<specula::object::Cylinder>(
            objs_ptr->back());
      }),
      "height", &specula::object::Cylinder::height, "radius",
      &specula::object::Cylinder::radius, sol::base_classes,
      sol::bases<specula::object::Object>());
  lua.new_usertype<specula::object::Plane>(
      "Plane", "new",
      sol::factories([objs_ptr](const float &x, const float &y, const float &z,
                                const float &w) {
        objs_ptr->push_back(
            std::make_shared<specula::object::Plane>(x, y, z, w));
        return std::dynamic_pointer_cast<specula::object::Plane>(
            objs_ptr->back());
      }),
      "normal", &specula::object::Plane::normal, sol::base_classes,
      sol::bases<specula::object::Object>());
  lua.new_usertype<specula::object::Torus>(
      "Torus", "new",
      sol::factories([objs_ptr](const float &radius_big,
                                const float &radius_small) {
        objs_ptr->push_back(
            std::make_shared<specula::object::Torus>(radius_big, radius_small));
        return std::dynamic_pointer_cast<specula::object::Torus>(
            objs_ptr->back());
      }),
      "torus", &specula::object::Torus::torus, sol::base_classes,
      sol::bases<specula::object::Object>());
  lua.new_usertype<specula::object::Quad>(
      "Quad", "new",
      sol::factories(
          [objs_ptr](const float &ax, const float &ay, const float &az,
                     const float &bx, const float &by, const float &bz,
                     const float &cx, const float &cy, const float &cz,
                     const float &dx, const float &dy, const float &dz) {
            objs_ptr->push_back(std::make_shared<specula::object::Quad>(
                ax, ay, az, bx, by, bz, cx, cy, cz, dx, dy, dz));
            return std::dynamic_pointer_cast<specula::object::Quad>(
                objs_ptr->back());
          }),
      "a", &specula::object::Quad::a, "b", &specula::object::Quad::b, "c",
      &specula::object::Quad::c, "d", &specula::object::Quad::d,
      sol::base_classes, sol::bases<specula::object::Object>());

  lua.new_usertype<Camera>("Camera", "eye", &Camera::eye, "center",
                           &Camera::center, "up", &Camera::up, "direction",
                           &Camera::direction);
  lua.set("camera", Camera());
  auto camera = lua["camera"];

  lua.set_function("render", [render_calls_ptr, objs_ptr, camera]() -> bool {
    specula::fs::path file(specula::cli::output_path);
    specula::fs::path file_name = file.filename().replace_extension(""),
                      file_extension = file.extension();
    file.remove_filename();
    file.append(file_name.string());
    file.append(
        fmt::format("{}{}", *render_calls_ptr, file_extension.string()));
    (*render_calls_ptr)++;
    Camera frame_camera = camera;
    return specula::renderer::render_frame(
        file, *objs_ptr, specula::cli::spp, specula::cli::fov,
        specula::cli::resolution,
        {{-frame_camera.eye_, -frame_camera.center_, frame_camera.up_}});
  });

  lua.script_file(specula::cli::script_source);

  if (render_calls == 0) {
    Camera frame_camera = camera;
    return specula::renderer::render_frame(
        specula::fs::path(specula::cli::output_path), objs, specula::cli::spp,
        specula::cli::fov, specula::cli::resolution,
        {{frame_camera.eye_, frame_camera.center_, frame_camera.up_}});
  }

  return 0;
}
