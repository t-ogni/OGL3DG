//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 019 19.09.20 at 5:59.

#ifndef OGL3DG_OBJECT_H
#define OGL3DG_OBJECT_H

#include "components/initals/Mesh.h"
#include "components/initals/Transform.h"
#include "shaders/standardShader.h"

#include <vector>

class Renderer;

class Object {
    friend Renderer;
protected:
    std::string label;
    std::vector<Mesh *> meshes;
    Shader *shader = nullptr;
    Material *material = nullptr;

public:
    Transform *transform = new Transform();

    Object() = default;
    explicit Object(const char* label);
    std::string getLabel();

    void setShader(Shader *shader);
    void setMaterial(Material *material);

    void addMesh(Mesh *mesh);
    void loadObjFromFile(const char *path);

    ~Object();
};


#endif //OGL3DG_OBJECT_H
