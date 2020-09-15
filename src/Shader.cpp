//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 014 14.09.20 at 21:37.


#include "Shader.h"


std::string Shader::getSource(const std::string& path){
    std::ifstream sourceFile(path.c_str());
    std::string source;
    if(not sourceFile){
        throw 7;
        //todo: throws and error codes
    }

    while (sourceFile)
    {
        std::string vertexFileShift;
        std::getline(sourceFile, source);
        source.append(vertexFileShift);
    }

    return source;
}

Shader::Shader(const std::string& VertexPath, const std::string& FragmentPath){
    const char *vertexSource = getSource(VertexPath).c_str();
    const char *fragmentSource = getSource(FragmentPath).c_str();
    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[512];
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
    }

    this-> Program = glCreateProgram();

    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);

    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(this->Program, 512, nullptr, infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::useProgram() {
    glUseProgram(this->Program);
}

Shader::~Shader() = default;

