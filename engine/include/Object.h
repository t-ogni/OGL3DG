//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 019 19.09.20 at 5:59.

#ifndef OGL3DG_OBJECT_H
#define OGL3DG_OBJECT_H

//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include "Console.h"
//#include "Shader.h"
// included from "Mesh.h"

#include "Material.h"
#include "Mesh.h"
#include <vector>

class Renderer;

class Object {
    friend Renderer;
private:
    std::vector<Mesh *> meshes;
    Shader *shader = nullptr; // todo basic shader
    Material *material = new Material();

public:

    Object() = default;
    Object(const char *pathToObj);
    Object(const char *pathToObj, Material *material1);
    Object(const char *pathToObj, Texture *texture1);
    Object(const char *pathToObj, const char *pathToTexture);

    void addMesh(std::vector<Vertex> vertices);
    void setShader(Shader *shader1);
    void setMaterial(Material *material1);
    void loadObjFromFile(const char *path);
    void loadMaterialFromFile(const char *path);
    ~Object();
};


#endif //OGL3DG_OBJECT_H
