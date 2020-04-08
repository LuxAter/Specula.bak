# ##############################################################################
# Fetch Macro
# ##############################################################################
include(ExternalProject)
find_package(Git REQUIRED)
macro(clone_git REPO_NAME)
  string(TOUPPER ${REPO_NAME} MODULE_NAME)
  if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${REPO_NAME}/.git)
    execute_process(
      COMMAND
        git submodule update --init --recursive --
        ${CMAKE_CURRENT_SOURCE_DIR}/${REPO_NAME})
  elseif(NOT GIT_FOUND)
    message(FATAL_ERROR "Git is required for submodules ${MODULE_NAME}")
  else()
    set(${MODULE_NAME}_FOUND TRUE)
  endif()
endmacro()
macro(load_submodule REPO_NAME)
  clone_git(${REPO_NAME})
  string(TOUPPER ${REPO_NAME} MODULE_NAME)
  if(${MODULE_NAME}_FOUND)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${REPO_NAME})
  endif()
endmacro()

# ##############################################################################
# DEPENDENCIES
# ##############################################################################
set(SPDLOG_BUILD_SHARED ${SPECULA_BUILD_SHARED_LIBS} CACHE BOOL "")
set(OIIO_BUILD_TOOLS OFF CACHE BOOL "")
set(OIIO_BUILD_TESTS OFF CACHE BOOL "")
set(BUILD_DOCS OFF CACHE BOOL "")
set(INSTALL_DOCS OFF CACHE BOOL "")
set(INSTALL_FONTS OFF CACHE BOOL "")
set(USE_PYTHON OFF CACHE BOOL "")
set(USE_OPENGL OFF CACHE BOOL "")

load_submodule(spdlog)
load_submodule(fmt)
load_submodule(Catch2)

clone_git(CImg)
add_library(CImg INTERFACE)
target_include_directories(CImg INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/CImg/")
add_library(CImg::CImg ALIAS CImg)
