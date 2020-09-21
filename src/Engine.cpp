//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#include "Engine.h"
#include "Object.h"
#include "Shader.h"
Engine::Engine() : globals(new EngineGlobals()) {

    if(!glfwInit())
        Console::error("GLFW cannot be started", ERROR::INIT_GLFW);
    else
        Console::message("GLFW started");


    window = glfwCreateWindow(this-> globals-> screenWidth,
                              this-> globals-> screenHeight,
                              this-> globals-> windowName,
                              nullptr, nullptr);


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    if(window == nullptr) {
        glfwTerminate();
        Console::error("Window cannot be initialised", ERROR::INIT_WINDOW);
    } else {
            Console::message("Window initialised");
    }


    int gladInitRes = gladLoadGL();
    if (!gladInitRes) {
        glfwDestroyWindow(window);
        glfwTerminate();
        Console::error("GLAD cannot be initialised", ERROR::INIT_GLAD);
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this-> globals-> glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this-> globals-> glMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}

int Engine::run(){
    Shader shad("shaders\\vertex\\basic.vert", "shaders\\fragment\\basic.frag");
    Object cube("common\\cube.obj");
    //glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(glm::vec3), &cube.vertices[0], GL_STATIC_DRAW);
    std::cout << "ok 1\n";
    for(glm::vec3 vert : cube.vertices){
        std::cout << vert.x << " - " << vert.y << " - " << vert.z << "\n";
    }
    std::cout << "ok 2\n";
    while(!glfwWindowShouldClose(window)){
        InputHandler(window);
        drawPicture();
    }

    glfwTerminate();
    return 0;
}

void Engine::resizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Engine::InputHandler(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

void Engine::drawPicture() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

Engine::~Engine() = default;
