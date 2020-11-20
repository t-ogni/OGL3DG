//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#ifndef OGL3DG_RENDERER_H
#define OGL3DG_RENDERER_H

#include <vector>
#include "Object.h"
#include "Camera.h"

class Renderer {
private:
    std::vector <Object *> objects;

public:
    Renderer();
    void addToScene(Object *object);
    void removeFromScene(Object *object);
    void draw(glm::mat4 MVmat);
    ~Renderer();
};


#endif //OGL3DG_RENDERER_H
