//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 019 19.09.20 at 5:59.

#ifndef OGL3DG_OBJECT_H
#define OGL3DG_OBJECT_H

#include "components/initals/Mesh.h"
#include "components/initals/Transform.h"
#include "shaders/standartShader.h"
#include <vector>

class Renderer;

class Object {
    friend Renderer;
private:
    std::vector<Mesh *> meshes;
    Shader *shader = new standartShader();
    Material *material = new Material();

public:
    std::string label = "unknown";
    Transform *transform = new Transform();

    Object() = default;
    explicit Object(const char *pathToObj);
    Object(const char *pathToObj, Material *material1);
    Object(const char *pathToObj, Texture *texture1);
    Object(const char *pathToObj, const char *pathToTexture);

    void setShader(Shader *shader);
    void setMaterial(Material *material);
    void addMesh(Mesh *mesh);
    void loadObjFromFile(const char *path);

    //void setRandomColors(glm::vec3 from = glm::vec3(0.5f), glm::vec3 to = glm::vec3(1.0f));
    ~Object();
};


#endif //OGL3DG_OBJECT_H
