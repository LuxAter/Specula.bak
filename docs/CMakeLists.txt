find_package(Doxygen)
if(DOXYGEN)
  # ############################################################################
  # SOURCE FILES
  # ############################################################################
  file(GLOB_RECURSE SOURCES "${SPECULA_SOURCE_DIR}/docs/*.md"
       "${SPECULA_SOURCE_DIR}/include/*.hpp" "${SPECULA_SOURCE_DIR}/cli/*.hpp")
  list(APPEND SOURCES "${SPECULA_SOURCE_DIR}/README.md")

  file(GLOB_RECURSE RESOURCE "${SPECULA_SOURCE_DIR}/docs/icons/*.svg")

  foreach(FILE_PATH IN LISTS SOURCES)
    set(DOXYGEN_INPUT "${DOXYGEN_INPUT} \\\n\"${FILE_PATH}\"")
  endforeach()
  foreach(FILE_PATH IN LISTS RESOURCE)
    set(DOXYGEN_RESOURCE "${DOXYGEN_RESOURCE} \\\n\"${FILE_PATH}\"")
  endforeach()
  configure_file(Doxyfile.in Doxyfile @ONLY)

  # ############################################################################
  # STYLE COMPILER
  # ############################################################################
  find_program(LESSC_EXECUTABLE "lessc")

  if(NOT LESSC_EXECUTABLE STREQUAL "LESS-NOTFOUND")
    add_custom_command(
      OUTPUT "${SPECULA_SOURCE_DIR}/docs/doxygen/extra.css"
      COMMAND
        ${LESSC_EXECUTABLE} --compress
        ${SPECULA_SOURCE_DIR}/docs/doxygen/extra.less >
        ${SPECULA_SOURCE_DIR}/docs/doxygen/extra.css
      COMMENT "Generating extra.css"
      DEPENDS ${SPECULA_SOURCE_DIR}/docs/doxygen/extra.less
      VERBATIM)
  endif()

  # ############################################################################
  # DOCUMENTATION GENERATOR
  # ############################################################################
  add_custom_target(
    docs
    "${DOXYGEN_EXECUTABLE}"
    DEPENDS ${DOXYGEN_DEPENDS} "${SPECULA_SOURCE_DIR}/docs/doxygen/extra.css"
    WORKING_DIRECTORY "${SPECULA_BINARY_DIR}/docs"
    COMMENT "Generating Doxygen documentation"
    VERBATIM)
endif()

# TODO: Add documentation coverage reporting using coverxygen
