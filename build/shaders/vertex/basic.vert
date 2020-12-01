#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 MVP;
uniform vec4 color;

out vec4 fragColor;
out vec2 fragTextureCoord;


void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
    fragColor = color;
    fragTextureCoord = texCoord;
}