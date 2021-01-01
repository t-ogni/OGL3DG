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
    glm::vec3 directionSide;
    glm::vec3 rightSide;
    glm::vec3 upSide;
    glm::mat4 ProjectionMatrix;
    glm::mat4 ViewMatrix;

    float yaw = 0.0f;
    float pitch = 0.0f;
    float scroll = 0.0f;

    float FOV = 45.0f;
    float aspect = 4.0f / 3.0f;
    float ddNear = 0.1f; // dd - drawing distance
    float ddFar = 100.0f;

public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    float speed = 2.0f;

    Camera();

    // get all info
    glm::vec3 getDirection();
    glm::vec3 getPosition();
    glm::vec2 getViewAngles();

    // sys funcs
    auto getProjViewMat() -> glm::mat4;
    void updateMatrices();

    // set core params
    void changeFOV(float x);
    void changeAspect(float a);

    // change positon and view
    void changeDirection(float x, float y, float dt);
    void setPosition(glm::vec3 pos);

    // moves
    // todo: make subclass
    void forward(float dt);
    void backward(float dt);
    void left(float dt);
    void right(float dt);
    void up(float dt);
    void down(float dt);
    void roll(float i, float dt);

    ~Camera();
};


#endif //OGL3DG_CAMERA_H
