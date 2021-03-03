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
#include "input/Mouse.h"
#include "input/Keyboard.h"

class Window {
protected:
    int w_width {}, w_height {};
    GLFWwindow *window = nullptr;
    const char *w_title = "Window";

    inline static Window* getWinClass(GLFWwindow* window);

    void resize(int width, int height);

public:
    Mouse *mouse;
    Keyboard *keyboard;

    Window() = default;
    explicit Window(const char *title, int width = 1024, int height = 720);

    // functionality
    void init();
    void initCallbacks();
    static void clear();
    void update();
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

private:
    static void resizeCallback(GLFWwindow *windowParam, int width, int height);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouse_position_callback(GLFWwindow *window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    static void mouse_scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

};


#endif //OGL3DG_WINDOW_H
