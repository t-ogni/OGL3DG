//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#ifndef OGL3DG_MATERIAL_H
#define OGL3DG_MATERIAL_H

#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"

class Renderer;

struct MaterialStuct {
    glm::vec3 Ambient = glm::vec3(0.2f);  // background color
    glm::vec3 Diffuse = glm::vec3(0.8f);  // light object
    glm::vec3 Specular = glm::vec3(1.0f); // reflection
    float alfa = 0.0;
    float shine = 0.0;
    short illum = 1;
};

class Material {
    friend Renderer;
private:
    glm::vec4 color;
    Texture *texture = nullptr;
    std::vector <MaterialStuct> materials;

public:
    Material() = default;
    Material(Texture *texture1, glm::vec4 color1 = {0.f, 1.f, 0.f, 1.f});
    void loadMtl(const char *path);
    void setColor(glm::vec3 color1);
    void setColor(glm::vec4 color1);

    ~Material();
};


#endif //OGL3DG_MATERIAL_H

/*
Структура .MTL:

newmtl string          название материала
Ka f f f              Ambient-свойства материала  float[3]
Kd f f f              Diffuse-свойства материала
Ks f f f              Specular-свойства материала
d  f                      Прозрачность float 0..1
Ns f                      Shine (блеск)  float 0..?
illum n                  режим float 0..?
map_Ka  имя файла с Ambient-текстурой      (Может отсутствовать)
map_Kd  имя файла с Diffuse-текстурой        (Может отсутствовать)
map_Ks  имя файла с Specular-текстурой      (Может отсутствовать)

# комментарий.

newmtl .....
.....
*/