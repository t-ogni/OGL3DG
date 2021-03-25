//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#include "Material.h"

Material::Material(glm::vec4 color1) :
        color(color1) {

}

Material::Material(Texture *texture1, glm::vec4 color1) :
        texture(texture1),
        color(color1) {

}

void Material::loadMtl(const char *path) {
    std::string currentMtl;  // map.rstring() ?
    std::ifstream mtlFile(path);
    if (!mtlFile) {
        Log->warning("Material file in %s cannot be opened", path);
        return;
    } else
        Log->info("Material file in %s was loaded successfully", path);
    std::string fileLine;
    while (mtlFile) {
        getline(mtlFile, fileLine);
        std::istringstream lineStream(fileLine);
        std::string oper;
        lineStream >> oper;
        if (oper == "newmtl") {
            lineStream >> currentMtl;
            surfaces[currentMtl] = new SurfaceStruct();
        } else if (oper == "Ka") {
            glm::vec3 Ka;
            lineStream >> Ka.x >> Ka.y >> Ka.z;
            surfaces[currentMtl]->Ambient = Ka;
        } else if (oper == "Kd") {
            glm::vec3 Kd;
            lineStream >> Kd.x >> Kd.y >> Kd.z;
            surfaces[currentMtl]->Diffuse = Kd;
        } else if (oper == "Ks") {
            glm::vec3 Ks;
            lineStream >> Ks.x >> Ks.y >> Ks.z;
            surfaces[currentMtl]->Specular = Ks;
        } else if (oper == "d") {
            float d;
            lineStream >> d;
            surfaces[currentMtl]->alfa = d;
        } else if (oper == "Ns") {
            float Ns;
            lineStream >> Ns;
            surfaces[currentMtl]->shine = Ns;
        } else if (oper == "illum") {
            int n;
            lineStream >> n;
            surfaces[currentMtl]->illum = n;
        }

    }
}

void Material::setColor(glm::vec3 color1) {
    color = glm::vec4(color1, 1.0f);
}

void Material::setColor(glm::vec4 color1) {
    color = color1;
}

SurfaceStruct *Material::getSurface(const std::string &title) {
    return surfaces[title] ? surfaces[title] : new SurfaceStruct();
}

Material::~Material() = default;


/*
Структура .MTL:

newmtl string          название материала
Ka f f f              Ambient-свойства материала  float[3]
Kd f f f              Diffuse-свойства материала
Ks f f f              Specular-свойства материала
d f                      Прозрачность float 0..1
Ns f                      Shine (блеск)  float 0..128 (^f)
illum n                  режим int 0..?
map_Ka  имя файла с Ambient-текстурой      (Может отсутствовать)
map_Kd  имя файла с Diffuse-текстурой        (Может отсутствовать)
map_Ks  имя файла с Specular-текстурой      (Может отсутствовать)

# комментарий.

newmtl .....
.....
*/

/*
Краткое описание свойств

AMBIENT - цвет фонового отражения материала
DIFFUSE -  цвет рассеянного отражения материала
SPECULAR - цвет зеркального отражения материала
EMISSION - цвет собственного излучения материала
SHININESS - степень в формуле зеркального отражения (коэффициент блеска). Допускаются значения в интервале [0; 128].
*/