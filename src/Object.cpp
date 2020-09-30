//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 019 19.09.20 at 5:59.

#include "Object.h"

Object::Object() {}

Object::Object(const char *path) {
    loadObj(path);
}

std::vector<std::string> splitStr(std::string &line, char separator = ' '){
    std::vector<std::string> mas;
    std::string buffer;      //буфферная строка
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


std::vector<int> splitInt(std::string &line, char separator = ' '){
    std::vector<int> mas;
    std::string buffer;      //буфферная строка
    for(char i : line){
        if (i != separator){
            buffer += i;
        } else {
            if(!buffer.empty()){
                mas.push_back(atoi(buffer.c_str()));
                buffer.clear();
            }
        }
    }
    if(!buffer.empty())
        mas.push_back(atoi(buffer.c_str()));

    return mas;
}

void Object::loadObj(const char *path) {
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    std::ifstream objFile(path);
    if (!objFile)
        Console::error("object cannot be opened ", ERROR::OPEN_FILE);
    else
        Console::message("Object was loaded");

    while (objFile) {
        std::string fileLine;
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
            }
        }
    }

    for(unsigned int vertexIndex : vertexIndices) {
        glm::vec3 vertex = temp_vertices[vertexIndex - 1]; // The OBJ index starts with 1, and c++ starts with 0
        this -> vertices.push_back(vertex);
    }

}


Object::~Object() {}