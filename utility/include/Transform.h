/*
    Created by michal-swiatek on 11.05.2020.
    Github: https://github.com/michal-swiatek/learning-opengl
*/

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    explicit Transform(const glm::vec3& position = glm::vec3(0.0f),
                       const glm::vec3& rotation = glm::vec3(0.0f),
                       const glm::vec3& scale = glm::vec3(1.0f)) :
                            position(position), rotation(rotation), scale(scale) { }
};

#endif //TRANSFORM_H
