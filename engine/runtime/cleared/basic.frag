#version 330 core
//#define LIGHTS_MAX 10
//dont fogot delete posbuild shader path

in vec2 fragTextureCoord;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 color;

uniform sampler2D TextureSample;

void main()
{
    vec4 texture = texture(TextureSample, fragTextureCoord);
    color = texture;
}



//uniform LightStruct lights[LIGHTS_MAX];
//uniform int lightsAmount;

