/*
    Created by michal-swiatek on 11.05.2020, based on Joey de Vries tutorials.
    Github: https://github.com/michal-swiatek/learning-opengl
    LearnOpenGL tutorial: https://learnopengl.com/Introduction
*/

#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) : destroyed(false)
{
    //  Read shaders code
    std::string vertexShaderSource = readShaderSource(vertexPath);
    std::string fragmentShaderSource = readShaderSource(fragmentPath);
    std::string geometryShaderSource = geometryPath ? readShaderSource(geometryPath) : "";

    const char* vertexShaderCode = vertexShaderSource.c_str();
    const char* fragmentShaderCode = fragmentShaderSource.c_str();
    const char* geometryShaderCode = geometryShaderSource.c_str();

    //  Build shaders
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);
    GLuint geometryShader = geometryPath ? compileShader(GL_GEOMETRY_SHADER, geometryShaderCode) : 0;

    //  Link program
    programID = linkProgram(vertexShader, fragmentShader, geometryShader);

    //  Delete shaders after they are linked into program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometryShader)
        glDeleteShader(geometryShader);
}

Shader::Shader(Shader &&other) noexcept
{
    programID = other.programID;
    other.programID = 0;
    other.destroyed = true;
}

/*
 *  Public
 */

void Shader::use()
{
    if (destroyed)
        throw std::exception(); // TODO: implement exception

    glUseProgram(programID);
}

void Shader::destroyProgram()
{
    glDeleteProgram(programID);

    programID = 0;
    destroyed = true;
}

GLuint Shader::getProgramID() const
{
    if (destroyed)
        throw std::exception(); // TODO: implement exception

    return programID;
}

/*
 *  Uniforms
 */

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

/*
 *  Private
 */

std::string Shader::readShaderSource(const char* shaderPath) const
{
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    // Ensure ifstream object can throw exceptions:
    shaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    try {
        shaderFile.open(shaderPath);
        shaderStream << shaderFile.rdbuf();

        shaderFile.close();
    }
    catch (std::ifstream::failure& e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\tShader path: " << shaderPath << std::endl;
    }

    return shaderStream.str();
}

GLuint Shader::compileShader(GLuint type, const char *shaderCode) const
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    //  Check for compile errors
    int success;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        const char* shaderType = type == GL_VERTEX_SHADER ? "VERTEX" : (type == GL_FRAGMENT_SHADER ? "FRAGMENT" : "GEOMETRY");

        std::cerr << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) const
{
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    if (geometryShader)
        glAttachShader(program, geometryShader);

    glLinkProgram(program);

    //  Check for linking errors
    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    return program;
}
