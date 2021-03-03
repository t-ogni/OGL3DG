//
// Created by moonlin on 28.02.2021.
//

#include "Keyboard.h"

Keyboard::Keyboard(GLFWwindow *win) {
    window = win;
    for(auto i : keyboardButtons)
        i = GLFW_RELEASE;
}

char Keyboard::getKeyStatus(int key) {
    return keyboardButtons[key];
}


void Keyboard::key_callback(int key, int scancode, int action, int mods) {
    keyboardButtons[key] = action;
}

void Keyboard::update() {

}
