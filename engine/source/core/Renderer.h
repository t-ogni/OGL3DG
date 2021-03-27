//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 020 20.11.20 at 21:56.

#ifndef OGL3DG_RENDERER_H
#define OGL3DG_RENDERER_H

#include <vector>
#include "components/object/Object.h"
#include "components/camera/Camera.h"
#include "core/Window.h"

class Renderer {
private:
    std::vector <Object *> objects;
    std::vector <Object *> lights;
    float ambientStrength = 0.1f;
    Material *defaultMaterial = nullptr;

public:
    float getAmbientStrength() const;
    void setAmbientStrength(float ambientStrength);

    Renderer();
    void addObject(Object &object);
    void removeObject(Object &object); // todo delete objects from scene
    void addLight(Object &object);
    void removeLight(Object &object);
    Object * getObjectPtr(const std::string& label);
    void draw(Camera *camera);
    static void drawMode(int mode);
    ~Renderer();
};


#endif //OGL3DG_RENDERER_H
