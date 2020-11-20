//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 014 14.11.20 at 1:01.

#include "Mesh.h"

Mesh::Mesh() :
        vbo(0),
        vao(0),
        size(0)
{

}

Mesh::Mesh(std::vector<Vertex> vertices, int mode) {
    setupMesh(vertices, mode);
}

void Mesh::setupMesh(std::vector<Vertex> vertices, int mode) {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    size = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], mode);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoord));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // offsetof returns byte pos in struct

    glBindVertexArray(0);
}

void Mesh::draw() const {
    glBindVertexArray(vao);

    // ENABLE VERTEX ATTRIBUTE ARRAYS
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glDrawArrays(GL_TRIANGLES, 0, size); //seg fault

    // DISABLE VERTEX ATTRIBUTE ARRAYS
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    // UNBIND VERTEX ARRAY
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    if (vbo) glDeleteBuffers(1, &vbo);
    if (vao) glDeleteVertexArrays(1, &vao);
}

