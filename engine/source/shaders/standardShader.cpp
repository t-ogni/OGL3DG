//
// Created by moonlin on 20.01.2021.
//

#include "standardShader.h"

std::string fragRawCode = R"(
#version 330 core
#define LIGHTS_MAX 10

in vec2 fragTextureCoord;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 color;

struct LightStruct {
    vec3 position;
    vec3 color;
};

uniform vec3 viewPos;
uniform sampler2D TextureSample;
uniform LightStruct light;  //s[LIGHTS_MAX];

void main()
{
    vec3 ambient = vec3(0.1f);
    vec3 objectColor = vec3(0.5f, 0.3f, 0.0f);
    if(light.position.x < 0) objectColor = vec3(0.0f, 0.5f, 0.1f);

    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, fragNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.color;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    color = vec4(result, 1.0) + texture(TextureSample, fragTextureCoord);
})";

std::string vertRawCode = R"(
#version 330 core
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 matModViewProj;
uniform mat4 matModel;

out vec2 fragTextureCoord;
out vec3 fragNormal;
out vec3 fragPos;

void main()
{
    gl_Position = matModViewProj * vec4(VertexPosition, 1.0f);
    fragPos = vec3(vec4(VertexPosition, 1.0f) * matModel);
    fragNormal = mat3(transpose(inverse(matModel))) * normal; // if was scaled
    fragTextureCoord = texCoord;
})";

standardShader::standardShader(){
    GLuint vertex = compileShader(vertRawCode, GL_VERTEX_SHADER);
    GLuint fragment = compileShader(fragRawCode, GL_FRAGMENT_SHADER);
    linkProgram(vertex, fragment);
}