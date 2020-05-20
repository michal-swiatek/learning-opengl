/*
    Created by michal-swiatek on 19.05.2020, based on Joey de Vries tutorials.
    Github: https://github.com/michal-swiatek/learning-opengl
    LearnOpenGL tutorial: https://learnopengl.com/Introduction
*/

#include "OpenGLApp.h"

#include <memory>

#include "Box.h"

class MultipleLights : public OpenGLApp
{
private:
    using Color = PhongMaterial::Color;

private:
    std::unique_ptr<Shader> materialShader;
    std::unique_ptr<PhongMaterial> boxMaterial;

public:
    MultipleLights() : OpenGLApp("Multiple lights") { }

    void init() override
    {
        materialShader = std::make_unique<Shader>("shaders/phong_view.vd.glsl", "shaders/phong_view.fs.glsl");
        boxMaterial = std::make_unique<PhongMaterial>(Color(1.0f));


    }
};

int main() {
    MultipleLights app;
    app.initApp();

    app.run();

    return 0;
}
