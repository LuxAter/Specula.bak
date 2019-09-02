#include <sol/sol.hpp>

#include <specula/log.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
  sol::state lua;
  lua.open_libraries(sol::lib::base, sol::lib::math);
  lua.script_file("resources/test.lua");

  specula::lfatal("This is very bad");
  specula::lerror("This is very bad");
  specula::lwarning("This is very bad");
  specula::lstatus("This is very bad");
  specula::lsuccess("This is very bad");
  specula::ldebug("This is very bad");
  specula::linfo("This is very bad");
  specula::lversion("This is very bad");
  return 0;
}
