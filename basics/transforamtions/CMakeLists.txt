add_executable(transformations transformations.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(transformations ${OPENGL_LIBS})

# Adding shaders to build and executable directory
add_custom_command(
        TARGET transformations POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${BUILD_DESTINATION}/shaders"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/shaders"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${RESOURCES_SOURCE}" "${RUNTIME_DESTINATION}/resources"
)

# Set working directory for MS Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(transformations PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()