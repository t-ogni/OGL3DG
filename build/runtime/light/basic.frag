#version 330 core

in vec2 fragTextureCoord;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 outputColor;

uniform vec4 fragColor;

void main()
{
    outputColor = fragColor;
}


