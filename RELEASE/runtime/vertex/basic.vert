#version 450 core
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
}