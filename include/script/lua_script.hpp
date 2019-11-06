#ifndef SPECULA_SCRIPT_LUA_HPP_
#define SPECULA_SCRIPT_LUA_HPP_

#include <string_view>

#include <sol/sol.hpp>

#include "script_class.hpp"
#include "../filesystem.hpp"

namespace specula {
namespace script {
class LuaScript : public Script {
  public:
  LuaScript(const fs::path &script_path);
  ~LuaScript() {}
  virtual bool exec();
  private:
  sol::state lua_;
};
} // namespace script
} // namespace specula

#endif // SPECULA_SCRIPT_CHAI_HPP_
