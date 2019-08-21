#include <sol/sol.hpp>

int main(int argc, char *argv[]) {
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::math);
  lua.script_file("resources/test.lua");
  return 0;
}
