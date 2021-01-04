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
#include "components/states/Transform.h"

// todo: make camera as object subclass
class Camera {
private:
    glm::mat4 ProjectionMatrix;
    glm::mat4 ViewMatrix;
    glm::vec3 directionSide, rightSide, upSide;
    float FOV = 45.0f;
    float aspect = 4.0f / 3.0f;
    float ddNear = 0.1f; // dd - drawing distance
    float ddFar = 100.0f;
    float speed = 1.0f;
    float sense = 1.0f;
public:
    Transform *transform = new Transform();
    Camera();

    // sys funcs
    auto getProjViewMat() -> glm::mat4;
    void updateMatrices();

    float getSpeed() const;
    float getFov() const;
    float getSense() const;

    void setSpeed(float speed);
    void setFov(float fov);
    void setSense(float sense);

    // moves
    void forward(float dt);
    void backward(float dt);
    void left(float dt);
    void right(float dt);
    void up(float dt);
    void down(float dt);

    ~Camera();
};


#endif //OGL3DG_CAMERA_H
