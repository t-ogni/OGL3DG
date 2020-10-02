//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:50.

#include "Camera.h"

#include <cmath>

Camera::Camera() : position(glm::vec3( 0, 0, -5 )) { }
Camera::~Camera() = default;

auto Camera::getMVP() -> glm::mat4 {
    glm::mat4 MVP;
    directionSide = glm::vec3(
            std::cos(verticalAngle) * std::sin(horizontalAngle),
            std::sin(verticalAngle),
            std::cos(verticalAngle) * std::cos(horizontalAngle)
    );

    rightSide = glm::vec3(
            std::sin(horizontalAngle - 3.14f/2.0f),
            0,
            std::cos(horizontalAngle - 3.14f/2.0f)
    );

    upSide = glm::cross( rightSide, directionSide );
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


void Camera::forward(float dt){ position += directionSide * speed; }
void Camera::backward(float dt){ position -= directionSide * speed; }
void Camera::left(float dt){ position -= rightSide * speed; }
void Camera::right(float dt){ position += rightSide * speed; }
void Camera::up(float dt) { position += upSide * speed; }
void Camera::down(float dt) { position += upSide * speed; }
