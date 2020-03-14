# ##############################################################################
# SOURCE FILES
# ##############################################################################
file(GLOB_RECURSE SOURCES "${SPECULA_SOURCE_DIR}/docs/*.md" "${SPECULA_SOURCE_DIR}/lib/include/*.hpp")

file(GLOB_RECURSE RESOURCE "${SPECULA_SOURCE_DIR}/docs/icons/*.svg")

foreach(FILE_PATH IN LISTS SOURCES)
  set(DOXYGEN_INPUT "${DOXYGEN_INPUT} \\\n\"${FILE_PATH}\"")
endforeach()
foreach(FILE_PATH IN LISTS RESOURCE)
  set(DOXYGEN_RESOURCE "${DOXYGEN_RESOURCE} \\\n\"${FILE_PATH}\"")
endforeach()
configure_file(Doxyfile.in Doxyfile @ONLY)

# ##############################################################################
# STYLE COMPILER
# ##############################################################################
find_program(LESSC_EXECUTABLE lessc)

if(NOT LESSC_EXECUTABLE STREQUAL "LESS-NOTFOUND")
  add_custom_command(
    OUTPUT "${SPECULA_SOURCE_DIR}/docs/extra.css"
    COMMAND ${LESSC_EXECUTABLE} --compress ${SPECULA_SOURCE_DIR}/docs/extra.less
            > ${SPECULA_SOURCE_DIR}/docs/extra.css
    COMMENT "Generating extra.css"
    DEPENDS ${SPECULA_SOURCE_DIR}/docs/extra.less
    VERBATIM)
endif()


# ##############################################################################
# DOCUMENTATION GENERATOR
# ##############################################################################
add_custom_target(
  docs
  "${DOXYGEN_EXECUTABLE}"
  DEPENDS ${DOXYGEN_DEPENDS} "${SPECULA_SOURCE_DIR}/docs/extra.css"
  WORKING_DIRECTORY "${SPECULA_BINARY_DIR}/docs"
  COMMENT "Generating Doxygen documentation"
  VERBATIM)
