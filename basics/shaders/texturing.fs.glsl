#version 330

out vec4 fColor;

in vec3 color;
in vec2 texCoords;

uniform bool use_color;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    if (use_color)
        fColor = mix(texture(texture1, texCoords), texture(texture2, texCoords), 0.3) * vec4(color, 1.0);
    else
        fColor = mix(texture(texture1, texCoords), texture(texture2, texCoords), 0.5);
}
