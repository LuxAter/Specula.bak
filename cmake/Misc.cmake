# ------------------------------------------------------------------------------
# -- Misc (no change needed).
# ------------------------------------------------------------------------------
# -- Have CMake parse the config file, generating the config header, with
# correct definitions. Here only used to make version number available to the
# source code. Include "exampleConfig.h" (no .in suffix) in the source.
configure_file("${PROJECT_SOURCE_DIR}/include/version.hpp.in"
               "${PROJECT_BINARY_DIR}/version.hpp")
# add the binary tree to the search path for include files so that we will find
# exampleConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# Ask CMake to output a compile_commands.json file for use with things like Vim
# YCM.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  execute_process(COMMAND ${CMAKE_COMMAND}
                          -E
                          copy_if_different
                          ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
                          ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)
endif()
