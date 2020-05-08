cmake_minimum_required(VERSION 3.15)

project(learning_opengl VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED False)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Find external dependencies
# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "GLFW3 include found at ${GLFW3_INCLUDE_DIR}, ${GLFW3_LIBRARY}, ${GLFW3_FOUND}")

# GLAD
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/include")
set(GLAD_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/src")
add_library(GLAD "${GLAD_SOURCE_DIR}/glad.c")

# Setting include directories
include_directories("${CMAKE_SOURCE_DIR}/include" "${GLFW3_INCLUDE_DIR}" "${GLAD_INCLUDE_DIR}")

# Create main target
add_executable(learning_opengl main.cpp)

# Project version available only in main project
configure_file(LearningOpenGLConfig.h.in LearningOpenGLConfig.h)
target_include_directories(learning_opengl PUBLIC "${PROJECT_BINARY_DIR}")

# Linking
set(LIBS "${GLFW3_LIBRARY}" opengl32 GLAD)

target_link_libraries(learning_opengl ${LIBS})

add_subdirectory(creating-window)

install(TARGETS learning_opengl DESTINATION C:/Users/PABLICITO/CLionProjects/learning-opengl/bin)