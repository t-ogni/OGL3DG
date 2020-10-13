//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#include "Engine.h"


Engine::Engine(Game *g) : settings(new Settings()), //todo settings
                            camera(new Camera()),
                            game(g)
{

    Console::message("game at %i (mem)", game);
    this-> game-> setEngine(this);

    glfwSetErrorCallback(&Console::glfwError);
    if(!glfwInit())
        Console::error("GLFW cannot be started", ERROR::INIT_GLFW);
    else
        Console::message("GLFW started");


    window = glfwCreateWindow(this-> settings-> screenWidth,
                              this-> settings-> screenHeight,
                              this-> settings-> windowName,
                              nullptr,
                              nullptr);



    if(window == nullptr) {
        glfwTerminate();
        Console::error("Window cannot be initialised", ERROR::INIT_WINDOW);
    } else {
        Console::message("Window initialised");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(this->window, this);

    auto resizeCallback_lambda = [](GLFWwindow* windowParam, int width, int height) {
        auto *e = static_cast<Engine*>(glfwGetWindowUserPointer(windowParam));
        e->resizeCallback(windowParam, width, height);
    };

    glfwSetFramebufferSizeCallback(window, resizeCallback_lambda);

    auto InputHandler_lambda = [](GLFWwindow* windowParam, int key, int scancode, int action, int mode) {
        auto *e = static_cast<Engine*>(glfwGetWindowUserPointer(windowParam));
        e->InputHandler(windowParam, key, scancode, action, mode);
    };
    glfwSetKeyCallback(window, InputHandler_lambda);

    int gladInitRes = gladLoadGL();
    if (!gladInitRes) {
        glfwDestroyWindow(window);
        glfwTerminate();
        Console::error("GLAD cannot be initialised", ERROR::INIT_GLAD);
    }

    if(GLVersion.major >= 3)
        Console::message("OpenGL Version is %i.%i", GLVersion.major, GLVersion.minor);
    else
        Console::error("OpenGL version is under 3.0 (%i.%i)", ERROR::INIT_GL, GLVersion.major, GLVersion.minor);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this-> settings-> glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this-> settings-> glMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

auto Engine::run() -> int
{
    if(game == nullptr)
        Console::error("game is nullptr");
    else
        Console::message("Engine running");

    this-> game-> Init();

    while(!glfwWindowShouldClose(window)){
        auto currentFrame = float(glfwGetTime());
        this->deltaTime = currentFrame - lastTime;
        this->lastTime = currentFrame;

        glfwPollEvents();

        this-> game-> ProcessInput(deltaTime);
        this-> game-> Update(deltaTime);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

        this-> game-> Render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void Engine::resizeCallback(GLFWwindow* windowParam, int width, int height){
    glViewport(0, 0, width, height);
    settings-> screenHeight = height;
    settings-> screenWidth = width;

}

void Engine::InputHandler(GLFWwindow* windowParam, int key, int scancode, int action, int mods)
{
    switch (action) {
        case GLFW_PRESS:
            this-> game-> keyPressed(key, mods);
            game-> keys[key] = true;
            break;
        case GLFW_RELEASE:
            this-> game-> keyReleased(key, mods);
            game-> keys[key] = false;
            break;
        default: break;
    }
}

Engine::~Engine() {
    delete settings;
    delete camera;
};

