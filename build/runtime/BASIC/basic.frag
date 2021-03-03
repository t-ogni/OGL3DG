#version 330 core
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
    vec3 ambient;  // background color
    vec3 diffuse;  // light object
    vec3 specular; // reflection
    float alfa;
    float shine;
    int illum;
};

uniform vec3 viewPos;
uniform sampler2D TextureSample;
uniform LightStruct light;  //s[LIGHTS_MAX];
uniform MaterialStuct material;

void main()
{
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, fragNormal);

    float diffuseAngle = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diffuseAngle * light.color;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
    vec3 specular = spec * light.color * material.specular;

    color = texture(TextureSample, fragTextureCoord);
    color += vec4(material.ambient + diffuse, 1.0);
    color += vec4(specular, 1.0);
}



//uniform LightStruct lights[LIGHTS_MAX];
//uniform int lightsAmount;

