# ##############################################################################
# Fetch Macro
# ##############################################################################
find_package(Git REQUIRED)
macro(load_submodule REPO_NAME)
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
  if(${MODULE_NAME}_FOUND)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${REPO_NAME} EXCLUDE_FROM_ALL)
  endif()
endmacro()

# ##############################################################################
# DEPENDENCIES
# ##############################################################################
option(SPDLOG_BUILD_SHARED "" ${BUILD_SHARED_LIBS})
load_submodule(spdlog)
