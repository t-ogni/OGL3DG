//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#include "Renderer.h"

Renderer::Renderer() = default;


float Renderer::getAmbientStrength() const {
    return ambientStrength;
}

void Renderer::setAmbientStrength(float ambientStrength1) {
    ambientStrength = ambientStrength1;
}

void Renderer::addToScene(Object *object) {
    objects.push_back(object);
}

void Renderer::removeFromScene(Object *object) {

}

void Renderer::draw(glm::mat4 VPmat) {
    for (auto &object : objects) {

        if(object-> material-> texture != nullptr)
            object -> material-> texture-> bind();

        if(object->shader != nullptr) {
            object->shader->bind();
            object->shader->uniformSet("matVP", VPmat);

            for (auto &mesh : object->meshes) {
                glm::vec3 ambient = mesh->material->Ambient * ambientStrength;
                object->shader->uniformSet("material.Ambient", ambient);
                object->shader->uniformSet("material.Diffuse", mesh->material->Diffuse);
                object->shader->uniformSet("material.Specular", mesh->material->Specular);
                object->shader->uniformSet("material.alfa", mesh->material->alfa);
                object->shader->uniformSet("material.shine", mesh->material->shine);
                object->shader->uniformSet("material.illum", mesh->material->illum);
                mesh->draw();
            }
//            for(int lightIndex = 0; lightIndex < lights.size(); lightIndex++){
//                std::string Name = "lights[";
//                Name += std::to_string(lightIndex);
//                Name += "]";
//                object->shader->uniformSet(Name, lights[lightIndex]->);
//
//            }
        }

        if(object-> material-> texture != nullptr)
            object -> material-> texture-> unbind();
    }
}

void Renderer::addLight(Object *light){
    lights.push_back(light);
}

void Renderer::drawMode(int mode) {
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

Renderer::~Renderer() = default;

// x - абсцисс
// y - ординат
// z - аппликат