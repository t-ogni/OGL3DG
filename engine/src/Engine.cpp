//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#include "Engine.h"


Engine::Engine(Game *g, Window *pwindow) : game(g), window(pwindow),
                                           camera(new Camera()), input(new InputHandler()) {
    this->game->setEngine(this);
    glfwSetErrorCallback(&Console::glfwError);
}

auto Engine::run() -> int {
    if (game == nullptr)
        Console::error("game is nullptr. Aborting..");
    else
        Console::message("Engine started successfully");
    window-> init();
    input->initCallbacks(window->getWindow());
    game->Init();

    while (!window->isCloseRequested()) {
        auto currentFrame = float(glfwGetTime());
        this->deltaTime = currentFrame - lastTime;
        this->lastTime = currentFrame;

        Window::update();

        this->game->ProcessInput(deltaTime);
        this->game->Update(deltaTime);
        Window::clear();
        this->game->Render();

        window->render();

    }

    game->Destroy();
    return 0;
}


void Engine::attachCamera(Object &obj, glm::vec3 position) {
    // todo persecution of the Object
};
