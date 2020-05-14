#Locate libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# OpenGL
find_package(OpenGL REQUIRED)

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "GLFW3 include found at ${GLFW3_INCLUDE_DIR}")

# GLM
find_package(GLM REQUIRED)
message(STATUS "GLM include found at ${GLM_INCLUDE_DIRS}")

#
# Build libraries from source files
#

# GLAD
set(GLAD_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/include")
set(GLAD_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/src")
add_library(GLAD "${GLAD_SOURCE_DIR}/glad.c")

# STB_IMAGE
set(STB_IMAGE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/include")
set(STB_IMAGE_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external-dependencies/src")
add_library(STB_IMAGE "${STB_IMAGE_SOURCE_DIR}/stb_image.cpp")

# Include libraries
include_directories("${GLFW3_INCLUDE_DIR}" "${GLM_INCLUDE_DIRS}" "${GLAD_INCLUDE_DIR}" "${STB_IMAGE_INCLUDE_DIR}")

# Linking
set(OPENGL_LIBS "${GLFW3_LIBRARY}" opengl32 GLAD STB_IMAGE)
