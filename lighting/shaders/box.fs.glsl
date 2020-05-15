#version 330

in vec2 texCoords;

out vec4 fColor;

uniform bool use_color;
uniform vec4 color;

void main() {
    if (use_color)
        fColor = color;
    else
        fColor = vec4(1.0, 0.0, 0.0, 1.0);
}
