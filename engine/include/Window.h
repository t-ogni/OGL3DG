//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 025 25.10.20 at 2:36.

#ifndef OGL3DG_WINDOW_H
#define OGL3DG_WINDOW_H

#include "Console.h"

class Window {
private:
    int w_width = 100, w_height = 100;
    GLFWwindow *window = nullptr;
    const char *w_title = "Window";

public:
    Window(const char *title, int width, int height);

    Window() = default;

    ~Window();

    void init();

    void resizeCallback(GLFWwindow *windowParam, int width, int height);

    auto isCloseRequested() -> bool;

    static void clear();

    static void update();

    void render();

    void dispose();

    GLFWwindow *getWindow();

    int getWidth();

    int getHeight();

    bool isActive();


};


#endif //OGL3DG_WINDOW_H
