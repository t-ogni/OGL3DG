//
// Created by moonlin on 28.02.2021.
//

#ifndef OGL3DG_MOUSE_H
#define OGL3DG_MOUSE_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window;

class Mouse {
    friend Window;
private:
    GLFWwindow *window {};
    bool lockStatus = false;
    glm::vec2 position = {0, 0};
    glm::vec2 previousPosition = {-1, -1};
    glm::vec2 lockedPosition = {0, 0};
    glm::vec2 scrollOffset = {0, 0};
    int8_t mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1] {};

    void position_callback(double xpos, double ypos);
    void button_callback(int button, int action, int mods);
    void scroll_callback(double xoffset, double yoffset);

    void update();

public:
    Mouse() = default;
    explicit Mouse(GLFWwindow *window);
    void setPosition(double x, double y);
    void setLockedPosition(double x, double y);
    void setCursorType(int type);
    void setLockStatus(bool lock);
    void toggleLock();

    glm::vec2 getPosition();
    glm::vec2 getLockedPosition();
    glm::vec2 getScrollOffset();
    bool isPressed(int button);
    bool isMoved();
    [[nodiscard]] inline bool isLocked() const { return lockStatus; }
};
#endif //OGL3DG_MOUSE_H
