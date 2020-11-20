//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:50.

#include "Camera.h"
#include <cmath>

Camera::Camera() : position(glm::vec3(0, 0, -5)),
                   directionSide(glm::vec3(0, 0, 1)),
                   rightSide(glm::vec3(-1, 0, 0)),
                   upSide(0, 1, 0) {

}


glm::mat4 Camera::getModelViewMat() {
    return ProjectionMatrix * ViewMatrix;
}

void Camera::updateMatrices() {
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

    ProjectionMatrix = glm::perspective(glm::radians(FOV), aspect, ddNear, ddFar);

    ViewMatrix = glm::lookAt(
            position,
            position + directionSide,
            upSide
    );
}

auto Camera::getDirection() const -> glm::vec2 {
    return glm::vec2(horizontalAngle, verticalAngle);
}

auto Camera::getPosition() const -> glm::vec3 {
    return position;
}
void Camera::changeFOV(float x) {
    this->FOV += x;
}

void Camera::changeAspect(float a) {
    aspect = a;
}

void Camera::forward(float dt) { position += directionSide * dt * speed; }
void Camera::backward(float dt) { position -= directionSide * dt * speed; }
void Camera::left(float dt) { position -= rightSide * dt * speed; }
void Camera::right(float dt) { position += rightSide * dt * speed; }
void Camera::up(float dt) { position += upSide * dt * speed; }
void Camera::down(float dt) { position -= upSide * dt * speed; }

void Camera::setPosition(glm::vec3 pos) { position = pos; }
void Camera::changeDirection(float x, float y, float dt) {
    horizontalAngle += x * dt;
    verticalAngle += y * dt;
}



Camera::~Camera() = default;