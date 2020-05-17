#version 330

layout (location = 0) in vec3 vPos;

uniform mat4 vp;

void main() {
    gl_Position = vp * vec4(vPos, 1.0f);
}
