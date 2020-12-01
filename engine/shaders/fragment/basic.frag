#version 330 core //dont fogot delete posbuild sha
in vec4 fragColor;
in vec2 fragTextureCoord;

out vec4 color;

uniform sampler2D TextureSample;

void main()
{
    color = texture(TextureSample, fragTextureCoord) + fragColor;
}