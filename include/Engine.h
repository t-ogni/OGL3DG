//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#ifndef OGL3DG_ENGINE_H
#define OGL3DG_ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Console.h"
#include "Settings.h"
#include "Object.h"
#include "Shader.h"
#include "Camera.h"

class Engine {
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    Settings *settings;
    Camera *camera;

public:
    GLFWwindow *window;
    Engine();
    int run();
    static void resizeCallback(GLFWwindow* window, int width, int height);
    void InputHandler(GLFWwindow* window);
    void drawPicture();
    ~Engine();
};


#endif //OGL3DG_ENGINE_H
