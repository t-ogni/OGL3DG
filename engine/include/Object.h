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
// included from "Shader.h"

#include "Texture.h"
#include "Shader.h"
#include <vector>

class Object {
    GLuint VBO = 0;
    Texture *texture = nullptr;
    Shader *shader = nullptr;


public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;

    GLuint VAO = 0;

    glm::vec3 Position{0.f, 0.f, 0.f},
            Velocity{0.f, 0.f, 0.f},
            Rotation{0.f, 0.f, 0.f};
    float alpha = 1.0f;
    bool Visible = false;

    Object() = default;

    explicit Object(const char *path);

    void loadObj(const char *path);
    void loadMtl(const char *path);

    void setTexture(Texture *texture1);
    void setShader(Shader *shader1);

    void operator()(const char *path);
    void operator()(const char *path, Texture *texture1);
    void operator()(const char *path, Texture *texture1, Shader *shader1);

    auto getVertices() -> std::vector<glm::vec3>;

    void draw(glm::mat4 MVP) const;

    void setupVAO(int mode = GL_STATIC_DRAW);

    ~Object();
};


#endif //OGL3DG_OBJECT_H
