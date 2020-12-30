//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 025 25.10.20 at 2:36.

#include "Window.h"


void Window::resizeCallback(GLFWwindow *windowParam, int width, int height) {
    glViewport(0, 0, width, height);
    w_width = width;
    w_height = height;
}

void Window::init() {
    if (!glfwInit())
        Log::error("GLFW cannot be started", ERROR::INIT_GLFW);
    else
        Log::info("GLFW started");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(this->w_width,
                              this->w_height,
                              this->w_title,
                              nullptr,
                              nullptr);

    if (window == nullptr) {
        glfwTerminate();
        Log::error("Window cannot be initialised", ERROR::INIT_WINDOW);
    } else
        Log::info("Window initialised");

    // Set Window Position centered relative to the main screen
    GLFWmonitor *glfwMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *glfwVidMode = glfwGetVideoMode(glfwMonitor);
    glfwSetWindowPos(window, (glfwVidMode->width - w_width) / 2, (glfwVidMode->height - w_height) / 2);

    auto resizeCallback_lambda = [](GLFWwindow *windowParam, int width, int height) {
        auto *w = static_cast<Window *>(glfwGetWindowUserPointer(windowParam));
        w->resizeCallback(windowParam, width, height);
    };

    glfwSetFramebufferSizeCallback(window, resizeCallback_lambda);

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(this->window, this);

    if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        Log::error("GLAD cannot be initialised", ERROR::INIT_GLAD);
    } else
        Log::info("GLAD initialised");

    Log::info("OpenGL Version is %i.%i", GLVersion.major, GLVersion.minor);

    glEnable(GL_DEPTH_TEST);
}


// UPDATE WINDOW
void Window::update() {
    glfwPollEvents();
}

// SWAP BUFFERS
void Window::render() {
    glfwSwapBuffers(window);
}

// CLEAR SCREEN
void Window::clear() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// DESTROY WINDOW & TERMINATE GLFW
void Window::dispose() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

// RETURN WINDOW WIDTH
int Window::getWidth() {
    return w_width;
}

// RETURN WINDOW HEIGHT
int Window::getHeight() {
    return w_height;
}

// RETURN GLFW WINDOW
GLFWwindow *Window::getWindow() {
    return window;
}

auto Window::isCloseRequested() -> bool {
    return glfwWindowShouldClose(window);
}

Window::Window(const char *title, int width, int height) {
    w_title = title;
    w_width = width;
    w_height = height;
}

Window::~Window() {
    dispose();
}

bool Window::isActive() {
    return glfwGetWindowAttrib(window, GLFW_FOCUSED);
}

