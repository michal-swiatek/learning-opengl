cmake_minimum_required(VERSION 3.16)

project(examples)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<CONFIG>")

include_directories(shaders)

# Adding shaders to build directory
set(SHADERS_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/shaders")

set(BUILD_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
set(RUNTIME_DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

macro(COPY_RESOURCES TARGET_NAME COPY_COMMAND)
    add_custom_command(
            TARGET ${TARGET_NAME}  POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E ${COPY_COMMAND} "${SHADERS_SOURCE}" "${BUILD_DESTINATION}/shaders"
            COMMAND "${CMAKE_COMMAND}" -E ${COPY_COMMAND} "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/shaders"
    )
endmacro(COPY_RESOURCES)

# Setting project files
set(CURRENT_INCLUDE_FILES ${UTILITY_INCLUDE_FILES})
set(CURRENT_SRC_FILES ${UTILITY_SRC_FILES})

# Add targets
add_subdirectory(box_gif)