add_executable(rectangle rectangle.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(rectangle ${OPENGL_LIBS})

# Adding shaders to build and executable directory

# Set debugging directory
add_custom_command(
        TARGET rectangle POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${BUILD_DESTINATION}/shaders"
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/shaders"
)
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(rectangle PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()