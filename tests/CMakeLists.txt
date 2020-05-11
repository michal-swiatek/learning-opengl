cmake_minimum_required(VERSION 3.15)

project(tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED False)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

# Setting project files
set(CURRENT_INCLUDE_FILES ${INCLUDE_FILES})
set(CURRENT_SRC_FILES ${SRC_FILES})

# Test external libraries
add_subdirectory(external-libraries)