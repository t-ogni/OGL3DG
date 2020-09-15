//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 014 14.09.20 at 21:37.

#ifndef OGL3DG_SHADER_H
#define OGL3DG_SHADER_H

#include <string>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader {
private:
    std::string getSource(const std::string& path);

public:
    GLuint Program;
    Shader() = default;
    Shader(const std::string& VertexPath, const std::string& FragmentPath);
    void useProgram();

    ~Shader();
};


#endif //OGL3DG_SHADER_H
