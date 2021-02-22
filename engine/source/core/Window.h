//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 025 25.10.20 at 2:36.

#ifndef OGL3DG_WINDOW_H
#define OGL3DG_WINDOW_H

#include "Console.h"
#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "InputHandler.h"

class Window {
private:
    static void resizeCallback(GLFWwindow *windowParam, int width, int height);

protected:
    int w_width {}, w_height {};
    GLFWwindow *window = nullptr;
    const char *w_title = "Window";

    inline static Window* getWinClass(GLFWwindow* window);

    void resize(int width, int height);

public:
    Window() = default;
    explicit Window(const char *title, int width = 1024, int height = 720);

    // functionality
    void init();
    void initCallbacks(InputHandler *handler);
    static void clear();
    static void update();
    void render();
    void dispose();

    // status functions
    bool isActive();
    auto isCloseRequested() -> bool;

    // setters
    void setTitle(const char *title);
    static void setClearColor(float r, float g, float b, float a = 1.0f);

    // getters
    GLFWwindow *getWindow();
    int getWidth() const;
    int getHeight() const;
    float getAspect() const;

    ~Window();
};


#endif //OGL3DG_WINDOW_H
