# setup glfw and glad library
set(GLFW_BUILD_DOCS
    OFF
    CACHE BOOL "GLFW lib only")
add_subdirectory(glfw)
add_subdirectory(glad/cmake)

# automaticly add library and include target source
glad_add_library(
  glad
  STATIC
  on
  LANGUAGE
  c
  API
  "gl:core=4.5"
  LOCATION
  "${CMAKE_CURRENT_BINARY_DIR}/glad")

# setup freetype library
add_subdirectory(freetype)

# setup GLM library for math
set(GLM_ENABLE_CXX_17)
add_subdirectory(glm)

# setup LIBPNG for texturing
set(PNG_SHARED OFF)
set(PNG_STATIC
    ON
    CACHE BOOL "" FORCE)
set(PNG_EXECUTABLES
    OFF
    CACHE BOOL "" FORCE) # we only want lib
set(PNG_TESTS
    OFF
    CACHE BOOL "" FORCE) # we only want lib
set(SKIP_INSTALL_ALL
    OFF
    CACHE BOOL "" FORCE) # we only want lib
add_subdirectory(libpng)

# setup spdlog library for logging
add_subdirectory(spdlog)
# Target-specific compile options to suppress warnings for vendor
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(spdlog PUBLIC -Wno-unused)
endif()

# setup OpenAL library for Sound library
set(ALSOFT_EXAMPLES OFF)
add_subdirectory(openal)

# setup YAMl library for configuration file
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(yaml-cpp)

# add include from library
target_include_directories(
  ${PROJECT_NAME}
  PRIVATE glfw/include
          ${CMAKE_CURRENT_BINARY_DIR}/glad/include
          freetype/include
          glm
          libpng
          spdlog/include
          openal/include
          yaml-cpp/include)

# set library
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE glfw
          glad
          freetype
          glm
          png_static
          spdlog::spdlog
          OpenAL::OpenAL
          yaml-cpp::yaml-cpp)
