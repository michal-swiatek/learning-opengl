add_executable(box_gif box_gif/box_gif.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(box_gif ${OPENGL_LIBS})

add_executable(cylinder cylinder/cylinder.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES})
target_link_libraries(cylinder ${OPENGL_LIBS})

add_executable(metaballs metaballs/metaballs.cpp ${CURRENT_INCLUDE_FILES} ${CURRENT_SRC_FILES} metaballs/Isosurface.h metaballs/Isosurface.cpp)
target_link_libraries(metaballs ${OPENGL_LIBS})

# Adding shaders to build and executable directory
COPY_RESOURCES(box_gif ${RESOURCES_COPY_COMMAND})
COPY_RESOURCES(cylinder ${RESOURCES_COPY_COMMAND})
COPY_RESOURCES(metaballs ${RESOURCES_COPY_COMMAND})

# Set working directory for MS Visual Studio
if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_target_properties(box_gif PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    set_target_properties(cylinder PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    set_target_properties(metaballs PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endif()
