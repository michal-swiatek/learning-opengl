cmake_minimum_required(VERSION 3.15)

project(learning_opengl VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED False)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>")

# Find external dependencies
# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS  "GLFW3 include found at ${GLFW3_INCLUDE_DIR}, ${GLFW3_LIBRARY}, ${GLFW3_FOUND}")

# GLAD
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/include")
set(GLAD_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/src")
add_library(GLAD "${GLAD_SOURCE_DIR}/glad.c")

# STB_IMAGE
set(STB_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/include")
set(STB_IMAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/src")
add_library(STB_IMAGE "${STB_IMAGE_SOURCE_DIR}/stb_image.cpp")

# Setting include directories
include_directories("${CMAKE_SOURCE_DIR}/include" "${GLFW3_INCLUDE_DIR}" "${GLAD_INCLUDE_DIR}" "${STB_IMAGE_INCLUDE_DIR}")

# Setting project files
set(INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/Shader.h")
set(SRC_FILES "${PROJECT_SOURCE_DIR}/src/Shader.cpp")

# Create main target
add_executable(learning_opengl main.cpp ${INCLUDE_FILES} ${SRC_FILES})

# Project version available only in main project
configure_file(LearningOpenGLConfig.h.in LearningOpenGLConfig.h)
target_include_directories(learning_opengl PUBLIC "${PROJECT_BINARY_DIR}")

# Linking
set(OPENGL_LIBS "${GLFW3_LIBRARY}" opengl32 GLAD STB_IMAGE)

target_link_libraries(learning_opengl ${OPENGL_LIBS})

# Basics project
add_subdirectory(basics)

# Tests project
add_subdirectory(tests)