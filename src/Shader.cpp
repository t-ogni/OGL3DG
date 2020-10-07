////______  _______ _______ _______ _______ _______
////|     \ |______    |    |______ |_____| |  |  |
////|_____/.______| .  |    |______ |     | |  |  |
//// Copyright (c) 2020 Dark Shield Team. All rights reserved.
//// Created by moonlin on 014 14.09.20 at 21:37.


#include "Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath){
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensures ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }  catch (...)  {
        Console::error("shader cannot be opened", ERROR::OPEN_FILE);
    }

    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();

    // 2. Compile shaders
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER),
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLint success = 0;
    GLchar infoLog[512];


    // Vertex Shader
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        Console::error(infoLog, ERROR::COMPILE_VERTEX);
    } else {
        Console::message("Vertex shader Compiled");
    }


    // Fragment Shader
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        Console::error(infoLog, ERROR::COMPILE_FRAGMENT);
    } else {
        Console::message("Fragment shader Compiled");
    }


    // Shader Program
    this->Program = glCreateProgram();
    glAttachShader(this->Program, vertex);
    glAttachShader(this->Program, fragment);
    glLinkProgram(this->Program);
    glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->Program, 512, nullptr, infoLog);
        Console::error(infoLog, ERROR::LINK_PROGRAM_SHADER);
    } else {
        Console::message("Shaders linked to Program");
    }

    // Delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void Shader::useProgram() const {
    glUseProgram(this->Program);
}



void Shader::uniformSet(const char *name, bool value) const
{
    this-> useProgram();
    glUniform1i(glGetUniformLocation(this->Program, name), int(value));
}

void Shader::uniformSet(const char *name, int value) const
{
    this-> useProgram();
    glUniform1i(glGetUniformLocation(this->Program, name), value);
}

void Shader::uniformSet(const char *name, float value) const
{
    this-> useProgram();
    glUniform1f(glGetUniformLocation(this->Program, name), int(value));
}

void Shader::uniformSet(const char *name, glm::vec2 &value) const
{
    this-> useProgram();
    glUniform2fv(glGetUniformLocation(this->Program, name), 1, &value[0]);
}

void Shader::uniformSet(const char *name, float x, float y) const
{
    this-> useProgram();
    glUniform2f(glGetUniformLocation(this->Program, name), x, y);
}


