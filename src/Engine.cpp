//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#include "Engine.h"


Engine::Engine(Game *g) : settings(new Settings()),
                    camera(new Camera()), game(g){
    RESOLUTION_HEIGHT = settings-> screenHeight;
    RESOLUTION_WIDTH = settings-> screenWidth;
    Console::message("game at %i (mem)", game);
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
    glfwSetFramebufferSizeCallback(window, resizeCallback);


    int gladInitRes = gladLoadGL();
    if (!gladInitRes) {
        glfwDestroyWindow(window);
        glfwTerminate();
        Console::error("GLAD cannot be initialised", ERROR::INIT_GLAD);
    }

    if(GLVersion.major >= 3) {
        Console::message("GL Version is %i.%i", GLVersion.major, GLVersion.minor);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this-> settings-> glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this-> settings-> glMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}

int Engine::run(){
    if(game == nullptr)
        Console::error("game is nullptr");
    else
        Console::message("Engine running");


    while(!glfwWindowShouldClose(window)){
        double currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - lastTime;
        this->lastTime = currentFrame;


        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1f, 0.2f, 0.15f, 1.0f);
        glfwSwapBuffers(window);
        glfwPollEvents();
        InputHandler(window);
    }
    glfwTerminate();
    return 0;
}

void Engine::resizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    //settings-> screenHeight = height;
    //settings-> screenWidth = width;

}

void Engine::InputHandler(GLFWwindow *window) { /* todo */ }

void Engine::drawPicture() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

Engine::~Engine() = default;


//cos(Xdeg) = Y
//arccos(Y) = Xdeg