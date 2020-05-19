/*
    Created by michal-swiatek on 19.05.2020, based on Joey de Vries tutorials.
    Github: https://github.com/michal-swiatek/learning-opengl
    LearnOpenGL tutorial: https://learnopengl.com/Introduction
*/

#include "OpenGLApp.h"

class MultipleLights : public OpenGLApp
{
public:
    MultipleLights() : OpenGLApp("Multiple lights") { }
};

int main() {
    MultipleLights app;
    app.initApp();

    app.run();

    return 0;
}
