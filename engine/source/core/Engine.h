//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#ifndef OGL3DG_ENGINE_H
#define OGL3DG_ENGINE_H

#include "Game.h"
#include "../components/camera/Camera.h"
#include "Window.h"
#include "InputHandler.h"
#include "Renderer.h"

class Engine {
public:
    int FPS = 0;
    float lastTime = 0.0;
    float deltaTime = 0.0;
    explicit Engine(Game *windowParam,
                    Window *pwindow = new Window);

    auto run() -> int;

    void attachCamera(Object &obj, glm::vec3 position);

    Camera *camera = nullptr;
    Window *window = nullptr;
    InputHandler *input = nullptr;
    Renderer *renderer = nullptr;

private:
    Game *game = nullptr;

};

#endif //OGL3DG_ENGINE_H
