add_executable(test_glfw3 test_glfw3.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(test_glfw3 ${OPENGL_LIBS})