#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoords;

out vec3 color;
out vec2 texCoords;

uniform mat4 transform;

void main() {
    color = vColor;
    texCoords = vTexCoords;

    gl_Position = transform * vec4(vPos, 1.0);
}
