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
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    GLuint Program;
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    void useProgram();
};

#endif //OGL3DG_SHADER_H
