#version 330

layout (location = 0) in vec3 vPos;

uniform mat4 mvp = mat4(1.0f);

void main() {
    gl_Position = mvp * vec4(vPos, 1.0f);
}
