#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 MVP;
uniform vec3 PlayerPos;
out vec3 outColor;


void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
        outColor = position;
}