//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#include "Engine.h"


Engine::Engine(Game *g, Window *pwindow) :
    game(g),  window(pwindow),
    camera(new Camera()),
    input(new InputHandler()),
    renderer(new Renderer()) {
    this->game->setEngine(this);
    glfwSetErrorCallback(&Log::glfwError);
}

auto Engine::run() -> int {
    if (game == nullptr) // if game not added to engine
        Log::error("game is nullptr. Aborting..");
    else
        Log::info("Engine started successfully");
    window->init();
    input->initCallbacks(window->getWindow());
    game->Init();

    while (!window->isCloseRequested()) {
        auto currentTime = float(glfwGetTime());
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        FPS = 1000 / deltaTime;


        Window::update();
        camera->updateMatrices();

        this->game->ProcessInput(deltaTime);
        this->game->Update(deltaTime);

        input -> update();

        Window::clear();
        this->game->Render();

        renderer->draw(camera);
        window->render();
    }

    game->Destroy();
    return 0;
}


void Engine::attachCamera(Object &obj, glm::vec3 position) {
    // todo persecution of the Object
};
