/*
    Created by michal-swiatek on 14.05.2020.
    Github: https://github.com/michal-swiatek/learning-opengl
*/

#include "Box.h"

#include <stdexcept>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vec_swizzle.hpp>

uint32_t Box::VBO = 0;
uint32_t Box::VAO = 0;

float vertices[] = {
        //  Position          //  Normals           //  TexCoords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
        0.5f,  -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
        0.5f,   0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        0.5f,   0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    0.0f, 0.0f,
        0.5f,  -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    1.0f, 0.0f,
        0.5f,   0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    1.0f, 1.0f,
        0.5f,   0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,    0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
        0.5f,  -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
        0.5f,  -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
        0.5f,  -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
        0.5f,   0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
        0.5f,   0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
        0.5f,   0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 1.0f
    };

Box::Box(const Transform& transform, const glm::vec4& color) : transform(transform), color(color)
{
    init();
}

Box::Box(const glm::vec3 &position, const glm::vec4 &rotation, const glm::vec3 &scale, const glm::vec4 &color) : color(color)
{
    transform = Transform(position, rotation, scale);

    init();
}

void Box::updateMatrices(const OptionalMat4 &projection)
{
    if (projection)
        projectionMatrix = *projection;

    //  Calculate model matrix
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    if (transform.rotation.w != 0.0)
        modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotation.w), glm::xyz(transform.rotation));
    modelMatrix = glm::scale(modelMatrix, transform.scale);
}

void Box::draw(const Shader& shader, const glm::mat4& view, bool use_color) const
{
    glBindVertexArray(VAO);

    //  Set uniforms
    shader.setBool("use_color", use_color);
    shader.setVector4f("color", color);

    shader.setMatrix4f("mv", view * modelMatrix);
    shader.setMatrix4f("mvp", projectionMatrix * view * modelMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}

void Box::translate(const glm::vec3& offset, bool updateModel)
{
    transform.position += offset;
    if (updateModel)
        updateMatrices();
}

void Box::rotate(float angle, bool updateModel)
{
    transform.rotation.w += angle;
    if (updateModel)
        updateMatrices();
}

void Box::scale(const glm::vec3 &value, bool updateModel)
{
    transform.scale *= value;
    if (updateModel)
        updateMatrices();
}

void Box::setPosition(const glm::vec3 &position, bool updateModel)
{
    transform.position = position;
    if (updateModel)
        updateMatrices();
}

void Box::setRotation(const glm::vec4 &rotation, bool updateModel)
{
    transform.rotation = rotation;
    if (updateModel)
        updateMatrices();
}

void Box::setScale(const glm::vec3 &scale, bool updateModel)
{
    transform.scale = scale;
    if (updateModel)
        updateMatrices();
}

//  Transform
const Transform& Box::getTransform() const
{
    return transform;
}

void Box::setTransform(const Transform& newTransform, bool updateModel)
{
    transform = newTransform;
    if (updateModel)
        updateMatrices();
}

//  Color
const glm::vec4& Box::getColor() const
{
    return color;
}

void Box::setColor(const glm::vec4& newColor)
{
    color = newColor;
}

void Box::init()
{
    if (VBO == 0)
    {
        glGenBuffers(1, &VBO);

        if (VBO == 0)
            throw std::runtime_error("Unable to generate Box VBO!\n");

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if (VAO == 0)
    {
        glGenVertexArrays(1, &VAO);

        if (VAO == 0)
            throw std::runtime_error("Unable to generate Box VAO!\n");

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
