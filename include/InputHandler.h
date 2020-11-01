//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 025 25.10.20 at 0:52.

#ifndef OGL3DG_INPUTHANDLER_H
#define OGL3DG_INPUTHANDLER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Console.h"

class InputHandler {
public:
    InputHandler() = default;
    void initCallbacks(GLFWwindow *window);

    auto getCursorPosition() -> glm::vec2;
    void setCursorPosition(GLFWwindow *window, glm::vec2 newPosition);

    void setCursorHidden(bool to);

    auto getScrollOffset() -> double;
    void setScrollOffset(float offset);

    auto getLockStatus() -> bool;
    void setLockedCursorPosition(glm::vec2 lockedPosition);
    auto getLockedCursorPosition() -> glm::vec2;
    void setLockStatus(bool to);

    bool isKeyboardPressed(int key);
    bool isMousePressed(int key);

private:
    bool KeyboardKeys[1024]{};
    bool MouseKeys[8]{};
    glm::vec2 cursorPosition = glm::vec2(0.0f, 0.0f);
    glm::vec2 lockedCursorPosition = glm::vec2(0.0f, 0.0f);
    bool isCursorLocked = false;
    double scrollOffset = 0;

    GLFWwindow *window;

    void clear();

    void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    void cursor_pos_callback(GLFWwindow *window, double x, double y);

    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
};


#endif //OGL3DG_INPUTHANDLER_H
