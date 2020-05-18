/*
 *  Created by swiat on 18.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#include "OpenGLApp.h"

#include <memory>
#include <cstdlib>
#include <ctime>

#include "Isosurface.h"

class Metaballs : public OpenGLApp
{
private:
    Isosurface isosurface;
    static const int gridSize = 50;
    static constexpr float gridResolution = 1.0f;

    std::unique_ptr<Shader> gridShader;

    float isovalue = 1.0f;
    float coefficient = 5.0f;
    int metaballsAmount = 10;

    std::vector<glm::vec3> r;
    std::vector<glm::vec3> v;

public:
    Metaballs() : OpenGLApp("Metaballs"), isosurface(Isosurface(gridSize, gridResolution))
    {
        srand(time(nullptr));

        for (int i = 0; i < metaballsAmount; ++i)
        {
            r.emplace_back(rand() % 50, rand() % 50, rand() % 50);
            v.emplace_back(rand() % 10 - 5, rand() % 10 - 5, rand() % 10 - 5);
        }
    }

    void init() override
    {
        gridShader = std::make_unique<Shader>("shaders/flatColor.vs.glsl", "shaders/flatColor.fs.glsl");
    }

    void updateInput() override
    {
        OpenGLApp::updateInput();

        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
            isovalue += 5.0 * deltaTime;
        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
            isovalue -= 5.0 * deltaTime;

        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_C) == GLFW_PRESS)
            coefficient += 5.0 * deltaTime;
        if (glfwGetKey(mainWindow->getWindow(), GLFW_KEY_Z) == GLFW_PRESS)
            coefficient -= 5.0 * deltaTime;
    }

    void updateLogic() override
    {
        for (int i = 0; i < metaballsAmount; ++i)
        {
            r[i] += v[i] * float(deltaTime);

            if (r[i].x - coefficient < 0)     v[i].x *= -1, r[i].x = coefficient;
            if (r[i].y - coefficient < 0)     v[i].y *= -1, r[i].y = coefficient;
            if (r[i].z - coefficient < 0)     v[i].z *= -1, r[i].z = coefficient;

            if (r[i].x + coefficient > 50)    v[i].x *= -1, r[i].x = 50 - coefficient;
            if (r[i].y + coefficient > 50)    v[i].y *= -1, r[i].y = 50 - coefficient;
            if (r[i].z + coefficient > 50)    v[i].z *= -1, r[i].z = 50 - coefficient;
        }

//        isosurface.updateIsosurface(isovalue, [](float x, float y, float z){
//            return glm::distance(glm::vec3(x, y, z), glm::vec3(0.0f));
//        });

//        float coefficient = this->coefficient;
//        auto fun = [&coefficient](float x, float y, float z){
//            return coefficient / glm::distance(glm::vec3(x, y, z), glm::vec3(0.0f));
//        };

//        float coefficient = this->coefficient;
//        auto fun = [&coefficient](float x, float y, float z){
//            float r1 = glm::distance(glm::vec3(x, y, z), glm::vec3(0.0f));
//            float r2 = glm::distance(glm::vec3(x, y, z), glm::vec3(50.0f));
//
//            return 2 * coefficient - r1 - r2;
//        };

        float coefficient = this->coefficient;
        float isovalue = this->isovalue;
        const std::vector<glm::vec3>& metaballs = this->r;

        auto fun = [&coefficient, &isovalue, &metaballs](float x, float y, float z){
            float total = 0.0;

            for (const auto& metaball : metaballs)
            {
                float RX = (x-metaball.x) * (x-metaball.x);
                float RY = (y-metaball.y) * (y-metaball.y);
                float RZ = (z-metaball.z) * (z-metaball.z);

                total += coefficient / (RX + RY + RZ);
            }

            return total;
        };

        isosurface.updateIsosurface(isovalue, fun);

        isosurface.generateIsosurfaceMesh();
    }

    void draw() override
    {
        gridShader->use();
        gridShader->setVector3f("diffuseColor", glm::vec3(1.0f));

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        isosurface.drawGrid(gridShader.get(), camera);

        gridShader->setVector3f("diffuseColor", glm::vec3(1.0f, 0.0f, 0.0f));
        isosurface.drawIsosurface(gridShader.get(), camera);
    }
};

int main() {
    Metaballs app;
    app.initApp(1280, 720, false, false);

    app.run();

    return 0;
}
