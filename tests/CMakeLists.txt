cmake_minimum_required(VERSION 3.16)
project(tests)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")

# Setting project files
set(CURRENT_INCLUDE_FILES ${UTILITY_INCLUDE_FILES})
set(CURRENT_SRC_FILES ${UTILITY_SRC_FILES})

# Test external libraries
add_subdirectory(external-libraries)
add_subdirectory(general)