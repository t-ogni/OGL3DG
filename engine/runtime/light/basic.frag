#version 330 core

in vec2 fragTextureCoord;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 color;

uniform vec4 ucolor;

void main()
{
    color = vec4(ucolor.xyz, 0.8f);
}


