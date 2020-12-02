//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#include "Renderer.h"

Renderer::Renderer() = default;


void Renderer::addToScene(Object *object) {
    objects.push_back(object);
}

void Renderer::removeFromScene(Object *object) {

}

void Renderer::draw(glm::mat4 MVmat) {
    for (auto &object : objects) {

        if(object-> material-> texture != nullptr)
            object -> material-> texture-> bind();

        if(object->shader != nullptr) {

            object->shader-> bind();
            object->shader-> uniformSet("MVP", MVmat);
            object->shader-> uniformSet("color", object-> material-> color);
        }
        for (auto &mesh : object-> meshes) {
            mesh->draw();
        }

        if(object-> material-> texture != nullptr)
            object -> material-> texture-> unbind();
    }
}

Renderer::~Renderer() = default;

// x - абсцисс
// y - ординат
// z - аппликат