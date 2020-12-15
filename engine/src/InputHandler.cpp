//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 025 25.10.20 at 0:52.

#include "InputHandler.h"


void InputHandler::initCallbacks(GLFWwindow *windowParam) {
    window = windowParam;
    clear();
    glfwSetWindowUserPointer(window, this);
    // idk how that anonymous func works, but it works :)
    auto key_callback_lambda = [](GLFWwindow *windowParam, int key, int scancode, int action, int mode) {
        InputHandler *ih = static_cast<InputHandler *>(glfwGetWindowUserPointer(windowParam));
        ih->key_callback(windowParam, key, scancode, action, mode);
    };

    auto cursor_pos_callback_lambda = [](GLFWwindow *windowParam, double xpos, double ypos) {
        InputHandler *ih = static_cast<InputHandler *>(glfwGetWindowUserPointer(windowParam));
        ih->cursor_pos_callback(windowParam, xpos, ypos);
    };

    auto mouse_button_callback_lambda = [](GLFWwindow *windowParam, int button, int action, int mods) {
        InputHandler *ih = static_cast<InputHandler *>(glfwGetWindowUserPointer(windowParam));
        ih->mouse_button_callback(windowParam, button, action, mods);
    };

    auto scroll_callback_lambda = [](GLFWwindow *windowParam, double xoffset, double yoffset) {
        InputHandler *ih = static_cast<InputHandler *>(glfwGetWindowUserPointer(windowParam));
        ih->scroll_callback(windowParam, xoffset, yoffset);
    };

    glfwSetKeyCallback(window, key_callback_lambda);
    glfwSetCursorPosCallback(window, cursor_pos_callback_lambda);
    glfwSetMouseButtonCallback(window, mouse_button_callback_lambda);
    glfwSetScrollCallback(window, scroll_callback_lambda);
    Log::info("Input Callbacks Initialized");
}


void InputHandler::clear() {
    setScrollOffset(0);
    for (auto &item : KeyboardKeys)
        item = false;

    for (auto &item : MouseKeys)
        item = false;
}

void InputHandler::key_callback(GLFWwindow *windowParam, int key, int scancode, int action, int mods) {
    KeyboardKeys[key] = action;
}

void InputHandler::mouse_button_callback(GLFWwindow *windowParam, int button, int action, int mods) {
    MouseKeys[button] = action;
}

void InputHandler::cursor_pos_callback(GLFWwindow *windowParam, double xpos, double ypos) {
    glm::vec2 position = glm::vec2((float) xpos, (float) ypos);
    cursorPosition = position;
    cursorMoved = true;

    if (isCursorLocked)
        setCursorPosition(window, lockedCursorPosition);
}

void InputHandler::scroll_callback(GLFWwindow *windowParam, double xoffset, double yoffset) {
    scrollOffset += yoffset;
}

auto InputHandler::getCursorPosition() -> glm::vec2 {
    return cursorPosition;
}

void InputHandler::setCursorPosition(GLFWwindow *windowParam, glm::vec2 newPosition) {
    glfwSetCursorPos(window, newPosition.x, newPosition.y);
}

void InputHandler::setCursorHidden(bool to) {
    glfwSetInputMode(window, GLFW_CURSOR, to ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
}

auto InputHandler::getScrollOffset() const -> double {
    return scrollOffset;
}

void InputHandler::setScrollOffset(float offset) {
    scrollOffset = offset;
}

bool InputHandler::getLockStatus() const {
    return isCursorLocked;
}

void InputHandler::setLockedCursorPosition(glm::vec2 lockedPosition) {
    lockedCursorPosition = lockedPosition;
}

auto InputHandler::getLockedCursorPosition() -> glm::vec2 {
    return lockedCursorPosition;
}

void InputHandler::setLockStatus(bool to) {
    isCursorLocked = to;
    if(to)
        setCursorPosition(window, lockedCursorPosition);

}

char InputHandler::getKeyStatus(int key) {
    return KeyboardKeys[key];
}

char InputHandler::getMouseStatus(int key) {
    return MouseKeys[key];
}

void InputHandler::update() {
    cursorMoved = false;
}

bool InputHandler::isCursorMoved() const {
    return cursorMoved;
};
