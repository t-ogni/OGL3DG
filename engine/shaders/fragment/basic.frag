#version 450 core
#define LIGHTS_MAX 10
//dont fogot delete posbuild shader path

in vec2 fragTextureCoord;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 color;

struct LightStruct {
    vec3 position;
    vec3 color;
};

struct MaterialStuct {
    vec3 Ambient;  // background color
    vec3 Diffuse;  // light object
    vec3 Specular; // reflection
    float alfa;
    float shine;
    int illum;
};


uniform sampler2D TextureSample;
uniform MaterialStuct material;

uniform LightStruct lights[LIGHTS_MAX];
uniform int lightsAmount;


void main()
{
    for(int i = 0; i < lightsAmount; i++) {
        vec3 lightDirection = normalize(lights[i].position - fragPos);
        float diff = max(dot(fragNormal, lightDirection), 0.0);
        fragColor = fragColor * vec4(diff * lights[i].color, 1.0f);
    }

    color = texture(TextureSample, fragTextureCoord);
}