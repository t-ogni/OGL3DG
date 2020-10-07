//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 019 19.09.20 at 5:59.

#ifndef OGL3DG_OBJECT_H
#define OGL3DG_OBJECT_H

#include "Console.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/glm.hpp>

class Object {
public:
    glm::vec3 Position {}, Size {}, Velocity {};
    glm::vec3 Color {};
    float Rotation = 0.0f;
    bool Destroyed = false;

    Object();
    Object(const char *path);
    void loadObj(const char *path);
    ~Object();

    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;
};


#endif //OGL3DG_OBJECT_H
