/*
 *  Created by michal-swiatek on 16.05.2020, based on Joey de Vries tutorials.
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    std::cout << "Setup successful\n";

    //
    //  Setup scene
    //
    glm::vec3 lightColor1(2.5f, 1.5f, 0.7f);
    //glm::vec3 lightColor2(1.0f);
    glm::vec3 lightPos(100.0f, 1000.0f, 100.0f);

    Box box(glm::vec3(0.0f), glm::vec4(0.37f, 0.61f, 0.61f, 1.0f));
    //Box box(glm::vec3(0.0f), glm::vec4(0.5f, 0.0f, 0.61f, 1.0f));
    int boxesNumber = 10;
    double maxBoxHeight = 8.0;
    double minBoxHeight = 3.0;
    double boxWidth = 2.0;
    double angle = 0.0;
    const double ANGLE_STEP = 1.0;
    const double PERIOD = 0.5f;

    camera.setTransform(Transform(glm::vec3(-50.0f, 35.0f, 50.f), glm::vec3(-50.0f, -40.0f, 0.0f)));

    Shader boxShader("shaders/phong_view.vs.glsl", "shaders/phong_view.fs.glsl");

    boxShader.use();
    boxShader.setVector3f("ambientColor", glm::vec3(0.2f));
    boxShader.setVector3f("lightColor", lightColor1);

    //  Setup rendering settings
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSwapInterval(0);

    while (!glfwWindowShouldClose(window))
    {
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        std::string fps = std::to_string(int(1.0f / deltaTime));
        glfwSetWindowTitle(window, ("Box gif, fps: " + fps).c_str());

        glfwPollEvents();
        processInput(window);

        //  Render
        glClearColor(0.1, 0.1, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(camera.getZoom(), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, 0.1f, 100.0f);

        boxShader.use();

        boxShader.setInt("shininess", 32);
        boxShader.setVector3f("lightPos", glm::vec3(view * glm::vec4(lightPos, 1.0f)));

        angle += ANGLE_STEP * deltaTime;
        box.updateMatrices(projection);

        for (int i = boxesNumber; i >= -boxesNumber; --i)
        {
            for (int j = boxesNumber; j >= -boxesNumber; --j)
            {
                double scale = maxBoxHeight * glm::abs(glm::sin(angle + PERIOD * glm::sqrt(i*i + j*j))) + minBoxHeight;

                glm::mat4 model(1.0f);
                model = glm::translate(model, glm::vec3(i * boxWidth, 0.0f, j * boxWidth));
                model = glm::scale(model, glm::vec3(boxWidth, scale, boxWidth));
                box.setModelMatrix(model);

                boxShader.setVector3f("lightColor", lightColor1);
                glViewport(0, 0, WIDTH, HEIGHT);
                box.draw(boxShader, view);

//                boxShader.setVector3f("lightColor", lightColor2);
//                glViewport(WIDTH / 2, 0, WIDTH / 2, HEIGHT);
//                box.draw(boxShader, view);
            }
        }

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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xpos, double ypos)
{
    camera.zoom(ypos);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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


