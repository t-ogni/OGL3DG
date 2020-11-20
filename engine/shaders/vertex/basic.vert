#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 MVP;
uniform vec3 color;

out vec3 outColor;


void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
    outColor = color;
}