//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#ifndef OGL3DG_MATERIAL_H
#define OGL3DG_MATERIAL_H

#include <glm/glm.hpp>
#include <map>
#include <fstream>
#include "Texture.h"
#include "core/Console.h"

class Renderer;

struct MaterialStuct {
    glm::vec3 Ambient = glm::vec3(0.2f);  // background color
    glm::vec3 Diffuse = glm::vec3(0.8f);  // light object
    glm::vec3 Specular = glm::vec3(1.0f); // reflection
    float alfa = 1.0f;
    float shine = 1.0f;
    int illum = 1;
};

class Material {
    friend Renderer;
private:
    glm::vec4 color {1.0f};
    Texture *texture = nullptr;
    std::map <std::string, MaterialStuct *> materials;

public:
    Material() = default;
    explicit Material(glm::vec4 color);
    explicit Material(Texture *texture, glm::vec4 color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

    void loadMtl(const char *path);

    void setColor(glm::vec3 color);
    void setColor(glm::vec4 color);

    MaterialStuct *getMaterial(const std::string& title);

    ~Material();
};


#endif //OGL3DG_MATERIAL_H
