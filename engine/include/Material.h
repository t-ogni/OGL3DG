//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#ifndef OGL3DG_MATERIAL_H
#define OGL3DG_MATERIAL_H

#include <glm/glm.hpp>
#include "Texture.h"

class Material {
private:
    glm::vec4 color { 1.0f };
    Texture *texture = nullptr;

public:
    Material();

    ~Material();
};


#endif //OGL3DG_MATERIAL_H
