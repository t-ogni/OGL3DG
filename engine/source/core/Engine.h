//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#ifndef OGL3DG_ENGINE_H
#define OGL3DG_ENGINE_H

#include "Time.h"
#include "Game.h"
#include "Window.h"
#include "Renderer.h"
#include "InputHandler.h"
#include "../components/camera/Camera.h"

class Engine {
private:
    Game *game = nullptr;

public:
    Camera *camera = nullptr;
    Window *window = nullptr;
    InputHandler *input = nullptr;
    Renderer *renderer = nullptr;

    explicit Engine(Game *windowParam,
                    Window *pwindow = new Window);

    auto run() -> int;
};

#endif //OGL3DG_ENGINE_H
