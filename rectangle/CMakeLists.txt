add_executable(rectangle rectangle.cpp)
target_link_libraries(rectangle ${LIBS})

# Adding shaders to build directory
add_custom_command(
        TARGET rectangle POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink ${SHADERS_SOURCE} ${SHADERS_DESTINATION}
        DEPENDS ${SHADERS_DESTINATION}
        COMMENT "created symbolic link for shaders folder from ${SHADERS_SOURCE} => ${SHADERS_DESTINATION}"
)