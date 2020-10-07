//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 014 14.09.20 at 21:37.

#ifndef OGL3DG_SHADER_H
#define OGL3DG_SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Console.h"

class Shader
{
public:
    GLuint Program;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void useProgram() const;

    //todo uniforms
    void uniformSet(const char *name, bool value) const;
    void uniformSet(const char *name, int value) const;
    void uniformSet(const char *name, float value) const;
    void uniformSet(const char *name, glm::vec2 &value) const;
    void uniformSet(const char *name, float x, float y) const;
};

#endif //OGL3DG_SHADER_H
