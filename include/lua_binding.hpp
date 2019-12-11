#ifndef SPECULA_BIN_LUA_BINDINGS_HPP_
#define SPECULA_BIN_LUA_BINDINGS_HPP_

#include "specula.hpp"
#include <sol/sol.hpp>

#define ObjectBinding(OBJ, constructor, ...)                                   \
  lua.new_usertype<specula::object::OBJ>(                                      \
      #OBJ, constructor, "set_material",                                       \
      sol::overload(sol::resolve<std::shared_ptr<specula::object::OBJ>(        \
                        const std::shared_ptr<specula::Material> &)>(          \
                        &specula::object::OBJ::set_material),                  \
                    sol::resolve<std::shared_ptr<specula::object::OBJ>(        \
                        const specula::Material &)>(                           \
                        &specula::object::OBJ::set_material)),                 \
      "translate",                                                             \
      sol::overload(sol::resolve<std::shared_ptr<specula::object::OBJ>(        \
                        const glm::vec3 &)>(&specula::object::OBJ::translate), \
                    sol::resolve<std::shared_ptr<specula::object::OBJ>(        \
                        const float &, const float &, const float &)>(         \
                        &specula::object::OBJ::translate)),                    \
      "rotate",                                                                \
      sol::overload(                                                           \
          sol::resolve<std::shared_ptr<specula::object::OBJ>(                  \
              const float &, const glm::vec3 &)>(                              \
              &specula::object::OBJ::rotate),                                  \
          sol::resolve<std::shared_ptr<specula::object::OBJ>(                  \
              const float &, const float &, const float &, const float &)>(    \
              &specula::object::OBJ::rotate)),                                 \
      "scale",                                                                 \
      sol::overload(sol::resolve<std::shared_ptr<specula::object::OBJ>(        \
                        const glm::vec3 &)>(&specula::object::OBJ::scale),     \
                    sol::resolve<std::shared_ptr<specula::object::OBJ>(        \
                        const float &, const float &, const float &)>(         \
                        &specula::object::OBJ::scale)),                        \
      __VA_ARGS__, sol::base_classes, sol::bases<specula::ObjectBase>());

void load_bindings(sol::state &lua);

#endif // SPECULA_BIN_LUA_BINDINGS_HPP_
