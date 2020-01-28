# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES
    docs/main.md
    include/specula/error.hpp
    include/specula/global.hpp
    include/specula/log.hpp
    include/specula/math.hpp
    include/specula/specula.hpp
    include/specula/version.hpp
    include/specula/transform/transform.hpp
    include/specula/transform/animated_transform.hpp
    include/specula/math/bounds.hpp
    include/specula/math/common.hpp
    include/specula/math/geometric.hpp
    include/specula/math/matrix.hpp
    include/specula/math/normal.hpp
    include/specula/math/point.hpp
    include/specula/math/quaternion.hpp
    include/specula/math/ray.hpp
    include/specula/math/ray_differential.hpp
    include/specula/math/vector.hpp
    include/specula/math/bounds/bounds2.hpp
    include/specula/math/bounds/bounds3.hpp
    include/specula/math/bounds/bounds4.hpp
    include/specula/math/matrix/matrix2x2.hpp
    include/specula/math/matrix/matrix3x3.hpp
    include/specula/math/matrix/matrix4x4.hpp
    include/specula/math/normal/normal2.hpp
    include/specula/math/normal/normal3.hpp
    include/specula/math/normal/normal4.hpp
    include/specula/math/point/point2.hpp
    include/specula/math/point/point3.hpp
    include/specula/math/point/point4.hpp
    include/specula/math/vector/vector2.hpp
    include/specula/math/vector/vector3.hpp
    include/specula/math/vector/vector4.hpp)

set(RESOURCES arrow.png icons/folder-open-solid.svg icons/folder-solid.svg icons/file-alt-solid.svg icons/arrow.svg icons/caret-down-sold.svg caret-right-sold.svg)

foreach(PATH IN LISTS SOURCES)
  list(APPEND DOXYGEN_DEPENDS "${SPECULA_SOURCE_DIR}/${PATH}")
endforeach()
foreach(PATH IN LISTS SOURCES)
  set(DOXYGEN_INPUT "${DOXYGEN_INPUT} \\\n\"${SPECULA_SOURCE_DIR}/${PATH}\"")
endforeach()
foreach(PATH IN LISTS RESOURCES)
  set(DOXYGEN_RESOURCES
      "${DOXYGEN_RESOURCES} \\\n\"${SPECULA_SOURCE_DIR}/docs/${PATH}\"")
endforeach()
configure_file(Doxyfile.in Doxyfile @ONLY)

# ##############################################################################
# EXECUTABLES
# ##############################################################################
find_program(LESSC_EXECUTABLE lessc)

# ##############################################################################
# TARGET
# ##############################################################################
if(NOT LESSC_EXECUTABLE STREQUAL "LESS-NOTFOUND")
  add_custom_command(
    OUTPUT "${SPECULA_SOURCE_DIR}/docs/extra.css"
    COMMAND ${LESSC_EXECUTABLE} --compress ${SPECULA_SOURCE_DIR}/docs/extra.less
            > ${SPECULA_SOURCE_DIR}/docs/extra.css
    COMMENT "Generating extra.css"
    DEPENDS "${SPECULA_SOURCE_DIR}/docs/extra.less"
    VERBATIM)
endif()
add_custom_target(
  docs
  "${DOXYGEN_EXECUTABLE}"
  DEPENDS ${DOXYGEN_DEPENDS} "${SPECULA_SOURCE_DIR}/docs/extra.css"
  WORKING_DIRECTORY "${SPECULA_BINARY_DIR}/docs"
  COMMENT "Generating Doxygen documentation"
  VERBATIM)
