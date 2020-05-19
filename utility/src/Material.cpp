/*
    Created by michal-swiatek on 19.05.2020, based on Joey de Vries tutorials.
    Github: https://github.com/michal-swiatek/learning-opengl
    LearnOpenGL tutorial: https://learnopengl.com/Introduction
*/

#include "Material.h"

#include <string>
#include <stdexcept>

#include <glad/glad.h>
#include <stb_image/stb_image.h>

bool has_suffix(const std::string &str, const std::string &suffix);     // Helper function

PhongMaterial::PhongMaterial(Color diffuse, Color specular, float shininess)
{
    setAmbient(diffuse);    //  By default same as diffuse (lighting control ambient)
    setDiffuse(diffuse);
    setSpecular(specular);
    setShininess(shininess);
}

PhongMaterial::PhongMaterial(const char *diffuseMap, const char *specularMap, float shininess)
{
    setAmbient(diffuseMap); //  By default same as diffuse (lighting control ambient)
    setDiffuse(diffuseMap);
    setSpecular(specularMap);
    setShininess(shininess);
}

//  Setup shader
void PhongMaterial::applyMaterial(const Shader &shader)
{
    //  Set uniforms
    shader.setInt("material.ambient", 0);
    shader.setInt("material.diffuse", 1);
    shader.setInt("material.specular", 2);
    shader.setFloat("material.shininess", material.shininess);

    //  Prepare textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, material.ambient);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, material.diffuse);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, material.specular);
}

//
//  Modify material
//

//  Set by color
void PhongMaterial::setAmbient(const Color& color)
{
    glDeleteTextures(1, &material.ambient);
    material.ambient = generateColorTexture(color);
}

void PhongMaterial::setDiffuse(const Color& color)
{
    glDeleteTextures(1, &material.diffuse);
    material.diffuse = generateColorTexture(color);
}

void PhongMaterial::setSpecular(const Color& color)
{
    glDeleteTextures(1, &material.specular);
    material.specular = generateColorTexture(color);
}

//  Set by texture map
void PhongMaterial::setAmbient(const char* ambientMap)
{
    glDeleteTextures(1, &material.ambient);
    material.ambient = loadTexture(ambientMap);
}

void PhongMaterial::setDiffuse(const char* diffuseMap)
{
    glDeleteTextures(1, &material.diffuse);
    material.diffuse = loadTexture(diffuseMap);
}

void PhongMaterial::setSpecular(const char* specularMap)
{
    glDeleteTextures(1, &material.specular);
    material.specular = loadTexture(specularMap);
}

void PhongMaterial::setShininess(float value)
{
    material.shininess = value;
}

//  Access underlying Material struct
const Material& PhongMaterial::getMaterial() const
{
    return material;
}

//
//  Private helper functions
//

uint32_t PhongMaterial::generateGLTexture() const
{
    uint32_t texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

uint32_t PhongMaterial::loadTexture(const char *path) const
{
    using uchar = unsigned char;

    //  Load texture data
    stbi_set_flip_vertically_on_load(true);

    int image_width, image_height, channels;
    uchar* image_data = stbi_load(path, &image_width, &image_height, &channels, 0);

    if (!image_data)
        throw std::runtime_error("Failed to load texture! Path: " + std::string(path) + "\n");

    uint32_t texture = generateGLTexture();

    //  Format texture according to type of file
    GLuint image_format;
    if (has_suffix(path, ".jpg"))
        image_format = GL_RGB;
    else if (has_suffix(path, ".png"))
        image_format = GL_RGBA;
    else {
        stbi_image_free(image_data);
        throw std::runtime_error("Unsupported image format! File: " + std::string(path) + "\n");
    }

    //  Send texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, image_format, image_width, image_height, 0, image_format, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image_data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

uint32_t PhongMaterial::generateColorTexture(const Color &color) const
{
    using uchar = unsigned char;

    //  Generate color texture (1x1)
    uchar image_data[4];
    image_data[0] = (255 * color.r);
    image_data[1] = (255 * color.g);
    image_data[2] = (255 * color.b);
    image_data[3] = (255 * color.a);

    uint32_t texture = generateGLTexture();

    //  Send texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

//  Helper function
bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
