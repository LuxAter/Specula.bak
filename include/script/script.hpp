#ifndef SPECULA_SCRIPT_HPP_
#define SPECULA_SCRIPT_HPP_

#include "script_class.hpp"
#include "lua_script.hpp"
#include "chai_script.hpp"

#include "../filesystem.hpp"

namespace specula {
  namespace script {
    inline std::shared_ptr<Script> load_script(const std::string_view& script){
      fs::path script_path(script);
      if(script_path.extension() == ".chai")
        return std::make_shared<ChaiScript>(script_path);
      else if (script_path.extension() == ".lua")
        return std::make_shared<LuaScript>(script_path);
    }
  } // namespace script
} // namespace specula

#endif  // SPECULA_SCRIPT_HPP_
