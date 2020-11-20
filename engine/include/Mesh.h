//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 014 14.11.20 at 1:01.

#ifndef OGL3DG_MESH_H
#define OGL3DG_MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec2 textureCoord;
    glm::vec3 normal;

    Vertex(glm::vec3 position = glm::vec3(0.0f), glm::vec2 textureCoord = glm::vec2(0.0f), glm::vec3 normal = glm::vec3(0.0f)) {
        this->position = position;
        this->textureCoord = textureCoord;
        this->normal = normal;
    }
};

class Mesh {
protected:
    unsigned int vao;		// Vertex Array Object
    unsigned int vbo;		// Vertex Buffer Object
    unsigned int size;

    void setupMesh(std::vector<Vertex> vertices, int mode = GL_STATIC_DRAW);

public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, int mode = GL_STATIC_DRAW);

    void draw() const;

    ~Mesh();

};


#endif //OGL3DG_MESH_H
