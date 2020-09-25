//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:50.

#include "Camera.h"

Camera::Camera() : position(glm::vec3( 0, 0, -5 )) {

}

Camera::~Camera() = default;
glm::mat4 Camera::getMVP() {
    glm::mat4 MVP;
    direction = glm::vec3(
            std::cos(verticalAngle) * std::sin(horizontalAngle),
            std::sin(verticalAngle),
            std::cos(verticalAngle) * std::cos(horizontalAngle)
    );
    rightSide = glm::vec3(
            sin(horizontalAngle - 3.14f/2.0f),
            0,
            cos(horizontalAngle - 3.14f/2.0f)
    );

    up = glm::cross( rightSide, direction );
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FOV), 4.0f / 3.0f, 0.1f, 100.0f);

    glm::mat4 ViewMatrix = glm::lookAt(
            position,
            position+direction,
            up
    );
    glm::mat4 Model = glm::mat4(1.0f);

     MVP = ProjectionMatrix * ViewMatrix * Model;

    return MVP;
}


void Camera::forward(){ position += direction * speed; }
void Camera::backward(){ position -= direction * speed; }
void Camera::left(){ position -= rightSide * speed; }
void Camera::right(){ position += rightSide * speed; }