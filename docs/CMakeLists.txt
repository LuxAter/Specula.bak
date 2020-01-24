# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES
    "docs/main.md"
    "include/specula/error.hpp"
    "include/specula/global.hpp"
    "include/specula/log.hpp"
    "include/specula/math.hpp"
    "include/specula/specula.hpp"
    "include/specula/version.hpp"
    "include/specula/transform/transform.hpp"
    "include/specula/transform/animated_transform.hpp"
    "include/specula/math/bounds.hpp"
    "include/specula/math/common.hpp"
    "include/specula/math/geometric.hpp"
    "include/specula/math/matrix.hpp"
    "include/specula/math/normal.hpp"
    "include/specula/math/point.hpp"
    "include/specula/math/quaternion.hpp"
    "include/specula/math/ray.hpp"
    "include/specula/math/ray_differential.hpp"
    "include/specula/math/vector.hpp"
    "include/specula/math/bounds/bounds2.hpp"
    "include/specula/math/bounds/bounds3.hpp"
    "include/specula/math/bounds/bounds4.hpp"
    "include/specula/math/matrix/matrix2x2.hpp"
    "include/specula/math/matrix/matrix3x3.hpp"
    "include/specula/math/matrix/matrix4x4.hpp"
    "include/specula/math/normal/normal2.hpp"
    "include/specula/math/normal/normal3.hpp"
    "include/specula/math/normal/normal4.hpp"
    "include/specula/math/point/point2.hpp"
    "include/specula/math/point/point3.hpp"
    "include/specula/math/point/point4.hpp"
    "include/specula/math/vector/vector2.hpp"
    "include/specula/math/vector/vector3.hpp"
    "include/specula/math/vector/vector4.hpp")

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
