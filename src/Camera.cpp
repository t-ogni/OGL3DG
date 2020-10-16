//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:50.

#include "Camera.h"
#include "Console.h"
#include <cmath>

Camera::Camera() : position(glm::vec3( 0, 0, -5 )),
                   directionSide(glm::vec3(0, 0, 1)),
                   rightSide(glm::vec3(-1, 0, 0)),
                   upSide(0, 1, 0)
{

}


auto Camera::getMVP() -> glm::mat4 {
    glm::mat4 MVP;
    directionSide = glm::vec3(
            cos((double) verticalAngle) * sin((double) horizontalAngle),
            sin((double) verticalAngle),
            cos((double) verticalAngle) * cos((double) horizontalAngle)
    );

    rightSide = glm::vec3(
            sin((double) horizontalAngle - 3.14f / 2.0f),
            0,
            cos((double) horizontalAngle - 3.14f / 2.0f)
    );

    upSide = glm::cross(rightSide, directionSide);
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FOV), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 ViewMatrix = glm::lookAt(
            position,
            position + directionSide,
            upSide
    );
    glm::mat4 Model = glm::mat4(1.0f);
    MVP = ProjectionMatrix * ViewMatrix * Model;
    return MVP;
}


void Camera::forward(float dt){ position += directionSide * dt * speed;}
void Camera::backward(float dt){ position -= directionSide * dt * speed; }
void Camera::left(float dt){ position -= rightSide * dt * speed; }
void Camera::right(float dt){ position += rightSide * dt * speed; }
void Camera::up(float dt) { position += upSide * dt * speed; }
void Camera::down(float dt) { position -= upSide * dt * speed; }
void Camera::setPos(glm::vec3 pos) { position = pos; }
void Camera::changeFOV(float x) { this-> FOV += x; }

void Camera::changeDirection(float x, float y, float dt) {
    horizontalAngle += x*dt;
    verticalAngle += y*dt;
}

Camera::~Camera() = default;