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

void Object::addMesh(Mesh *mesh) {
    meshes.push_back(mesh);
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

    auto usingMtl = new MaterialStuct();

    if (!objFile) {
        Log.warning("Object file in %s cannot be opened", path);
        return;
    } else
        Log.info("Object file in %s was loaded successfully", path);

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
                std::stringstream pStream(point);
                std::string v, vt, vn;
                Vertex vertex;
                std::getline(pStream, v, '/');
                std::getline(pStream, vt, '/');
                std::getline(pStream, vn, '/');
                vertex.position = (v.empty()) ? glm::vec3(0.f) : positions[stoi(v) - 1];
                vertex.textureCoord = (vt.empty()) ? glm::vec2(0.f) : texCoords[stoi(vt) - 1];
                vertex.normal = (vn.empty()) ? glm::vec3(0.f) : normals[stoi(vn) - 1];
                vertices.push_back(vertex);
            } //todo: split by meshes
        } else if (oper == "s") {
            auto tmpMesh = new Mesh(vertices);
            tmpMesh->setMaterial(usingMtl);
            meshes.push_back(tmpMesh);
            vertices.clear();
        } else if (oper == "usemtl") {
            std::string title;
            lineStream >> title;

            usingMtl = material->getMaterial(title);

        } else if (oper == "mtllib") {
            std::string pathToMtl, pathObj = path;

            // use current path for load mtl
            for (auto itChar = pathObj.end() - 1; itChar != pathObj.begin() - 1; --itChar)
                if (*itChar == '/' or *itChar == '\\') {
                    pathObj.erase(itChar + 1, pathObj.end());
                    break;
                }
            lineStream >> pathToMtl;
            pathToMtl.insert(0, pathObj);
            Log.debug("looking for mtl file in %s", pathToMtl.c_str());
            material->loadMtl(pathToMtl.c_str());
        }
    }

    if(meshes.empty())
        meshes.push_back(new Mesh(vertices));

}

Object::~Object() = default;


/*
  # Список вершин, с координатами (x,y,z[,w]), w является не обязательным и по умолчанию 1.0.
  v 0.123 0.234 0.345 1.0
  ...
  # Текстурные координаты (u,v[,w]), w является не обязательным и по умолчанию 0.
  # Текстурная координата по y может быть указана как 1 - v, и при этом по x = u
  vt 0.500 -1.352 [0.234]
  ...
  # Нормали (x,y,z); нормали могут быть не нормированными.
  vn 0.707 0.000 0.707
  ...
  # Параметры вершин в пространстве (u [,v] [,w]); свободная форма геометрического состояния (см. ниже)
  vp 0.310000 3.210000 2.100000
  ...
  # Определения поверхности (сторон)
  f 1 2 3
  f 3/1 4/2 5/3
  f 6/4/1 3/5/3 7/6/5
  f 6//1 3//3 7//5
  ...
  # Группа
  g Group1
  s set1
*/
