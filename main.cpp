#include <iostream>

#include "LearningOpenGLConfig.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(int argc, char** argv) {
    if (argc < 2)
        // Report version
        std::cout << "Version " << learning_opengl_VERSION_MAJOR << '.' << learning_opengl_VERSION_MINOR << std::endl;

    return 0;
}
