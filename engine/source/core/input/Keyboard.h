//
// Created by moonlin on 28.02.2021.
//

#ifndef OGL3DG_KEYBOARD_H
#define OGL3DG_KEYBOARD_H

#define BTN_RELEASE 0
#define BTN_PRESS 1
#define BTN_HOLD 2
#define BTN_REPEAT 3


#include <GLFW/glfw3.h>
class Window;

class Keyboard {
    friend Window;
private:
    GLFWwindow *window{};
    int8_t keyboardButtons[GLFW_KEY_LAST + 1]{};

    void key_callback(int key, int scancode, int action, int mods);

    void update();
public:
    Keyboard() = default;
    explicit Keyboard(GLFWwindow *window);
    char getKeyStatus(int key);

};


#endif //OGL3DG_KEYBOARD_H
