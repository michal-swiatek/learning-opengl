add_executable(test_OpenGLApp test_OpenGLApp.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(test_OpenGLApp ${OPENGL_LIBS})