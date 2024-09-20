cmake_minimum_required(VERSION 3.29.6)
project(
  VerdantValey
  VERSION 0.1.0
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      Debug
      CACHE
        STRING
        "Choose the type of build (Debug, Release, RelWithDebInfo, MinSizeRel)"
        FORCE)
endif()

# Configure compiler flags for different build types
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# Output directory for generated headers
set(SHADER_OUTPUT_DIR "${CMAKE_BINARY_DIR}/include/generated")
file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

# glsl to c header tools
add_executable(glsl_to_header tools/glsl_to_header.cpp)

# GLSL files
set(SHADERS ${CMAKE_SOURCE_DIR}/shaders/vertex.glsl
            ${CMAKE_SOURCE_DIR}/shaders/fragment.glsl)

# Custom command to convert GLSL to C headers using xxd
foreach(SHADER ${SHADERS})
  get_filename_component(SHADER_NAME ${SHADER} NAME_WE)

  set(CUSTOM_VARIABLE_NAME "g_${SHADER_NAME}_shader_data")
  set(HEADER_FILE "${SHADER_OUTPUT_DIR}/${SHADER_NAME}_shader.h")

  add_custom_command(
    OUTPUT ${HEADER_FILE}
    COMMAND glsl_to_header ${SHADER} ${HEADER_FILE} ${CUSTOM_VARIABLE_NAME}
    DEPENDS glsl_to_header ${SHADER}
    COMMENT "Converting ${SHADER} to C header with custom variable name")

  list(APPEND GENERATED_HEADERS ${HEADER_FILE})
endforeach()

# Add generated headers to the project
add_custom_target(GenerateShaderHeaders ALL DEPENDS ${GENERATED_HEADERS})

# Include the generated shader headers in the build
include_directories(${SHADER_OUTPUT_DIR})

# main include directories
include_directories(include)

add_subdirectory(src)
add_subdirectory(vendor)

add_dependencies(${PROJECT_NAME} GenerateShaderHeaders)
