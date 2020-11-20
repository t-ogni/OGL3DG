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

class Object {
public:
    std::vector<Mesh *> meshes;
    Shader *shader = nullptr;
    Material *material = nullptr;

    Object() = default;
    Object(const char *path);
    Object(Mesh *mesh1);

    void addMesh(std::vector<Vertex> vertices);
    void bindShader(Shader *shader1);
    void loadFromFile(const char *path);

    ~Object();
};


#endif //OGL3DG_OBJECT_H
