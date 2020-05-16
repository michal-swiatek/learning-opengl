#version 330

out vec4 fColor;

in vec3 fragNormal; //  In view space
in vec3 fragPos;    //  In view space
in vec2 texCoords;

//  Lighting
uniform vec3 lightPos;  //  In view space
uniform vec3 lightColor;

uniform vec3 ambientColor = vec3(0.1f);
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform int shininess = 32;

void main() {
    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(fragPos - lightPos);
    vec3 viewDir = normalize(-fragPos);
    vec3 reflectionDir = reflect(lightDir, normal);

    vec3 ambient = ambientColor * lightColor;
    vec3 diffuse = max(dot(-lightDir, normal), 0.0f) * lightColor;
    vec3 specular = pow(max(dot(reflectionDir, viewDir), 0.0f), shininess) * specularColor * lightColor;

    fColor = vec4((ambient + diffuse + specular) * diffuseColor, 1.0f);
}
