#include "script/lua_script.hpp"

#include <string_view>
#include <string>

#include "filesystem.hpp"
#include "object/object.hpp"
#include "script/script_class.hpp"

specula::script::LuaScript::LuaScript(const fs::path &script_path)
    : Script(script_path) {
  lua_.open_libraries();
  auto ns = lua_["specula"].get_or_create<sol::table>();
  ns.new_usertype<specula::object::Object>(
      "Object", "rotate_x", &specula::object::Object::rotate_x, "rotate_y",
      &specula::object::Object::rotate_y, "rotate_z",
      &specula::object::Object::rotate_z, "translate",
      &specula::object::Object::translate, "scale",
      &specula::object::Object::scale);
  ns.new_usertype<specula::object::Sphere>("Sphere");
}

bool specula::script::LuaScript::exec() {
  lua_.script_file(this->script_path_.string());
  return true;
}
