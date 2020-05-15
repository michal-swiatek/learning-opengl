add_executable(phong phong.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(phong ${OPENGL_LIBS})

# Add shaders and resources to build and runtime directory
COPY_RESOURCES(phong ${RESOURCES_COPY_COMMAND})

# Set working directory for MS Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(phong PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
