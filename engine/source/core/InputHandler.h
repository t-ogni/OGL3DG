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


class Mouse {
private:
    static bool m_cursorLocked;
public:
    static double lastX;
    static double lastY;
    static bool   leftButtonDown;
    static bool   middleButtonDown;
    static bool   rightMouseDown;

    static bool isPressed(int button);
    static void setPosition(double x, double y);
    static void centre();
    static void lock();
    static void toggleLock();
    static void unlock();
    static inline bool isLocked() { return m_cursorLocked; }
};

class Keyboard {
private:
public:
    static bool isPressed(int key);
};

class InputHandler {
public:
    InputHandler() = default;

    auto getCursorPosition() -> glm::vec2;
    auto getScrollOffset() const -> double;
    char getKeyStatus(int key);
    char getMouseStatus(int key);
    auto getLockedCursorPosition() -> glm::vec2;

    bool getLockStatus() const;
    bool isCursorMoved() const;

    void setCursorPosition(GLFWwindow *window, glm::vec2 newPosition);
    void setCursorHidden(bool to);
    void setScrollOffset(float offset);
    void setLockedCursorPosition(glm::vec2 lockedPosition);
    void setLockStatus(bool to);

    void update();

protected:
    virtual void keyCallback(int key, int scancode, int action, int mods) {};
    virtual void mouseCallback(int button, int action, int mods) {};
    virtual void cursorPosCallback(double x, double y) {};
    virtual void scrollCallback(double xoffset, double yoffset) {};
private:
    int8_t KeyboardKeys[GLFW_KEY_LAST + 1] {};
    int8_t MouseKeys[GLFW_MOUSE_BUTTON_LAST + 1] {};
    glm::vec2 cursorPosition = glm::vec2(0.0f, 0.0f);
    glm::vec2 lockedCursorPosition = glm::vec2(0.0f, 0.0f);
    bool isCursorLocked = false;
    bool cursorMoved = true;
    double scrollOffset = 0;

    void clear();

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
    static void cursor_pos_callback(GLFWwindow *window, double x, double y);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
};

void input_callback_key(GLFWwindow* window, int key, int scancode, int action, int mods);
//void input_callback_char(GLFWwindow* winodw, unsigned int codepoint);
void input_callback_cursorPosition(GLFWwindow* window, double xpos, double ypos);
//void input_callback_cursorEnter(GLFWwindow* window, int entered);
void input_callback_mouseButton(GLFWwindow* window, int button, int action, int mods);
void input_callback_scroll(GLFWwindow* window, double xoffset, double yoffset);

#endif //OGL3DG_INPUTHANDLER_H
