//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:50.

#ifndef OGL3DG_CAMERA_H
#define OGL3DG_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget;
    glm::vec3 direction;
    glm::vec3 rightSide;
    glm::vec3 up;
    float FOV = 45.0f;
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    float speed = 2.0f;


protected:

public:
    Camera();
    glm::mat4 getMVP();
    void changeFOV(int x);
    void changeDirection(float x, float y);
    void forward();
    void backward();
    void left();
    void right();
    ~Camera();
};


#endif //OGL3DG_CAMERA_H
