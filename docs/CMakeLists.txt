# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES
    "docs/main.dox" "include/specula/specula.hpp"
    "include/specula/geometry.hpp" "include/specula/geometry/point.hpp"
    "include/specula/geometry/vector.hpp")

foreach(path IN LISTS SOURCES)
  set(DOXYGEN_INPUT "${DOXYGEN_INPUT} \\\n\"${SPECULA_SOURCE_DIR}/${path}\"")
endforeach()
configure_file(Doxyfile.in Doxyfile @ONLY)

# ##############################################################################
# TARGET
# ##############################################################################
add_custom_target(
  docs
  "${DOXYGEN_EXECUTABLE}"
  WORKING_DIRECTORY "${SPECULA_BINARY_DIR}/docs"
  COMMENT "Generating Doxygen documentation"
  VERBATIM)
