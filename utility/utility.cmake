# Include utility files
set(UTILITY_PATH "${CMAKE_SOURCE_DIR}/utility")

include_directories("${UTILITY_PATH}/include")

set(UTILITY_INCLUDE_FILES
        "${UTILITY_PATH}/include/Shader.h"
        "${UTILITY_PATH}/include/Camera.h"
        "${UTILITY_PATH}/include/Transform.h"
        "${UTILITY_PATH}/include/Box.h"
        "${UTILITY_PATH}/include/Cylinder.h"
        "${UTILITY_PATH}/include/Window.h"
        "${UTILITY_PATH}/include/OpenGLApp.h"
        )

set(UTILITY_SRC_FILES
        "${UTILITY_PATH}/src/Shader.cpp"
        "${UTILITY_PATH}/src/Camera.cpp"
        "${UTILITY_PATH}/src/Box.cpp"
        "${UTILITY_PATH}/src/Window.cpp"
        "${UTILITY_PATH}/src/OpenGLApp.cpp"
        )