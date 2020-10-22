//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 019 19.09.20 at 5:59.

#include "Object.h"

Object::Object() {  }

Object::Object(const char *path) : Visible(false){
    loadObj(path);
}

auto splitStr(std::string &line, char separator = ' ') -> std::vector<std::string>{
    std::vector<std::string> mas;
    std::string buffer;
    for(char i : line){
        if (i != separator){
            buffer += i;
        } else {
            if(!buffer.empty()){
                mas.push_back(buffer);
                buffer.clear();
            }
        }
    }
    if(!buffer.empty())
        mas.push_back(buffer);

    return mas;
}

auto splitInt(std::string &line, char separator = ' ') -> std::vector<int>{
    std::vector<int> mas;
    std::string buffer;
    for(char i : line){
        if (i != separator){
            buffer += i;
        } else {
            if(!buffer.empty()){
                mas.push_back(int(strtol(buffer.c_str(), nullptr, 10)));
                buffer.clear();
            }
        }
    }
    if(!buffer.empty())
        mas.push_back(int(strtol(buffer.c_str(), nullptr, 10)));

    return mas;
}

void Object::loadObj(const char *path) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    bool existsNormals = false;

    std::ifstream objFile(path);
    if (!objFile) {
        Console::warning("Object in %s cannot be opened ", path);
        return;
    } else
        Console::message("Object in %s was loaded", path);
    std::string fileLine;
    while (objFile) {
        getline(objFile, fileLine);

        if (fileLine.rfind("v ", 0) == 0) {
            fileLine.erase(fileLine.begin(), fileLine.begin()+2);
            std::istringstream lineStream(fileLine);
            glm::vec3 vertex;
            if (!(lineStream >> vertex.x >> vertex.y >> vertex.z))
                Console::warning("stringStream cannot read float values in obj file (v ...)");

            temp_vertices.push_back(vertex);
        } else if (fileLine.rfind("vt ", 0) == 0) {
            fileLine.erase(fileLine.begin(), fileLine.begin()+3);
            std::istringstream lineStream(fileLine);
            glm::vec2 uv;
            lineStream >> uv.x;
            lineStream >> uv.y;
            temp_uvs.push_back(uv);
        } else if (fileLine.rfind("vn ", 0) == 0) {
            existsNormals = true;
            fileLine.erase(fileLine.begin(), fileLine.begin()+3);
            std::istringstream lineStream(fileLine);
            glm::vec3 normal;
            lineStream >> normal.x;
            lineStream >> normal.y;
            lineStream >> normal.z;
            temp_normals.push_back(normal);
        } else if (fileLine.rfind("f ", 0) == 0) {
            fileLine.erase(fileLine.begin(), fileLine.begin()+2);
            std::vector<std::string> points = splitStr(fileLine, ' ');

            int iterator = 0;
            for (auto it = points.begin(); it<points.end(); it++, iterator++) {
                std::vector<int> point = splitInt(*it, '/');
                int &vertex = point[0];
                int &uv = point[1];
                int &normal = point[2];
                vertexIndices.push_back(vertex);
                uvIndices.push_back(uv);
                normalIndices.push_back(normal);
                // todo EBO indices
            }
        } else {
            Console::message("unknown arg %s", fileLine.c_str());
        }

    }

    for(unsigned int vertexIndex : vertexIndices) {
        glm::vec3 vertex = temp_vertices[vertexIndex-1]; // The OBJ index starts with 1, and c++ starts with 0
        this -> vertices.push_back(vertex);
    }

    for(unsigned int uvIndex : uvIndices) {
        glm::vec2 uv = temp_uvs[uvIndex-1];
        this -> uvs.push_back(uv);
    }
    if (existsNormals){
        for(unsigned int normalIndex : normalIndices) {
            glm::vec3 normal = temp_normals[normalIndex-1];
            this -> normals.push_back(normal);
        }
    }

    Visible = true;
    setupVAO();

    Console::message("object created");
}

auto Object::getVertices() -> std::vector<glm::vec3> {
    std::vector<glm::vec3> vert_modifed;
    for (auto &vertex : vertices) {
        vert_modifed.push_back(vertex * Position);
    }
    return vert_modifed;
}

void Object::draw(Shader shader, glm::mat4 MVP) const {
    shader.useProgram();
    shader.uniformSet("MVP", MVP);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}


void Object::setupVAO(int mode)
{
    Console::message("started setting UP VAO");
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], mode);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*) nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

}

void Object::operator()(const char *path) {
    loadObj(path);
}

Object::~Object() = default;
