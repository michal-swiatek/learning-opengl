#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec3 fragNormal;
out vec3 fragPos;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 mvp;
uniform mat3 modelInvTrans;

void main() {
    fragNormal = modelInvTrans * vNormal;
    fragPos = vec3(model * vec4(vPos, 1.0f));
    texCoords = vTexCoords;

    gl_Position = mvp * vec4(vPos, 1.0f);
}
