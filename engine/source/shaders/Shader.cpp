////______  _______ _______ _______ _______ _______
////|     \ |______    |    |______ |_____| |  |  |
////|_____/.______| .  |    |______ |     | |  |  |
//// Copyright (c) 2020 Dark Shield Team. All rights reserved.
//// Created by moonlin on 014 14.09.20 at 21:37.


#include "Shader.h"


Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    Program = loadShaders(vertexPath, fragmentPath);
}

void Shader::bind() const {
    glUseProgram(this->Program);
}

void Shader::unbind() const {
    glUseProgram(0);
}

auto loadCode(const char *path) -> std::string {
    std::ifstream File;
    std::stringstream Stream;
    File.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        File.open(path);
        Stream << File.rdbuf();
        File.close();
    } catch (...) {
        Log::error("File cannot be opened (path: %s)", ERROR::OPEN_FILE, path);
    }
    return Stream.str();
}

auto compileShader(const std::string &s_code, int type) -> GLuint {
    GLuint shader = glCreateShader(type);
    GLint success = 0;
    GLchar infoLog[512];
    const char *code = s_code.c_str();
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        Log::error("Shader cannot be compiled: %s", ERROR::COMPILE_SHADER, infoLog);
    } else {
        Log::info("Shader compiled (type: %i)", type);
    }
    return shader;
}


auto Shader::loadShaders(const char *vertexPath, const char *fragmentPath) -> GLuint {
    // Compile shaders
    GLuint vertex = compileShader(loadCode(vertexPath), GL_VERTEX_SHADER);
    GLuint fragment = compileShader(loadCode(fragmentPath), GL_FRAGMENT_SHADER);

    // Shader Program
    GLint success = 0;
    GLchar infoLog[512];
    GLuint ProgID = glCreateProgram();
    glAttachShader(ProgID, vertex);
    glAttachShader(ProgID, fragment);
    glLinkProgram(ProgID);
    glGetProgramiv(ProgID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ProgID, 512, nullptr, infoLog);
        Log::error(infoLog, ERROR::LINK_PROGRAM_SHADER);
    } else
        Log::info("Shaders linked to Program (ID: %i)", ProgID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return ProgID;
}


void Shader::uniformSet(const char *name, bool value) const {
    glUniform1i(glGetUniformLocation(this->Program, name), int(value));
}

void Shader::uniformSet(const char *name, int value) const {
    glUniform1i(glGetUniformLocation(this->Program, name), value);
}

void Shader::uniformSet(const char *name, float value) const {
    glUniform1f(glGetUniformLocation(this->Program, name), int(value));
}
//
//void Shader::uniformSet(const char *name, glm::vec2 &value) const {
//    glUniform2fv(glGetUniformLocation(this->Program, name), 1, &value[0]);
//}

void Shader::uniformSet(const char *name, glm::vec2 value) const {
    glUniform2fv(glGetUniformLocation(this->Program, name), 1, &value[0]);
}

void Shader::uniformSet(const char *name, float x, float y) const {
    glUniform2f(glGetUniformLocation(this->Program, name), x, y);
}

//
//void Shader::uniformSet(const char *name, glm::vec3 &value) const {
//    glUniform3fv(glGetUniformLocation(this->Program, name), 1, &value[0]);
//}

void Shader::uniformSet(const char *name, glm::vec3 value) const {
    glUniform3fv(glGetUniformLocation(this->Program, name), 1, &value[0]);
}

void Shader::uniformSet(const char *name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(this->Program, name), x, y, z);
}
//
//void Shader::uniformSet(const char *name, glm::vec4 &value) const {
//    glUniform4fv(glGetUniformLocation(this->Program, name), 1, &value[0]);
//}

void Shader::uniformSet(const char *name, glm::vec4 value) const {
    glUniform4fv(glGetUniformLocation(this->Program, name), 1, &value[0]);
}
void Shader::uniformSet(const char *name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(this->Program, name), x, y, z, w);
}

void Shader::uniformSet(const char *name, glm::mat2 &value) const {
    glUniformMatrix2fv(glGetUniformLocation(this->Program, name), 1, GL_FALSE,
                       &value[0][0]); // idk what doing 3rd argument (transpose)
}

void Shader::uniformSet(const char *name, glm::mat3 &value) const {
    glUniformMatrix3fv(glGetUniformLocation(this->Program, name), 1, GL_FALSE, &value[0][0]);
}

void Shader::uniformSet(const char *name, glm::mat4 &value) const {
    glUniformMatrix4fv(glGetUniformLocation(this->Program, name), 1, GL_FALSE, &value[0][0]);
}








