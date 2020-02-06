# ##############################################################################
# TARGET
# ##############################################################################
add_executable(binary_to_compressed binary_to_compressed.cpp)
set_target_properties(
  binary_to_compressed
  PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)
