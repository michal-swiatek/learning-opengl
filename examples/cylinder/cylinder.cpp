/*
 *  Created by michal-swiatek on 17.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 *
 *  Cylinder generation by Rafał Uzarowicz
 */

#include "OpenGLApp.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Cylinder.h"
#include "Shader.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

class CylinderVisualization : public OpenGLApp
{
private:
    std::unique_ptr<Shader> cylinderShader;
    std::unique_ptr<Cylinder> cylinder;

    uint VBO, VAO, EBO;

public:
    CylinderVisualization() : OpenGLApp("Cylinder visualtization") { }

    void init() override
    {
        cylinder = std::make_unique<Cylinder>(5.0, 5.0, 10.0, 30, 2);

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, cylinder->vertices.size() * sizeof(float), cylinder->vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cylinder->indices.size() * sizeof(unsigned int), cylinder->indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        cylinderShader = std::make_unique<Shader>("shaders/phong_view.vs.glsl", "shaders/phong_view.fs.glsl");

        cylinderShader->use();
        cylinderShader->setVector3f("lightColor", glm::vec3(1.0f));
        cylinderShader->setVector3f("ambientColor", glm::vec3(0.5f));
        cylinderShader->setVector3f("diffuseColor", glm::vec3(1.0f));
        cylinderShader->setVector3f("specularColor", glm::vec3(0.6f));
    }

    void draw() override
    {
        glm::mat4 projection = glm::perspective(camera.getZoom(), float(WIDTH)/float(HEIGHT), 0.1f, 100.0f);

        glm::mat4 view = camera.getViewMatrix();

        cylinderShader->use();
        cylinderShader->setVector3f("lightPos", glm::vec3(view * glm::vec4(glm::vec3(10.0f), 1.0f)));

        cylinderShader->setMatrix4f("mv", view);
        cylinderShader->setMatrix4f("mvp", projection * view);
        cylinderShader->setMatrix3f("mvInvTrans", glm::mat3(glm::transpose(glm::inverse(view))));

        glBindVertexArray(VAO);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glViewport(0, 0, WIDTH / 2, HEIGHT);
        glDrawElements(GL_TRIANGLES, cylinder->indices.size(), GL_UNSIGNED_INT, 0);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glViewport(WIDTH / 2, 0, WIDTH / 2, HEIGHT);
        glDrawElements(GL_TRIANGLES, cylinder->indices.size(), GL_UNSIGNED_INT, 0);
    }
};

int main() {
    CylinderVisualization app;
    app.initApp(WIDTH, HEIGHT, false, false);

    app.run();

    return 0;
}


