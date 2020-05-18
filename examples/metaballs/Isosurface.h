/*
 *  Created by swiat on 18.05.2020.
 *  Github: https://github.com/michal-swiatek/learning-opengl
 */

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <functional>

#include <glad/glad.h>

#include "Camera.h"
#include "Shader.h"
#include "Box.h"

class Isosurface
{
public:
    explicit Isosurface(int32_t gridSize = 0, float gridResolution = 1.0);

    void drawGrid(Shader* shader, const cam::Camera& camera);
    void drawIsosurface(Shader* shader, const cam::Camera& camera);

    void updateIsosurface(float isovalue, const std::function<float(float, float, float)>& fun);
    void generateIsosurfaceMesh();

private:
    int32_t gridSize;
    float gridResolution;
    Box gridBounds;

    std::vector<float> grid;
    std::vector<float> isosurface;

    //  Isosurface parameters
    std::vector<float> values;  //  Sample values
    float threshold;

    unsigned int gridVBO, gridVAO;
    unsigned int isosurfaceVBO, isosurfaceVAO;

    //  Utility functions
    [[nodiscard]] glm::vec3 linearInterpolation(int32_t x1, int32_t y1, int32_t z1, int32_t x2, int32_t y2, int32_t z2) const;
    [[nodiscard]] inline int32_t getIndex(int32_t x, int32_t y, int32_t z) const { return (z * gridSize + y) * gridSize + x; }
};

#endif //GRID_H
