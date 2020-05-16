#version 330
out vec4 fColor;

uniform vec3 diffuseColor;

void main() {
    fColor = vec4(diffuseColor, 1.0f);
}
