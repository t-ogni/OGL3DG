#version 330 core
#define LIGHTS_MAX 10
//dont fogot delete posbuild shader path

in vec2 fragTextureCoord;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 color;

struct Light {
    vec3 position;
    vec3 color;
};

struct Material {
    vec3 diffuse;  // light object
    vec3 specular; // reflection
    float alfa;
    float shine;
    int illum;
};

uniform sampler2D TextureSample;
uniform vec3 viewPos;
uniform vec4 fragColor;
uniform Light light;  //s[LIGHTS_MAX];
uniform Material material;

void main()
{
    vec4 texture = texture(TextureSample, fragTextureCoord) * fragColor;

    vec3 lightDir = normalize(light.position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, fragNormal);

    vec4 ambient = texture * 0.3f;

    float diffuseAngle = max(dot(fragNormal, lightDir), 0.0);
    vec4 diffuse = diffuseAngle * texture ;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
    vec4 specular = vec4(material.specular * spec, 1.0f);

    color = (ambient + diffuse + specular) * vec4(light.color, 1.0f);
}


//uniform LightStruct lights[LIGHTS_MAX];
//uniform int lightsAmount;

