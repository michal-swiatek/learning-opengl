cmake_minimum_required(VERSION 3.15)

project(basics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED False)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")

include_directories(shaders)
include_directories(resources)

# Adding shaders to build directory
set(SHADERS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(RESOURCES_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources")

set(BUILD_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
set(RUNTIME_DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Setting project files
set(CURRENT_INCLUDE_FILES ${INCLUDE_FILES})
set(CURRENT_SRC_FILES ${SRC_FILES})

# Add targets
add_subdirectory(rectangle)
add_subdirectory(texturing)
add_subdirectory(transforamtions)
