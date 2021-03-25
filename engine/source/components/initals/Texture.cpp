//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 007 07.11.20 at 22:59.

#include "Texture.h"
#include <glad/glad.h>

Texture::Texture(const char *path) {
    loadTextures(path);
}

void Texture::loadTextures(const char *path) {
    int width = 0, height = 0;
    unsigned char* image = SOIL_load_image(path, &width, &height, nullptr, SOIL_LOAD_RGB);
    if(image == nullptr) {
        Log->warning("Texture [%s] not loaded", path);
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
//    glCreateTextures(GL_TEXTURE_2D, 1, &textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    Log->debug("Texture loaded successfully");
}

void Texture::bind() const {
    //glActiveTexture(GL_TEXTURE0 + textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::getTextureID() const {
    return textureID;
}

Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

