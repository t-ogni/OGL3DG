//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#include "Engine.h"


Engine::Engine(Game *gamePtr, Window *windowPtr) :
    game(gamePtr),
    window(windowPtr) {
    this->game->setEngine(this);
    glfwSetErrorCallback(&Logger::glfwError);
}

auto Engine::run() -> int {
    if (game == nullptr) // if game not added to engine
        Log->error("child class not set. Aborting..");

    window->init();
    game->Init();
    Log->info("Engine started successfully");

    while (!window->isCloseRequested()) {
        TIME->update();

        window-> update();
        camera->updateMatrices(window->getAspect());

        this->game->ProcessInput(TIME->getDelta());
        this->game->Update(TIME->getDelta());

        Window::clear();
        this->game->Render();

        renderer->draw(camera);
        window->render();
    }

    game->Destroy();
    return 0;
}


