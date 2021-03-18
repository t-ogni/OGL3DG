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
    vec4 texture = texture(TextureSample, fragTextureCoord);
    if(vec3(texture) == vec3(0, 0, 0)){
        texture = vec4(0.2, 0.2, 0.2, 1);
    }
    
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, fragNormal);

    vec3 ambient = light.color;

    float diffuseAngle = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diffuseAngle * light.color;

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
    vec3 specular = material.specular * spec * light.color ;

    vec3 result = (ambient + diffuse + specular) * vec3(texture);
    color = vec4(result, 1.0f);
}



//uniform LightStruct lights[LIGHTS_MAX];
//uniform int lightsAmount;

