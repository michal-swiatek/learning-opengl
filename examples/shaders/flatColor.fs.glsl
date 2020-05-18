#version 330

out vec4 fColor;

uniform vec3 diffuseColor = vec3(0.8f);

void main() {
    fColor = vec4(diffuseColor, 1.0f);
}
