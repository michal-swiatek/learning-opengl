/*
    Created by michal-swiatek on 14.05.2020.
    Github: https://github.com/michal-swiatek/learning-opengl
*/

#ifndef BOX_H
#define BOX_H

#include <cstdint>
#include <optional>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Transform.h"

class Box
{
    using OptionalMat4 = std::optional<glm::mat4>;

public:
    explicit Box(const Transform& transform, const glm::vec4& color = glm::vec4(1.0f));
    explicit Box(const glm::vec3& position = glm::vec3(0.0f), const glm::vec4& rotation = glm::vec4(0.0), const glm::vec3& scale = glm::vec3(1.0f), const glm::vec4& color = glm::vec4(1.0f));

    void updateMatrices(const OptionalMat4& projection = {});
    void draw(const Shader& shader, const glm::mat4& view, bool use_color = true) const;

    void translate(const glm::vec3& offset, bool updateModel = true);
    void rotate(float angle, bool updateModel = true);
    void scale(const glm::vec3& value, bool updateModel = true);

    void setPosition(const glm::vec3& position, bool updateModel = true);
    void setRotation(const glm::vec4& rotation, bool updateModel = true);
    void setScale(const glm::vec3& scale, bool updateModel = true);

    //  Transform
    [[nodiscard]] const Transform& getTransform() const;
    void setTransform(const Transform& newTransform, bool updateModel = true);

    //  Color
    [[nodiscard]] const glm::vec4& getColor() const;
    void setColor(const glm::vec4& newColor);

private:
    static uint32_t VBO;
    static uint32_t VAO;

    Transform transform;
    glm::mat4 modelMatrix;
    glm::mat4 projectionMatrix;

    glm::vec4 color;

    static void init();
};

#endif //BOX_H
