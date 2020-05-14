/*
    Created by michal-swiatek on 14.05.2020.
    Github: https://github.com/michal-swiatek/learning-opengl
*/

#ifndef BOX_H
#define BOX_H

#include <cstdint>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Transform.h"

class Box
{
public:
    explicit Box(const Transform& transform, const glm::vec4& color = glm::vec4(1.0f));
    explicit Box(const glm::vec3& position, const glm::vec4& rotation = glm::vec4(0.0), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));

    void draw(const Shader& shader, bool use_color = true) const;

    void translate(const glm::vec3& offset);
    void rotate(float angle);
    void scale(const glm::vec3& value);

    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec4& rotation);
    void setScale(const glm::vec3& scale);

    //  Transform
    [[nodiscard]] const Transform& getTransform() const;
    void setTransform(const Transform& newTransform);

    //  Color
    [[nodiscard]] const glm::vec4& getColor() const;
    void setColor(const glm::vec4& newColor);

private:
    static uint32_t VBO;
    static uint32_t VAO;

    Transform transform;
    glm::vec4 color;

    static void init();
};

#endif //BOX_H
