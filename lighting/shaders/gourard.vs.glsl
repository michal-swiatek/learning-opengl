#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec2 texCoords;

out vec3 ambient;
out vec3 diffuse;
out vec3 specular;

struct Light
{
    vec4 position;  //  w component is used to test whether light is directional or point

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//  Lighting is specified in view space
uniform Light light = Light(vec4(vec3(0.0), 1.0), vec3(0.1), vec3(1.0), vec3(0.5));
uniform float shininess;

uniform mat4 mv;
uniform mat4 mvp;
uniform mat3 mvInvTrans;

void main() {
    //  Transform vertex/normal to view space
    vec3 fragNormal = mvInvTrans * vNormal;
    vec3 fragPos = vec3(mv * vec4(vPos, 1.0f));
    texCoords = vTexCoords;

    //  Lighting calculation
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(fragPos - vec3(light.position));
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectionDir = reflect(lightDir, normal);

    ambient = light.ambient;

    float diff = max(dot(-lightDir, normal), 0.0f);
    diffuse = diff * light.diffuse;

    float spec = pow(max(dot(reflectionDir, viewDir), 0.0f), shininess * 128);
    specular = spec * light.specular;

    //  Vertex position
    gl_Position = mvp * vec4(vPos, 1.0f);
}
