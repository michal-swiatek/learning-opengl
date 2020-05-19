add_executable(multiple_lights multiple_lights.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(multiple_lights ${OPENGL_LIBS})

# Add shaders and resources to build and runtime directory
COPY_RESOURCES(multiple_lights ${RESOURCES_COPY_COMMAND})

# Set working directory for MS Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(multiple_lights PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
