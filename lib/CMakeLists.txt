# ##############################################################################
# SOURCE FILES
# ##############################################################################
set(SOURCES src/dev/log.cpp)
configure_file("${SPECULA_SOURCE_DIR}/lib/include/specula/version.hpp.in"
  "${SPECULA_SOURCE_DIR}/lib/include/specula/version.hpp")

# ##############################################################################
# STATIC LIBRARY
# ##############################################################################
if(SPECULA_BUILD_STATIC_LIBS)
  add_library(specula-static STATIC ${SOURCES})
  add_library(specula::static ALIAS specula-static)

  target_include_directories(specula-static PUBLIC ${SPECULA_SOURCE_DIR}/lib/include)
  target_include_directories(specula-static PRIVATE ${SPECULA_SOURCE_DIR}/lib/include/specula)

  set_target_properties(specula-static PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)

  target_link_libraries(specula-static PUBLIC spdlog fmt::fmt)
  install(TARGETS specula-static ARCHIVE DESTINATION lib)
endif()

# ##############################################################################
# SHARED LIBRARY
# ##############################################################################
if(SPECULA_BUILD_SHARED_LIBS)
  add_library(specula-shared SHARED ${SOURCES})
  add_library(specula::shared ALIAS specula-shared)

  target_include_directories(specula-shared PUBLIC ${SPECULA_SOURCE_DIR}/lib/include)
  target_include_directories(specula-shared PRIVATE ${SPECULA_SOURCE_DIR}/lib/include/specula)

  set_target_properties(specula-shared PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS OFF)

  target_link_libraries(specula-shared PUBLIC spdlog fmt::fmt)
  install(TARGETS specula-shared LIBRARY DESTINATION lib)
endif()

# ##############################################################################
# ALIASED LIBRARY
# ##############################################################################
if(SPECULA_BUILD_SHARED_LIBS)
  add_library(specula::specula ALIAS specula-shared)
elseif(SPECULA_BUILD_STATIC_LIBS)
  add_library(specula::specula ALIAS specula-static)
endif()
