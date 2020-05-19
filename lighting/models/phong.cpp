/*
 *  Created by michal-swiatek on 15.05.2020, based on Joey de Vries tutorials.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 *  LearnOpenGL tutorial: https://learnopengl.com/Introduction
 */

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Material.h"

#include "Transform.h"
#include "Box.h"

using uint = unsigned int;
using uchar = unsigned char;

const int WIDTH = 1600;
const int HEIGHT = 900;

cam::Camera camera;

float deltaTime = 0.0;
float lastTime = 0.0;

void processInput(GLFWwindow* window);

void framebuffer_size_callback1(GLFWwindow* window, int width, int height);
void scroll_callback1(GLFWwindow* window, double xpos, double ypos);
void mouse_callback1(GLFWwindow* window, double xpos, double ypos);

int main(int argc, char**) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lighting", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback1);
    glfwSetScrollCallback(window, scroll_callback1);
    glfwSetCursorPosCallback(window, mouse_callback1);

    std::cout << "Setup successful\n";

    //
    //  Setup scene
    //
    PhongMaterial boxMaterial(glm::vec4(1.0f, 0.5f, 0.3f, 1.0f));

    Box light(Transform(glm::vec3(2.0f, 3.0f, 3.0f), glm::vec3(1.0f), glm::vec3(0.3f)), glm::vec4(1.0f));
    Box box(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec4(1.0f, 0.5f, 0.3f, 1.0f));

    //
    //  Setup shaders
    //
    Shader lightShader("shaders/light.vs.glsl", "shaders/light.fs.glsl");
    Shader boxShader("shaders/phong_view.vs.glsl", "shaders/phong_view.fs.glsl");

    boxShader.use();
    boxShader.setVector3f("light.ambient", glm::vec3(0.1f));
    boxShader.setVector3f("light.diffuse", glm::vec3(light.getColor()));
    boxShader.setVector3f("light.specular", glm::vec3(1.0f));

    //  Setup rendering settings
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSwapInterval(0);

    camera.getSettings().movementSpeed /= 2;

    while (!glfwWindowShouldClose(window))
    {
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        std::string fps = std::to_string(int(1.0f / deltaTime));
        glfwSetWindowTitle(window, ("Lighting, fps: " + fps).c_str());

        glfwPollEvents();
        processInput(window);

        //  Render
        glClearColor(0.1, 0.1, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(camera.getZoom(), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

        lightShader.use();

        light.updateMatrices(projection);
        light.draw(lightShader, view);

        boxShader.use();

        boxMaterial.applyMaterial(boxShader);

        boxShader.setVector4f("light.position", view * glm::vec4(light.getTransform().position, 1.0f));
        boxShader.setFloat("material.shininess", 1.0f);

        box.updateMatrices(projection);
        box.draw(boxShader, view);

        glfwSwapBuffers(window);
    }

    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //  Camera control

    //  Speed
    cam::Speed cameraSpeed = cam::Speed::NORMAL;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraSpeed = cam::Speed::FAST;
    else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
        cameraSpeed = cam::Speed::SLOW;

    //  Movement direction
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.move(cam::Direction::FORWARD, cameraSpeed, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.move(cam::Direction::BACKWARD, cameraSpeed, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.move(cam::Direction::RIGHT, cameraSpeed, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.move(cam::Direction::LEFT, cameraSpeed, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.move(cam::Direction::UP, cameraSpeed, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.move(cam::Direction::DOWN, cameraSpeed, deltaTime);
}

void framebuffer_size_callback1(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void scroll_callback1(GLFWwindow* window, double xpos, double ypos)
{
    camera.zoom(ypos);
}

void mouse_callback1(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;

    static double lastX = WIDTH / 2;
    static double lastY = HEIGHT / 2;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;

        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;   //  Reversed because y-coordinates range from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.rotate(xoffset, yoffset, 0.0);
}
