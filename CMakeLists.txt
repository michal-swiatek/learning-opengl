cmake_minimum_required(VERSION 3.16)
project(opengl)

set(CMAKE_CXX_STANDARD 20)

# Define command for copying resources
set(RESOURCES_COPY_COMMAND copy_directory)
set(RESOURCES_USE_SYMLINK False CACHE STRING "Copy resources by symlink (symlink might require admin privileges to work) (True or False)" FORCE)

if(RESOURCES_USE_SYMLINK STREQUAL "True")
    set(RESOURCES_COPY_COMMAND create_symlink)
endif()

include(external-dependencies/setup_libraries.cmake)
include(utility/utility.cmake)

add_subdirectory(tests)

add_subdirectory(basics)
