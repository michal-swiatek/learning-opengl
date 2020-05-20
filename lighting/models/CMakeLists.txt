add_executable(phong_view phong_view.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(phong_view ${OPENGL_LIBS})

add_executable(phong_model phong_model.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(phong_model ${OPENGL_LIBS})

add_executable(gourard gourard.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(gourard ${OPENGL_LIBS})

# Add shaders and resources to build and runtime directory
COPY_RESOURCES(phong_view ${RESOURCES_COPY_COMMAND})
COPY_RESOURCES(phong_model ${RESOURCES_COPY_COMMAND})
COPY_RESOURCES(gourard ${RESOURCES_COPY_COMMAND})

# Set working directory for MS Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(phong_view PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    set_target_properties(phong_model PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    set_target_properties(gourard PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
