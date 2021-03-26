//
// Created by moonlin on 28.02.2021.
//

#include "Mouse.h"


Mouse::Mouse(GLFWwindow *win) {
    window = win;
    for(auto i : mouseButtons)
        i = GLFW_RELEASE;
}

void Mouse::setPosition(double x, double y) {
    previousPosition = position;
    position = { x, y };
    glfwSetCursorPos(window, x, y);
}

void Mouse::setLockedPosition(double x, double y) {
    lockedPosition = {x, y};
}

void Mouse::setCursorType(int type) {
    glfwSetInputMode(window, GLFW_CURSOR, type);
}

void Mouse::setLockStatus(bool lock) {
     lockStatus = lock;
}

void Mouse::toggleLock() {
    setLockStatus(!lockStatus);
}

glm::vec2 Mouse::getPosition() {
    return position;
}

glm::vec2 Mouse::getLockedPosition() {
    return lockedPosition;
}

glm::vec2 Mouse::getScrollOffset(){
    return scrollOffset;
}

bool Mouse::isPressed(int button){
    return mouseButtons[button];
}

bool Mouse::isMoved() {
    return lockedPosition != position;
}

void Mouse::position_callback(double xpos, double ypos) {
    if (previousPosition.x < 0) // if first movement
        previousPosition = position;

    if(lockStatus)
        setPosition(lockedPosition.x, lockedPosition.y);

    previousPosition = position;
    position = { xpos, ypos };


}

void Mouse::button_callback(int button, int action, int mods) {
    if(mouseButtons[button] == BTN_PRESS && action == BTN_PRESS)
        mouseButtons[button] = BTN_HOLD;
    else
        mouseButtons[button] = action;
}

void Mouse::scroll_callback(double xoffset, double yoffset) {
    scrollOffset.x = xoffset;
    scrollOffset.y = yoffset;
}

void Mouse::update() {
    previousPosition = position;
    if(lockStatus) position = lockedPosition;
}



