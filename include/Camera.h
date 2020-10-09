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
    glm::vec3 directionSide;
    glm::vec3 rightSide;
    glm::vec3 upSide;
    float FOV = 45.0f;
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;
    float speed = 2.0f;


protected:

public:
    Camera();
    auto getMVP() -> glm::mat4;
    void changeFOV(float x);
    void changeDirection(float x, float y);
    void forward(float dt);
    void backward(float dt);
    void left(float dt);
    void right(float dt);
    void up(float dt);
    void down(float dt);
    void setPos(glm::vec3 pos);
    ~Camera();
};


#endif //OGL3DG_CAMERA_H
