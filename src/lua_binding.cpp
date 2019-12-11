#include "lua_binding.hpp"

#include <sol/sol.hpp>

#include "specula.hpp"

glm::vec2 table_to_vec2(const sol::table &t) {
  return glm::vec2(t.get_or("1", 0.0f), t.get_or("2", 0.0f));
}
glm::vec2 float_to_vec2(const float &x, const float &y) {
  return glm::vec2(x, y);
}
glm::vec3 table_to_vec3(const sol::table &t) {
  return glm::vec3(t.get_or("1", 0.0f), t.get_or("2", 0.0f),
                   t.get_or("3", 0.0f));
}
glm::vec3 float_to_vec3(const float &x, const float &y, const float &z) {
  return glm::vec3(x, y, z);
}
glm::vec4 table_to_vec4(const sol::table &t) {
  return glm::vec4(t.get_or("1", 0.0f), t.get_or("2", 0.0f),
                   t.get_or("3", 0.0f), t.get_or("4", 0.0f));
}
glm::vec4 float_to_vec4(const float &x, const float &y, const float &z,
                        const float &w) {
  return glm::vec4(x, y, z, w);
}

void load_bindings(sol::state &lua) {
  lua.new_usertype<glm::vec2>("vec2", "new",
                              sol::overload(table_to_vec2, float_to_vec2), "x",
                              &glm::vec2::x, "y", &glm::vec2::y);
  lua.new_usertype<glm::vec3>(
      "vec3", "new", sol::overload(table_to_vec3, float_to_vec3), "x",
      &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z, "r", &glm::vec3::x,
      "g", &glm::vec3::y, "b", &glm::vec3::z);
  lua.new_usertype<glm::vec4>("vec4", "new",
                              sol::overload(table_to_vec4, float_to_vec4), "x",
                              &glm::vec4::x, "y", &glm::vec4::y, "z",
                              &glm::vec4::z, "w", &glm::vec4::w);

  auto camera = lua["camera"].get_or_create<sol::table>(sol::new_table());
  camera.set_function("set_fov",
                      sol::overload(sol::resolve<void(const float &)>(
                          specula::set_camera_fov)));
  camera.set_function(
      "set_pos",
      sol::overload(
          sol::resolve<void(const glm::vec3 &)>(specula::set_camera_pos),
          sol::resolve<void(const float &, const float &, const float &)>(
              specula::set_camera_pos)));
  camera.set_function(
      "set_center",
      sol::overload(
          sol::resolve<void(const glm::vec3 &)>(specula::set_camera_center),
          sol::resolve<void(const float &, const float &, const float &)>(
              specula::set_camera_center)));
  camera.set_function(
      "set_direction",
      sol::overload(
          sol::resolve<void(const glm::vec3 &)>(specula::set_camera_direction),
          sol::resolve<void(const float &, const float &, const float &)>(
              specula::set_camera_direction)));
  camera.set_function(
      "set_up",
      sol::overload(
          sol::resolve<void(const glm::vec3 &)>(specula::set_camera_up),
          sol::resolve<void(const float &, const float &, const float &)>(
              specula::set_camera_up)));

  lua.new_usertype<specula::Material>(
      "Material", "Emissive",
      sol::factories(
          sol::resolve<std::shared_ptr<specula::Material>(
              const float &, float, float, float)>(specula::Material::Emissive),
          sol::resolve<std::shared_ptr<specula::Material>(float, glm::vec3)>(
              specula::Material::Emissive)),
      "Diffuse",
      sol::factories(
          sol::resolve<std::shared_ptr<specula::Material>(
              const float &, const float &, const float &)>(
              specula::Material::Diffuse),
          sol::resolve<std::shared_ptr<specula::Material>(glm::vec3)>(
              specula::Material::Diffuse)),
      "Specular", sol::factories(specula::Material::Specular), "Transparent",
      sol::factories(specula::Material::Transparent), "type",
      &specula::Material::type, "base_color", &specula::Material::base_color,
      "emission", &specula::Material::emission, "ior", &specula::Material::ior);
  lua["Material"]["Type"] =
      lua.create_table_with("DIFFUSE", specula::Material::Type::DIFFUSE,
                            "SPECULAR", specula::Material::Type::SPECULAR,
                            "REFRACTIVE", specula::Material::Type::TRANSPARENT);

  lua.new_usertype<specula::ObjectBase>(
      "Object", "gpu_enabled", &specula::ObjectBase::gpu_enabled, "cpu_enabled",
      &specula::ObjectBase::cpu_enabled);

  ObjectBinding(
      Sphere,
      sol::factories(
          sol::resolve<std::shared_ptr<specula::object::Sphere>(const float &)>(
              &specula::Sphere)),
      "radius", &specula::object::Sphere::radius);
  ObjectBinding(
      Plane,
      sol::factories(
          sol::resolve<std::shared_ptr<specula::object::Plane>(
              const float &, const float &, const float &, const float &)>(
              &specula::Plane),
          sol::resolve<std::shared_ptr<specula::object::Plane>(
              const glm::vec4 &)>(&specula::Plane)),
      "normal", &specula::object::Plane::normal);
  ObjectBinding(
      Box,
      sol::factories(
          sol::resolve<std::shared_ptr<specula::object::Box>(
              const float &, const float &, const float &)>(&specula::Box),
          sol::resolve<std::shared_ptr<specula::object::Box>(
              const glm::vec3 &)>(&specula::Box)),
      "dimensions", &specula::object::Box::dimensions);
  ObjectBinding(
      Torus,
      sol::factories(sol::resolve<std::shared_ptr<specula::object::Torus>(
                         const float &, const float &)>(&specula::Torus),
                     sol::resolve<std::shared_ptr<specula::object::Torus>(
                         const glm::vec2 &)>(&specula::Torus)),
      "torus", &specula::object::Torus::torus);
  ObjectBinding(
      Cylinder,
      sol::factories(sol::resolve<std::shared_ptr<specula::object::Cylinder>(
                         const float &, const float &)>(&specula::Cylinder)),
      "radius", &specula::object::Cylinder::radius, "height",
      &specula::object::Cylinder::height);

  JoinBinding(
      "UnionBase", Union,
      sol::factories(
          sol::resolve<std::shared_ptr<specula::object::Union>(
              const std::shared_ptr<specula::ObjectBase> &,
              const std::shared_ptr<specula::ObjectBase> &)>(&specula::Union)));
  lua["Union"] = [](const std::shared_ptr<specula::ObjectBase> &a,
                    const std::shared_ptr<specula::ObjectBase> &b) {
    return specula::Union(a, b);
  };
  JoinBinding("IntersectionBase", Intersection,
              sol::factories(
                  sol::resolve<std::shared_ptr<specula::object::Intersection>(
                      const std::shared_ptr<specula::ObjectBase> &,
                      const std::shared_ptr<specula::ObjectBase> &)>(
                      &specula::Intersection)));
  lua["Intersection"] = [](const std::shared_ptr<specula::ObjectBase> &a,
                           const std::shared_ptr<specula::ObjectBase> &b) {
    return specula::Intersection(a, b);
  };
  lua["Intersect"] = [](const std::shared_ptr<specula::ObjectBase> &a,
                        const std::shared_ptr<specula::ObjectBase> &b) {
    return specula::Intersection(a, b);
  };
  JoinBinding(
      "SubtractionBase", Subtraction,
      sol::factories(sol::resolve<std::shared_ptr<specula::object::Subtraction>(
                         const std::shared_ptr<specula::ObjectBase> &,
                         const std::shared_ptr<specula::ObjectBase> &)>(
          &specula::Subtraction)));
  lua["Subtraction"] = [](const std::shared_ptr<specula::ObjectBase> &a,
                          const std::shared_ptr<specula::ObjectBase> &b) {
    return specula::Subtraction(a, b);
  };
  lua["Subtract"] = [](const std::shared_ptr<specula::ObjectBase> &a,
                       const std::shared_ptr<specula::ObjectBase> &b) {
    return specula::Subtraction(a, b);
  };
}
