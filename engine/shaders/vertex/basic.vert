#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 MVP;

out vec3 outColor;


void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
    outColor = vec3(gl_Position.x, gl_Position.y, gl_Position.y);
}