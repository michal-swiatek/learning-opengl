/*
    Created by michal-swiatek on 08.05.2020.
    Github: https://github.com/michal-swiatek/learning-opengl
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using uint = unsigned int;

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

    //
    // Build shaders
    //

    //  Vertex shader
    std::ifstream vertexShaderFile("../shaders/triangle.vs.glsl");
    std::stringstream vertexShaderStream;

    vertexShaderStream << vertexShaderFile.rdbuf();
    std::string vertexShaderSource = vertexShaderStream.str();
    const char* vertexShaderCode = vertexShaderSource.c_str();

    std::cout << vertexShaderCode << '\n';

    uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);

    //  Fragment shader
    std::ifstream fragmentShaderFile("../shaders/triangle.fs.glsl");
    std::stringstream fragmentShaderStream;

    fragmentShaderStream << fragmentShaderFile.rdbuf();
    std::string fragmentShaderSource = fragmentShaderStream.str();
    const char* fragmentShaderCode = fragmentShaderSource.c_str();

    std::cout << fragmentShaderCode << '\n';

    uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);

    // Create shader
    uint triangleShader = glCreateProgram();

    glAttachShader(triangleShader, vertexShader);
    glAttachShader(triangleShader, fragmentShader);
    glLinkProgram(triangleShader);

    glDeleteProgram(vertexShader);
    glDeleteProgram(fragmentShader);

    glUseProgram(triangleShader);

    //
    // Set up triangle data
    //
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };

    uint VBO;
    glGenBuffers(1, &VBO);

    uint VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(triangleShader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
