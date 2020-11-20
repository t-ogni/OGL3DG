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
        object-> shader-> bind();
        object-> shader-> uniformSet("MVP", MVmat);
        for (auto &mesh : object-> meshes) {
            mesh->draw();
        }
    }
}

Renderer::~Renderer() = default;

