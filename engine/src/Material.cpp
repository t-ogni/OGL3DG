//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#include "Material.h"

Material::Material(Texture *texture1, glm::vec4 color1) {
    texture = texture1;
    color = color1;
}

void Material::loadMtl(const char *path) {

}

void Material::setColor(glm::vec3 color1) {
    color = glm::vec4(color1, 1.0f);
}

void Material::setColor(glm::vec4 color1) {
    color = color1;
}

Material::~Material() {}

