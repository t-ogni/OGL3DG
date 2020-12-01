//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#ifndef OGL3DG_MATERIAL_H
#define OGL3DG_MATERIAL_H

#include <glm/glm.hpp>
#include "Texture.h"

class Renderer;

class Material {
    friend Renderer;
private:
    glm::vec4 color;
    Texture *texture;

public:
    Material();
    Material(Texture *texture1, glm::vec4 color1 = {0.f, 1.f, 0.f, 1.f});
    void loadMtl(const char *path);
    void setColor(glm::vec3 color1);
    void setColor(glm::vec4 color1);
    ~Material();
};


#endif //OGL3DG_MATERIAL_H
