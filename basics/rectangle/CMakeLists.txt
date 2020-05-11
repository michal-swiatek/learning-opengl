add_executable(rectangle rectangle.cpp)
target_link_libraries(rectangle ${OPENGL_LIBS})

# Adding shaders to build and executable directory

if(CMAKE_GENERATOR MATCHES "Visual Studio")
add_custom_command(
        TARGET rectangle POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${BUILD_DESTINATION}/shaders"
        COMMAND if $<CONFIG:Debug> neq 0 ("${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/Debug/shaders")
        COMMAND if $<CONFIG:Release> neq 0 ("${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/Release/shaders")
        DEPENDS "${SHADERS_SOURCE}"
        COMMENT "copied shaders directory from ${SHADERS_SOURCE} to ${BUILD_DESTINATION}/shaders"
        COMMENT "copied shaders directory from ${SHADERS_SOURCE} to ${BUILD_DESTINATION}/CONFIG/shaders"
)

# Set debugging directory
set_target_properties(rectangle PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>")
else()
    add_custom_command(
            TARGET rectangle POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${BUILD_DESTINATION}/shaders"
            COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/shaders"
            DEPENDS "${SHADERS_SOURCE}"
            COMMENT "copied shaders directory from ${SHADERS_SOURCE} to ${BUILD_DESTINATION}/shaders"
            COMMENT "copied shaders directory from ${SHADERS_SOURCE} to ${BUILD_DESTINATION}/CONFIG/shaders"
    )
endif()
