macro(LOAD_EXTERNAL REPO_NAME)
  string(TOUPPER ${REPO_NAME} MODULE_NAME)
  if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/REPO_NAME}/.git)
    execute_process(
      COMMAND git submodule update --init --
              ${CMAKE_CURRENT_SOURCE_DIR}/${REPO_NAME}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    set(${MODULE_NAME}_FOUND TRUE)
  elseif(NOT GIT_FOUND)
    message(FATAL_ERROR "Git is required to clone ${MODULE_NAME}")
  else()
    set(${MODULE_NAME}_FOUND TRUE)
  endif()
endmacro()

macro(install)

endmacro()

load_external(spdlog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/spdlog EXCLUDE_FROM_ALL)
load_external(libpng)
option(PNG_STATIC "" OFF)
option(PNG_TESTS "" OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libpng EXCLUDE_FROM_ALL)
load_external(libjpeg-turbo)
option(ENABLE_SHARED "" ON)
option(WITH_JPEG8 "" ON)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libjpeg-turbo EXCLUDE_FROM_ALL)
load_external(sol2)
option(SOL2_LUA_VERSION "" "5.1.5")
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sol2 EXCLUDE_FROM_ALL)
load_external(filesystem)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/filesystem EXCLUDE_FROM_ALL)
load_external(CLI11)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/CLI11 EXCLUDE_FROM_ALL)
load_external(fmt)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/fmt EXCLUDE_FROM_ALL)

load_external(luajit)
add_custom_target(
  luajit
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/luajit
          ${CMAKE_CURRENT_BINARY_DIR}/luajit
  COMMAND cd ${CMAKE_CURRENT_BINARY_DIR}/luajit && make install
          PREFIX=${CMAKE_CURRENT_BINARY_DIR}/luajit)
add_library(luajit_static STATIC IMPORTED)
set_property(
  TARGET luajit_static
  PROPERTY IMPORTED_LOCATION
           ${CMAKE_CURRENT_BINARY_DIR}/luajit/lib/libluajit-5.1.a)
add_dependencies(luajit_static luajit)
