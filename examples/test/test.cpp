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

#include "Cylinder.h"
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
    Cylinder cylinder(0.5, 0.5, 10.0, 30, 30);

    std::cout << "Vertices\n";
    for (auto& pos : cylinder.vertices)
        std::cout << pos << ' ';

    std::cout << "\nIndices\n";
    for (auto& index : cylinder.indices)
        std::cout << index << ' ';

    std::cout << "\nIndices count: " << cylinder.indices.size() << '\n';
    std::cout << "Indices size: " << cylinder.indices.size() * sizeof(float) << '\n';
    std::cout << "Vertices size: " << cylinder.vertices.size() * sizeof(unsigned int) << '\n';

    std::cout << '\n';

    uint VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, cylinder.vertices.size() * sizeof(float), cylinder.vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinder.indices.size() * sizeof(unsigned int), cylinder.indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    Shader cylinderShader("shaders/cylinder.vs.glsl", "shaders/cylinder.fs.glsl");

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window))
    {
        deltaTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        std::string fps = std::to_string(int(1.0f / deltaTime));
        glfwSetWindowTitle(window, ("Lighting, fps: " + fps).c_str());

        glfwPollEvents();
        processInput(window);

        glm::mat4 projection = glm::perspective(camera.getZoom(), float(WIDTH)/float(HEIGHT), 0.1f, 100.0f);

        //  Render
        glClearColor(0.1, 0.1, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cylinderShader.use();
        cylinderShader.setMatrix4f("vp", projection * camera.getViewMatrix());

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, cylinder.indices.size(), GL_UNSIGNED_INT, 0);

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
