#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec3 fragNormal;
out vec3 fragPos;
out vec2 texCoords;

uniform mat4 mv;
uniform mat4 mvp;
uniform mat3 mvInvTrans;

void main() {
    fragNormal = mvInvTrans * vNormal;
    fragPos = vec3(mv * vec4(vPos, 1.0f));
    texCoords = vTexCoords;

    gl_Position = mvp * vec4(vPos, 1.0f);
}
