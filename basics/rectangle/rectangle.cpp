/*
    Created by michal-swiatek on 08.05.2020, based on Joey de Vries tutorial.
    Github: https://github.com/michal-swiatek/learning-opengl
    LearnOpenGL tutorial: https://learnopengl.com/Introduction
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

using uint = unsigned int;

int width = 800;
int height = 600;

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main(int argc, char** argv) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    std::cout << "Setup successful\n";

    //
    // Build shaders
    //

    Shader rectangleShader("shaders/rectangle.vs.glsl", "shaders/rectangle.fs.glsl");
    rectangleShader.use();

    //
    // Set up rectangle data
    //
    float vertices[] = {
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,    // top right
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,    // bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,   // bottom left
            -0.5f,  0.5f, 0.0f, 0.5f, 0.5f, 1.0f    // top left
    };

    uint indices[] = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    uint VBO;
    glGenBuffers(1, &VBO);

    uint EBO;
    glGenBuffers(1, &EBO);

    uint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        // Set uniforms
        double time = glfwGetTime();
        float color_scale = (float)sin(time) / 4.0f + 0.75f;

        rectangleShader.use();
        rectangleShader.setFloat("color_scale", color_scale);

        // glDrawArrays(GL_TRIANGLES, 0, 3);

        // Draw filled quad in top part of screen
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glViewport(0, height / 2, width, height / 2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Draw wireframe quad in bottom part of screen
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glViewport(0, 0, width, height / 2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
