#include "script/chai_script.hpp"

#include <string_view>

#include "filesystem.hpp"
#include "script/script_class.hpp"

specula::script::ChaiScript::ChaiScript(const fs::path &script_path)
    : Script(script_path) {}

bool specula::script::ChaiScript::exec() { return false; }
