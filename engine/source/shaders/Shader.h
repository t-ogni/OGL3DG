//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 014 14.09.20 at 21:37.

#ifndef OGL3DG_SHADER_H
#define OGL3DG_SHADER_H

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include "core/Console.h"

class Shader {
private:
    GLuint Program = 0;

protected:  // i think it`s bad
    static std::string loadCode(const char *path);
    static GLuint compileShader(const std::string &s_code, int type);
    void linkProgram(GLuint vertex, GLuint fragment);
public:
    Shader() = default;
    Shader(const char *vertexPath, const char *fragmentPath);

    void bind() const;
    void unbind() const;

    void loadShaders(const char *vertexPath, const char *fragmentPath);

    void uniformSet(const char *name, bool value) const;
    void uniformSet(const char *name, int value) const;
    void uniformSet(const char *name, float value) const;
//    void uniformSet(const char *name, glm::vec2 &value) const;
    void uniformSet(const char *name, glm::vec2 value) const;
    void uniformSet(const char *name, float x, float y) const;
//    void uniformSet(const char *name, glm::vec3 &value) const;
    void uniformSet(const char *name, glm::vec3 value) const;
    void uniformSet(const char *name, float x, float y, float z) const;
//    void uniformSet(const char *name, glm::vec4 &value) const;
    void uniformSet(const char *name, glm::vec4 value) const;
    void uniformSet(const char *name, float x, float y, float z, float w) const;
    void uniformSet(const char *name, glm::mat2 &value) const;
    void uniformSet(const char *name, glm::mat3 &value) const;
    void uniformSet(const char *name, glm::mat4 &value) const;
};

#endif //OGL3DG_SHADER_H
