add_executable(texturing texturing.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(texturing ${OPENGL_LIBS})

# Adding shaders to build and executable directory
add_custom_command(
        TARGET texturing POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${BUILD_DESTINATION}/shaders"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/shaders"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${RESOURCES_SOURCE}" "${RUNTIME_DESTINATION}/resources"
)

# Set working directory for MS Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(texturing PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()