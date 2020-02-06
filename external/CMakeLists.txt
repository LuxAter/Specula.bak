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
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${REPO_NAME} EXCLUDE_FROM_ALL)
  endif()
endmacro()

# ##############################################################################
# DEPENDENCIES
# ##############################################################################
option(SPDLOG_BUILD_SHARED "" ${BUILD_SHARED_LIBS})
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
# option(CXXOPTS_BUILD_EXAMPLES "" OFF)
# option(CXXOPTS_BUILD_TEST "" OFF)
# option(CXXOPTS_ENABLE_INSTALL "" OFF)
# option(RE2_BUILD_TESTING "" OFF)
# option(JSON_BuildTest "" OFF)
# option(JSON_Install "" OFF)
load_submodule(spdlog)
load_submodule(fmt)
# load_submodule(cxxopts)
load_submodule(glm)
# load_submodule(filesystem)
# load_submodule(json)
load_submodule(glfw)
# clone_git(stb)
clone_git(imgui)