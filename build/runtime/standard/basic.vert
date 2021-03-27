#version 330 core
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 ResultMatrix;
uniform mat4 ModelMatrix;

out vec2 fragTextureCoord;
out vec3 fragNormal;
out vec3 fragPos;

void main()
{
    gl_Position = ResultMatrix * vec4(VertexPosition, 1.0f);
    fragPos = vec3(ModelMatrix * vec4(VertexPosition, 1.0f));
    fragNormal = normal * mat3(transpose(inverse(ModelMatrix)));
    fragTextureCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}