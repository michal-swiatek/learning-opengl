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

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, transform.scale);
}

Box::Box(const glm::vec3 &position, const glm::vec4 &color) : transform(Transform(position)), color(color)
{
    init();

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, transform.scale);
}

void Box::updateMatrices(const OptionalMat4 &projection)
{
    if (projection)
        projectionMatrix = *projection;
}

void Box::draw(const Shader& shader, const glm::mat4& view, bool use_color) const
{
    glBindVertexArray(VAO);

    //  Set uniforms
    shader.setBool("use_color", use_color);
    shader.setVector3f("diffuseColor", glm::vec3(color));
    shader.setVector3f("specularColor", 0.5f * glm::vec3(color));

    glm::mat4 mv = view * modelMatrix;
    shader.setMatrix4f("mv", mv);
    shader.setMatrix4f("mvp", projectionMatrix * mv);
    shader.setMatrix3f("mvInvTrans", glm::mat3(glm::transpose(glm::inverse(view * modelMatrix))));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}

void Box::translate(const glm::vec3& offset)
{
    transform.position += offset;

    modelMatrix = glm::translate(modelMatrix, offset);
}

void Box::rotate(float angle, const std::optional<glm::vec3>& axis)
{
    if (axis)
        transform.rotation = *axis;

    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), transform.rotation);
    modelMatrix = glm::translate(modelMatrix, -transform.position);
}

void Box::scale(const glm::vec3 &value)
{
    transform.scale *= value;

    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, value);
    modelMatrix = glm::translate(modelMatrix, -transform.position);
}

void Box::setPosition(const glm::vec3 &position)
{
    modelMatrix = glm::translate(modelMatrix, -transform.position);
    transform.position = position;
    modelMatrix = glm::translate(modelMatrix, transform.position);
}

void Box::setRotation(float angle, const glm::vec3 &axis)
{
    transform.rotation = axis;

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), transform.rotation);
    modelMatrix = glm::scale(modelMatrix, transform.scale);
}

void Box::setScale(const glm::vec3 &scale)
{
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::translate(modelMatrix, -transform.position);

    transform.scale = scale;

    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::translate(modelMatrix, -transform.position);
}

//  Transform
const Transform& Box::getTransform() const
{
    return transform;
}

void Box::setTransform(const Transform& newTransform)
{
    transform = newTransform;

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, transform.position);
    modelMatrix = glm::scale(modelMatrix, transform.scale);
}

const glm::mat4& Box::getModelMatrix() const
{
    return modelMatrix;
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
