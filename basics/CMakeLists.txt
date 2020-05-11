cmake_minimum_required(VERSION 3.15)

project(basics)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED False)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories(shaders)

# Adding shaders to build directory
set(SHADERS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(BUILD_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
set(RUNTIME_DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

message(STATUS "SHADERS_SOURCE set to ${SHADERS_SOURCE}")
message(STATUS "BUILD_DESTINATION set to ${BUILD_DESTINATION}")
message(STATUS "RUNTIME_DESTINATION set to ${RUNTIME_DESTINATION}")

# Rectangle project
add_subdirectory(rectangle)
