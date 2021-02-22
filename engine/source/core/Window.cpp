//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 025 25.10.20 at 2:36.

#include "Window.h"

Window::Window(const char *title, int width, int height) {
    w_title = title;
    w_width = width;
    w_height = height;
}

void Window::resizeCallback(GLFWwindow *windowParam, int width, int height) {
    auto *win = getWinClass(windowParam);
    win-> resize(width, height);
}

void Window::resize(int width, int height) {
    glViewport(0, 0, width, height);
    w_width = width;
    w_height = height;
}

void Window::init() {
    if (!glfwInit())
        Log.error("GLFW cannot be started", ERR::INIT_GLFW);
    Log.info("GLFW started");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create window
    window = glfwCreateWindow(this->w_width, this->w_height, this->w_title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        Log.error("Window cannot be initialised", ERR::INIT_WINDOW);
    }
    Log.info("Window initialised");

    // Set Window Position centered relative to the main screen
    GLFWmonitor *glfwMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *glfwVidMode = glfwGetVideoMode(glfwMonitor);
    glfwSetWindowPos(window, (glfwVidMode->width - w_width) / 2, (glfwVidMode->height - w_height) / 2);

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    if (!gladLoadGL()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        Log.error("GLAD cannot be initialised", ERR::INIT_GLAD);
    }
    Log.info("GLAD initialised");

    Log.info("OpenGL Version: %i.%i", GLVersion.major, GLVersion.minor);
    Log.debug("Vendor: %s", glGetString(GL_VENDOR));
    Log.debug("GLSL Version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_DEPTH_TEST);
}


void Window::initCallbacks(InputHandler *handler) {
    glfwSetKeyCallback(window, InputHandler::key_callback);
    glfwSetMouseButtonCallback(window, InputHandler::mouse_button_callback);
    glfwSetCursorPosCallback(window, InputHandler::cursor_pos_callback);
    glfwSetScrollCallback(window, InputHandler::scroll_callback);

    Log.info("Input Callbacks Initialized");
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto Window::isCloseRequested() -> bool {
    return glfwWindowShouldClose(window);
}

// close and destroy window & GLFW
void Window::dispose() {
    glfwDestroyWindow(window);
    glfwTerminate();
    Log.info("Window Terminated");
}

bool Window::isActive() {
    return glfwGetWindowAttrib(window, GLFW_FOCUSED);
}

// setters
void Window::setTitle(const char *title1) {
    w_title = title1;
}

void Window::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

// getters
Window *Window::getWinClass(GLFWwindow *window) {
    return static_cast<Window *>(glfwGetWindowUserPointer(window));
}

GLFWwindow *Window::getWindow() {
    return window;
}

int Window::getWidth() const {
    return w_width;
}

int Window::getHeight() const {
    return w_height;
}

float Window::getAspect() const {
    Log.debug("wh: %i %i", w_width, w_height);
    return (float) w_width / (float) w_height;
}

// destructor
Window::~Window() {
    dispose();
}
