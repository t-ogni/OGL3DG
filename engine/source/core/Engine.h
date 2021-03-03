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
#include "../components/camera/Camera.h"

class Engine {
private:
    Game *game = nullptr;

public:
    Window *window = nullptr;
    Renderer *renderer = new Renderer();
    Camera *camera = new Camera();

    explicit Engine(Game *windowParam,
                    Window *pwindow = new Window);

    auto run() -> int;
};

#endif //OGL3DG_ENGINE_H
