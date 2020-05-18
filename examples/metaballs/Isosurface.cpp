/*
 *  Created by swiat on 18.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#include "Isosurface.h"
#include "LookupTable.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

Isosurface::Isosurface(int32_t gridSize, float gridResolution) : gridSize(gridSize), gridResolution(gridResolution)
{
    gridVBO = gridVAO = isosurfaceVBO = isosurfaceVAO = 0;

    gridBounds = Box();
    gridBounds.scale(glm::vec3(gridSize));

    //  Allocate buffers
    grid.reserve(gridSize * gridSize * gridSize * 3);
    values.resize(gridSize * gridSize * gridSize);

    //  Generate grid
    for (int32_t z = 0; z < gridSize; ++z)
        for (int32_t y = 0; y < gridSize; ++y)
            for (int32_t x = 0; x < gridSize; ++x)
            {
                grid.push_back(x * gridResolution);
                grid.push_back(y * gridResolution);
                grid.push_back(z * gridResolution);
            }

    //  Generate grid mesh as it will be static
    glGenBuffers(1, &gridVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, grid.size() * sizeof(float), grid.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &gridVAO);
    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    //  Initialize buffers for isosurface
    glGenBuffers(1, &isosurfaceVBO);
    glGenVertexArrays(1, &isosurfaceVAO);

    glBindVertexArray(isosurfaceVAO);
    glBindBuffer(GL_ARRAY_BUFFER, isosurfaceVBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Isosurface::drawGrid(Shader *shader, const cam::Camera &camera)
{
    gridBounds.updateMatrices(camera.getProjectionMatrix());
    gridBounds.draw(*shader, camera.getViewMatrix());

//    glm::mat4 model = glm::mat4(1.0f);
//    model = glm::scale(model, glm::vec3(1.0f / gridResolution));
//    model = glm::translate(model, glm::vec3(-(gridSize * gridResolution) / 2));
//    shader->setMatrix4f("mvp", camera.getViewProjectionMatrix() * model);
//
//    glBindVertexArray(gridVAO);
//    glDrawArrays(GL_POINTS, 0, grid.size());
}

void Isosurface::drawIsosurface(Shader *shader, const cam::Camera &camera)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1.0f / gridResolution));
    model = glm::translate(model, glm::vec3(-(gridSize * gridResolution) / 2));
    shader->setMatrix4f("mvp", camera.getViewProjectionMatrix() * model);

    glBindVertexArray(isosurfaceVAO);
    glDrawArrays(GL_TRIANGLES, 0, isosurface.size());
}

void Isosurface::updateIsosurface(float isovalue, const std::function<float (float, float, float)> &fun)
{
    //  Sample values
    threshold = isovalue;
    for (int32_t z = 0; z < gridSize; ++z)
        for (int32_t y = 0; y < gridSize; ++y)
            for (int32_t x = 0; x < gridSize; ++x)
                values[getIndex(x, y, z)] = fun(x * gridResolution, y * gridResolution, z * gridResolution);
};

void Isosurface::generateIsosurfaceMesh()
{
    isosurface.clear();

    //  Marching cubes algorithm to generate triangle for mesh
    for (int32_t z = 0; z < gridSize - 1; ++z)
        for (int32_t y = 0; y < gridSize - 1; ++y)
            for (int32_t x = 0; x < gridSize - 1; ++x)
            {
                //  Check which vertices are under isosurface
                int32_t cubeIndex = 0;
                if (values[getIndex(x + 0, y + 0, z + 0)] <= threshold) cubeIndex |= 1;
                if (values[getIndex(x + 1, y + 0, z + 0)] <= threshold) cubeIndex |= 2;
                if (values[getIndex(x + 1, y + 0, z + 1)] <= threshold) cubeIndex |= 4;
                if (values[getIndex(x + 0, y + 0, z + 1)] <= threshold) cubeIndex |= 8;
                if (values[getIndex(x + 0, y + 1, z + 0)] <= threshold) cubeIndex |= 16;
                if (values[getIndex(x + 1, y + 1, z + 0)] <= threshold) cubeIndex |= 32;
                if (values[getIndex(x + 1, y + 1, z + 1)] <= threshold) cubeIndex |= 64;
                if (values[getIndex(x + 0, y + 1, z + 1)] <= threshold) cubeIndex |= 128;

                //  Cube is entirely in/out of the surface
                if (edgeTable[cubeIndex] == 0)
                    continue;

                //  Find the vertices where the surface intersects the cube
                glm::vec3 vertList[12];
                if (edgeTable[cubeIndex] & 1)       vertList[0] = linearInterpolation(x, y, z, x + 1, y, z);
                if (edgeTable[cubeIndex] & 2)       vertList[1] = linearInterpolation(x + 1, y, z, x + 1, y, z + 1);
                if (edgeTable[cubeIndex] & 4)       vertList[2] = linearInterpolation(x + 1, y, z + 1, x, y, z + 1);
                if (edgeTable[cubeIndex] & 8)       vertList[3] = linearInterpolation(x, y, z, x, y, z + 1);
                if (edgeTable[cubeIndex] & 16)      vertList[4] = linearInterpolation(x, y + 1, z, x + 1, y + 1, z);
                if (edgeTable[cubeIndex] & 32)      vertList[5] = linearInterpolation(x + 1, y + 1, z, x + 1, y + 1, z + 1);
                if (edgeTable[cubeIndex] & 64)      vertList[6] = linearInterpolation(x + 1, y + 1, z + 1, x, y + 1, z + 1);
                if (edgeTable[cubeIndex] & 128)     vertList[7] = linearInterpolation(x, y + 1, z, x, y + 1, z + 1);
                if (edgeTable[cubeIndex] & 256)     vertList[8] = linearInterpolation(x, y, z, x, y + 1, z);
                if (edgeTable[cubeIndex] & 512)     vertList[9] = linearInterpolation(x + 1, y, z, x + 1, y + 1, z);
                if (edgeTable[cubeIndex] & 1024)    vertList[10] = linearInterpolation(x + 1, y, z + 1, x + 1, y + 1, z + 1);
                if (edgeTable[cubeIndex] & 2048)    vertList[11] = linearInterpolation(x, y, z + 1, x, y + 1, z + 1);

                //  Generate triangles
                for (int i = 0; triTable[cubeIndex][i] != -1; i += 3) {
                    isosurface.push_back(vertList[triTable[cubeIndex][i    ]].x);
                    isosurface.push_back(vertList[triTable[cubeIndex][i    ]].y);
                    isosurface.push_back(vertList[triTable[cubeIndex][i    ]].z);

                    isosurface.push_back(vertList[triTable[cubeIndex][i + 1]].x);
                    isosurface.push_back(vertList[triTable[cubeIndex][i + 1]].y);
                    isosurface.push_back(vertList[triTable[cubeIndex][i + 1]].z);

                    isosurface.push_back(vertList[triTable[cubeIndex][i + 2]].x);
                    isosurface.push_back(vertList[triTable[cubeIndex][i + 2]].y);
                    isosurface.push_back(vertList[triTable[cubeIndex][i + 2]].z);
                }
            }

    //  Generate isosurface mesh
    glBindBuffer(GL_ARRAY_BUFFER, isosurfaceVBO);
    glBufferData(GL_ARRAY_BUFFER, isosurface.size() * sizeof(float), isosurface.data(), GL_DYNAMIC_DRAW);
}

glm::vec3 Isosurface::linearInterpolation(int32_t x1, int32_t y1, int32_t z1, int32_t x2, int32_t y2, int32_t z2) const
{
    int32_t p1 = 3 * getIndex(x1, y1, z1);
    int32_t p2 = 3 * getIndex(x2, y2, z2);
    float v1 = values[getIndex(x1, y1, z1)];
    float v2 = values[getIndex(x2, y2, z2)];

    glm::vec3 P1 = glm::vec3(grid[p1], grid[p1 + 1], grid[p1 + 2]);
    glm::vec3 P2 = glm::vec3(grid[p2], grid[p2 + 1], grid[p2 + 2]);

    float val = glm::abs(v1 - threshold) / glm::abs(v1 - v2);
    return float(1.0 - val) * P1 + val * P2;
}
