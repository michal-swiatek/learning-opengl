add_executable(transformations transformations.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(transformations ${OPENGL_LIBS})

add_executable(coordinate_systems coordinate_systems.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(coordinate_systems ${OPENGL_LIBS})

# Adding shaders to build and executable directory
COPY_RESOURCES(transformations ${RESOURCES_COPY_COMMAND})
COPY_RESOURCES(coordinate_systems ${RESOURCES_COPY_COMMAND})

# Set working directory for MS Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(transformations PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    set_target_properties(coordinate_systems PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()