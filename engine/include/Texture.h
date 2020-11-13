//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 007 07.11.20 at 22:59.

#ifndef OGL3DG_TEXTURE_H
#define OGL3DG_TEXTURE_H

#include <SOIL/SOIL.h>
#include <glad/glad.h>

class Texture {
    GLuint textureID = 0;
public:
    void bind() const;
    void unbind() const;

    int getTextureID();

    Texture() = default;
    Texture(const char *path);
    void loadTextures(const char *path);

    ~Texture();
};


#endif //OGL3DG_TEXTURE_H
