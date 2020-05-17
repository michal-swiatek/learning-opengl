/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#include "OpenGLApp.h"

#include <stdexcept>

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

OpenGLApp::OpenGLApp(std::string&& name, uint32_t appVersionMajor, uint32_t appVersionMinor)
{
    this->appVersionMajor = appVersionMajor;
    this->appVersionMinor = appVersionMinor;
    this->name = name;
    this->windowTitle = name + ", version: " + std::to_string(appVersionMajor) + '.' + std::to_string(appVersionMinor);

    lastTime = deltaTime = 0.0;
    framesCounter = 0;
    framesPerSecond = 0.0;
}

void OpenGLApp::initApp(uint32_t width, uint32_t height, bool fullscreen, bool showCursor)
{
    //  Initialize OpenGL and GLFW
    if (glfwInit() == GLFW_FALSE)
        throw std::runtime_error("Failed to initialize GLFW!\n");

    WindowSettings settings(width, height, windowTitle.c_str(), fullscreen, showCursor);
    mainWindow = std::make_unique<Window>(settings);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD!\n");

    mainCamera = cam::Camera();

    init();
}

void OpenGLApp::run()
{
    lastTime = deltaTime = 0.0;
    framesCounter = 0;

    while (!mainWindow->isClosed())
    {
        //  Timing and fps info
        ++framesCounter;
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        framesPerSecond = static_cast<float>(1 / deltaTime);

        //  Update input
        glfwPollEvents();

        std::string windowInfo = windowTitle + ", fps: " + std::to_string(int(framesPerSecond));
        glfwSetWindowTitle(mainWindow->getWindow(), windowInfo.c_str());

        updateInput();
        updateLogic();
        draw();
    }

    quit();
}

void OpenGLApp::updateInput()
{
    if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        mainWindow->close();
}

void OpenGLApp::updateLogic()
{

}

void OpenGLApp::draw()
{
    glClearColor(0.1, 0.1, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(mainWindow->getWindow());
}

void OpenGLApp::init()
{

}

void OpenGLApp::quit()
{

}
