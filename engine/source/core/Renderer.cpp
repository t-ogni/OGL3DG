//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#include "Renderer.h"

Renderer::Renderer() = default;

bool Renderer::addObject(Object &object) {
    if(std::find(objects.begin(), objects.end(), &object) == objects.end())
        objects.push_back(&object);
    else
        return false;
    return true;
}

bool Renderer::removeObject(Object &object) {
    std::erase(objects, &object);  // since c++20 !!!
    return true;
}

bool Renderer::addLight(BaseLight &object) {
    if(std::find(lights.begin(), lights.end(), &object) == lights.end())
        lights.push_back(&object);  // since c++20 !!!
    else
        return false;
    return true;
}

bool Renderer::removeLight(BaseLight &object) {
    lights.push_back(&object);
    return true;
}


void Renderer::draw(Camera *camera) {
    glm::mat4 ViewProjectionMatrix = camera-> getProjViewMat();
    for (auto &object : objects) {
        object-> transform-> updateMat();
        lights[0]->transform->updateMat();
        glm::mat4 ModelMatrix = object-> transform-> getModel();
        glm::mat4 ResultMatrix = ViewProjectionMatrix * ModelMatrix;

        if(object-> material-> DiffuseTexture != nullptr)
            object -> material-> DiffuseTexture-> bind();
        if(object->shader != nullptr) {
            object->shader->bind();
            object->shader->uniformSet("ResultMatrix", ResultMatrix);
            object->shader->uniformSet("ModelMatrix", ModelMatrix);

            object->shader->uniformSet("viewPos", camera->transform->getPosition());
            object->shader->uniformSet("fragColor", object->material->color);

            for (auto &mesh : object->meshes) {
                object->shader->uniformSet("material.diffuse", mesh->surface->diffuse);
                object->shader->uniformSet("material.specular", mesh->surface->specular);
                object->shader->uniformSet("material.alfa", mesh->surface->alfa);
                object->shader->uniformSet("material.shine", mesh->surface->shine);
                object->shader->uniformSet("material.illum", mesh->surface->illumination);
                mesh->draw();
            }

           // lights
           object->shader->uniformSet("lightsAmount", int(lights.size()));
            for(int lightIndex = 0; lightIndex < lights.size(); lightIndex++){
                auto pos = lights[lightIndex]->transform->getPosition();
                auto direction = lights[lightIndex]->transform->getDirection();
                auto color = lights[lightIndex]->material->color;
                std::string uniformName = "lights[";
                uniformName += std::to_string(lightIndex);
                uniformName += "]";
                object->shader->uniformSet((uniformName + ".position").c_str(), pos);
                object->shader->uniformSet((uniformName + ".color").c_str(), glm::vec3(color));
            }

            Shader::unbind();
        }

        if(object-> material-> DiffuseTexture != nullptr)
            Texture::unbind();
    }
}

void Renderer::drawMode(int mode) {
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

Object *Renderer::getObjectPtr(const std::string& label) {
    for (auto &object : objects)
        if(object->label == label)
            return object;
    return new Object((std::string("undefined_")+label).c_str());
}

Renderer::~Renderer() = default;

// x - абсцисс
// y - ординат
// z - аппликат