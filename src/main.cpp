#include "lua.hpp"

#include "log.hpp"
#include "specula.hpp"

int main(int argc, char* argv[]) {
  specula::log::init();
  version("Specula V.%u.%u", SPECULA_VERSION_MAJOR, SPECULA_VERSION_MINOR);
  specula::log::term();
}
