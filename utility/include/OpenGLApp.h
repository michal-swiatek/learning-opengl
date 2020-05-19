/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#ifndef OPENGLAPP_H
#define OPENGLAPP_H

#include <cstdint>
#include <memory>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.h>

#include "Window.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"

class OpenGLApp
{
public:
    using uint = uint32_t;
    using uchar = uint8_t;

public:
    explicit OpenGLApp(std::string&& name, uint32_t appVersionMajor = 1, uint32_t appVersionMinor = 0);
    virtual ~OpenGLApp() = default;

    //  Start application
    void initApp(uint32_t width = 1280, uint32_t height = 720, bool fullscreen = false, bool showCursor = true);
    void run();

    static cam::Camera& getMainCamera();

protected:
    //  User Interface
    virtual void updateInput();
    virtual void updateLogic();
    virtual void draw();

    virtual void init();
    virtual void quit();

    //  TODO: implement ConfigFile
    //virtual void loadConfig(const char* path);
    //virtual void saveConfig(const char* path);

    std::unique_ptr<Window> mainWindow;
    cam::Camera& camera = mainCamera;

    double deltaTime;
    double lastTime;
    uint32_t framesCounter;
    float framesPerSecond;

    static cam::Camera mainCamera;

private:
    uint32_t appVersionMajor;
    uint32_t appVersionMinor;

    std::string name;
    std::string windowTitle;
};

#endif //OPENGLAPP_H
