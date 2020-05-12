add_executable(test_glfw3 test_glfw3.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(test_glfw3 ${OPENGL_LIBS})

add_executable(test_glm test_glm.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(test_glm ${OPENGL_LIBS})

add_executable(test_stb_image test_stb_image.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(test_stb_image ${OPENGL_LIBS})