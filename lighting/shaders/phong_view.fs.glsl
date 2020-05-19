#version 330
out vec4 fColor;

struct Material
{
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;

    float shininess;
};

struct Light
{
    vec4 position;  //  w component is used to test whether light is directional or point

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 fragNormal; //  In view space
in vec3 fragPos;    //  In view space
in vec2 texCoords;

//  Lighting is specified in view space
uniform Light light = Light(vec4(vec3(0.0), 1.0), vec3(0.1), vec3(1.0), vec3(0.5));

uniform Material material;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(fragPos - vec3(light.position));
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectionDir = reflect(lightDir, normal);

    vec3 ambient = vec3(texture(material.ambient, texCoords)) * light.ambient;

    float diff = max(dot(-lightDir, normal), 0.0f);
    vec3 diffuse = diff * vec3(texture(material.diffuse, texCoords)) * light.diffuse;

    float spec = pow(max(dot(reflectionDir, viewDir), 0.0f), material.shininess * 128);
    vec3 specular = spec * vec3(texture(material.specular, texCoords)) * light.specular;

    fColor = vec4(ambient + diffuse + specular, 1.0f);
}
