add_executable(box_gif box_gif.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(box_gif ${OPENGL_LIBS})

# Adding shaders to build and executable directory
COPY_RESOURCES(box_gif ${RESOURCES_COPY_COMMAND})

# Set working directory for MS Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(box_gif PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()