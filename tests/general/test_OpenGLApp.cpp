/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#include "OpenGLApp.h"

class TestOpenGLApp : public OpenGLApp
{
public:
    TestOpenGLApp() : OpenGLApp("Test") { }
};

int main() {
    TestOpenGLApp app;
    app.initApp();

    app.run();

    return 0;
}
