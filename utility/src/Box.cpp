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
        // positions          // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,   0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,   1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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

void Box::draw(const Shader& shader, bool use_color) const
{
    glBindVertexArray(VAO);

    //  Calculate model matrix
    glm::mat4 model(1.0f);
    model = glm::translate(model, transform.position);
    if (transform.rotation.w != 0.0)
        model = glm::rotate(model, glm::radians(transform.rotation.w), glm::xyz(transform.rotation));
    model = glm::scale(model, transform.scale);

    //  Set uniforms
    shader.setBool("use_color", use_color);
    shader.setVector4f("color", color);
    shader.setMatrix4f("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(0);
}

void Box::translate(const glm::vec3& offset)
{
    transform.position += offset;
}

void Box::rotate(float angle)
{
    transform.rotation.w += angle;
}

void Box::scale(const glm::vec3 &value)
{
    transform.scale *= value;
}

void Box::setPosition(const glm::vec3 &position)
{
    transform.position = position;
}

void Box::setRotation(const glm::vec4 &rotation)
{
    transform.rotation = rotation;
}

void Box::setScale(const glm::vec3 &scale)
{
    transform.scale = scale;
}

//  Transform
const Transform& Box::getTransform() const
{
    return transform;
}

void Box::setTransform(const Transform& newTransform)
{
    transform = newTransform;
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

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
