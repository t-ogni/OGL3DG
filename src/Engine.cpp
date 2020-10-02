//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#include "Engine.h"


Engine::Engine() : settings(new Settings()) {
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
        Console::message("GL Version is " );
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this-> settings-> glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this-> settings-> glMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}

int Engine::run(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while(!glfwWindowShouldClose(window)){


        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
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

void Engine::InputHandler(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        //cam.forward();
    }
    if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        //cam.backward();
    }
    if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
        //cam.right();
    }
    if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        //cam.left();
    }
}

void Engine::drawPicture() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

Engine::~Engine() = default;


//cos(Xdeg) = Y
//acos(Y) = Xdeg