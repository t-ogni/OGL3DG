//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#ifndef OGL3DG_ENGINE_H
#define OGL3DG_ENGINE_H

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "Console.h"
// included from "Shader.h"


//#include "Object.h"
//#include "Shader.h"
// included from "Game.h"

#include "Game.h"
#include "Camera.h"
#include "Window.h"
#include "InputHandler.h"

class Engine {
public:
    explicit Engine(Game *windowParam,
                    Window *pwindow = new Window);

    auto run() -> int;

    void attachCamera(Object &obj, glm::vec3 position);

    Camera *camera = nullptr;
    Window *window = nullptr;
    InputHandler *input = nullptr;
private:
    Game *game = nullptr;

    float deltaTime = 0.0;
    float lastTime = 0.0;

};

#endif //OGL3DG_ENGINE_H
