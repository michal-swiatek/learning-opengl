/*
    Created by michal-swiatek on 19.05.2020, based on Joey de Vries tutorials.
    Github: https://github.com/michal-swiatek/learning-opengl
    LearnOpenGL tutorial: https://learnopengl.com/Introduction
*/

#ifndef MATERIAL_H
#define MATERIAL_H

#include <cstdint>

#include <glm/glm.hpp>

#include "Shader.h"

struct Material
{
    //  There are always textures, if color is specified then a 1x1 texture is created
    uint32_t ambient = 0;
    uint32_t diffuse = 0;
    uint32_t specular = 0;

    uint32_t shininess = 32;
};

class PhongMaterial
{
public:
    using Color = glm::vec4;

public:
    explicit PhongMaterial(Color diffuse = Color(1.0f), Color specular = Color(0.5f, 0.5f, 0.5f, 1.0f), uint32_t shininess = 32);
    explicit PhongMaterial(const char* diffuseMap, const char* specularMap, uint32_t shininess = 32);

    //  Setup shader
    void applyMaterial(const Shader& shader);

    //
    //  Modify material
    //

    //  Set by color
    void setAmbient(const Color& color = Color(1.0f));
    void setDiffuse(const Color& color = Color(1.0f));
    void setSpecular(const Color& color = Color(0.5f, 0.5f, 0.5f, 1.0f));

    //  Set by texture map
    void setAmbient(const char* ambientMap);
    void setDiffuse(const char* diffuseMap);
    void setSpecular(const char* specularMap);

    void setShininess(uint32_t value = 32);

    //  Access underlying material struct
    [[nodiscard]] const Material& getMaterial() const;

private:
    Material material;

    [[nodiscard]] uint32_t generateGLTexture() const;   //  Generates and prepares texture id
    [[nodiscard]] uint32_t loadTexture(const char* path) const;
    [[nodiscard]] uint32_t generateColorTexture(const Color& color) const;
};

#endif //MATERIAL_H
