add_executable(rectangle rectangle.cpp)
target_link_libraries(rectangle ${OPENGL_LIBS})

# Adding shaders to build directory
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    # Visual Studio runtime executable is placed in Debug/Release directory
    add_custom_command(
            TARGET rectangle POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${BUILD_DESTINATION}/shaders"
            COMMAND if $<CONFIG:Debug> neq 0 ("${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/Debug/shaders")
            COMMAND if $<CONFIG:Release> neq 0 ("${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/Release/shaders")
            DEPENDS "${SHADERS_SOURCE}"
            COMMENT "copied shaders directory from ${SHADERS_SOURCE} to ${BUILD_DESTINATION}/shaders"
            COMMENT "copied shaders directory from ${SHADERS_SOURCE} to ${BUILD_DESTINATION}/CONFIG/shaders"
    )
else()
    add_custom_command(
            TARGET rectangle POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${BUILD_DESTINATION}/shaders"
            COMMAND "${CMAKE_COMMAND}" -E copy_directory "${SHADERS_SOURCE}" "${RUNTIME_DESTINATION}/shaders"
            DEPENDS "${SHADERS_SOURCE}"
            COMMENT "copied shaders directory from ${SHADERS_SOURCE} to ${BUILD_DESTINATION}/shaders"
            COMMENT "copied shaders directory from ${SHADERS_SOURCE} to ${RUNTIME_DESTINATION}/shaders"
    )
endif()
