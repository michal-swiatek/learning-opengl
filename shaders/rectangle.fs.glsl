#version 330

in vec3 color;
out vec4 fColor;

uniform float color_scale;

void main() {
    fColor = vec4(color * color_scale, 1.0f);
}
