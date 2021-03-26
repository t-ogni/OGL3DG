//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 014 14.11.20 at 1:01.

#ifndef OGL3DG_MESH_H
#define OGL3DG_MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "shaders/Shader.h"
#include "Material.h"

struct Vertex {
    glm::vec3 position;
    glm::vec2 textureCoord;
    glm::vec3 normal;

    explicit Vertex(glm::vec3 position = glm::vec3(0.0f),
           glm::vec2 textureCoord = glm::vec2(0.0f),
           glm::vec3 normal = glm::vec3(0.0f)) :
           position(position),
           textureCoord(textureCoord),
           normal(normal) { }
};

class Mesh {
    friend Renderer;
private:
    unsigned int vao = 0;	// Vertex Array Object
    unsigned int vbo = 0;	// Vertex Buffer Object
    unsigned int size = 0;  // amount of vertices
    SurfaceStruct *surface = nullptr;

public:
    explicit Mesh(std::vector<Vertex> vertices, SurfaceStruct *surface,  int mode = GL_STATIC_DRAW);
    void setMaterial(SurfaceStruct *mat);

    void draw() const;
    ~Mesh();

};


#endif //OGL3DG_MESH_H
