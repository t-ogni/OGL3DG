#version 330 core
in vec3 outColor;
in vec2 TexCoord;
out vec4 color;

uniform sampler2D inTexture;

void main()
{
    color = texture(inTexture, TexCoord) * vec4(outColor, 1.0f);
}