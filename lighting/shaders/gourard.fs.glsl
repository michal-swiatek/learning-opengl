#version 330
out vec4 fColor;

in vec2 texCoords;

in vec3 ambient;
in vec3 diffuse;
in vec3 specular;

struct Material
{
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

uniform Material material;

void main() {
    vec3 ambient = ambient * vec3(texture(material.ambient, texCoords));
    vec3 diffuse = diffuse * vec3(texture(material.diffuse, texCoords));
    vec3 specular = specular * vec3(texture(material.specular, texCoords));

    fColor = vec4(ambient + diffuse + specular, 1.0f);
}
