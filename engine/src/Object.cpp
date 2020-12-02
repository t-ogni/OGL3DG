//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 019 19.09.20 at 5:59.

#include "Object.h"

Object::Object(const char *pathToObj) {
    loadObjFromFile(pathToObj);
}

Object::Object(const char *pathToObj, Material *material1) {
    loadObjFromFile(pathToObj);
    material = material1;
}

Object::Object(const char *pathToObj, Texture *texture) {
    loadObjFromFile(pathToObj);
    material = new Material(texture);

}

Object::Object(const char *pathToObj, const char *pathToTexture) {
    loadObjFromFile(pathToObj);
    material = new Material(new Texture(pathToTexture));
}

void Object::addMesh(std::vector<Vertex> vertices) {
    meshes.push_back(new Mesh(vertices));
}

void Object::setShader(Shader *shader1) {
    shader = shader1;
}

void Object::setMaterial(Material *material1) {
    material = material1;
}

void Object::loadObjFromFile(const char *path) {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;

    std::vector<Vertex> vertices;
    std::ifstream objFile(path);

    if (!objFile) {
        Console::warning("Object file in %s cannot be opened ", path);
        return;
    } else
        Console::message("Object file in %s was loaded", path);

    std::string fileLine;
    while (objFile) {
        getline(objFile, fileLine);
        std::istringstream lineStream(fileLine);
        std::string oper;
        lineStream >> oper;
        if (oper == "v") {
            glm::vec3 vertex;
            lineStream >> vertex.x >> vertex.y >> vertex.z;

            positions.push_back(vertex);

        } else if (oper == "vt") {
            glm::vec2 uv;
            lineStream >> uv.x >> uv.y;

            texCoords.push_back(uv);

        } else if (oper == "vn") {
            glm::vec3 normal;
            lineStream >> normal.x >> normal.y >> normal.z;

            normals.push_back(normal);

        } else if (oper == "f") {
            std::string points[3];
            lineStream >> points[0] >> points[1] >> points[2];

            for (auto &point : points) {
                std::stringstream pStream (point);
                std::string v, vt, vn;
                Vertex vertex;
                std::getline(pStream, v, '/');
                std::getline(pStream, vt, '/');
                std::getline(pStream, vn, '/');
                vertex.position = (v == "") ? glm::vec3(0.f) : positions[stoi(v) - 1];
                vertex.textureCoord = (vt == "") ? glm::vec2(0.f) : texCoords[stoi(vt) - 1];
                vertex.normal = (vn == "") ? glm::vec3(0.f) : normals[stoi(vn) - 1];
                vertices.push_back(vertex);
            } //todo: split by meshes
        }  // todo: matreial (.mtl)
    }
    addMesh(vertices);
    return;
}

Object::~Object() = default;