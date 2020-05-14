/*
    Created by michal-swiatek on 11.05.2020, based on Joey de Vries tutorials.
    Github: https://github.com/michal-swiatek/learning-opengl
    LearnOpenGL tutorial: https://learnopengl.com/Introduction
*/

#ifndef SHADER_H
#define SHADER_H

#include <cstdint>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
    // Builds shader program
    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
    Shader(Shader&& other) noexcept;

    void use(); // Activate shader program
    void destroyProgram();

    [[nodiscard]] GLuint getProgramID() const;

    //
    //  Setting uniforms
    //

    //  Scalars
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    //  Matrices
    void setMatrix2f(const std::string& name, const glm::mat2& matrix) const;
    void setMatrix3f(const std::string& name, const glm::mat3& matrix) const;
    void setMatrix4f(const std::string& name, const glm::mat4& matrix) const;

private:
    GLuint programID;
    bool destroyed;

    std::string readShaderSource(const char* shaderPath) const;
    GLuint compileShader(GLuint type, const char* shaderCode) const;
    GLuint linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) const;
};

#endif //SHADER_H
