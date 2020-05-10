add_executable(rectangle rectangle.cpp)
target_link_libraries(rectangle ${OPENGL_LIBS})

# Adding shaders to build directory
add_custom_command(
        TARGET rectangle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${SHADERS_SOURCE}" "${SHADERS_DESTINATION}"
        DEPENDS "${SHADERS_DESTINATION}" "${SHADERS_SOURCE}"
        COMMENT "created symbolic link for shaders folder from ${SHADERS_SOURCE} => ${SHADERS_DESTINATION}"
)