//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.12.20 at 5:19.

#include "Transform.h"

Transform::Transform():
        position(glm::vec3(0)),
        rotation(glm::vec3(0, 0, 0)),
        model(glm::mat4(1.0f))
{

}


Transform::Transform(glm::vec3 position, glm::vec3 EulerAxis):
        position(position),
        yaw(EulerAxis.y),
        pitch(EulerAxis.z),
        roll(EulerAxis.x)
{

}


float Transform::getRoll() const {
    return roll;
}

void Transform::setRoll(float roll1) {
    Transform::roll = roll1;
}

float Transform::getPitch() const {
    return pitch;
}

void Transform::setPitch(float pitch1) {
    Transform::pitch = pitch1;
}

float Transform::getYaw() const {
    return yaw;
}

void Transform::setYaw(float yaw1) {
    Transform::yaw = yaw1;
}

glm::vec3 Transform::getDirection() {
    return rotation;
}

void Transform::setPosition(glm::vec3 position1) {
    Transform::position = position1;
}

glm::vec3 Transform::getPosition() const {
    return position * glm::mat3(model);
}

void Transform::setEulerAngles(glm::vec3 axes) {
    roll = axes.x;
    yaw = axes.y;
    pitch = axes.z;
}

glm::vec3 Transform::getEulerAngles() const {
    return glm::vec3(roll, yaw, pitch);
}


glm::mat4 Transform::getModel() {
    return model;
}

void Transform::updateMat() {
    // euler's angles
    model = glm::mat4(1.0f);  // that stuff causes gimbal lock
    model = glm::translate(model, position);
    model = glm::rotate(model, roll, glm::vec3(1.0, 0.0, 0.0));
    model = glm::rotate(model, yaw, glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate(model, pitch, glm::vec3(0.0, 0.0, 1.0));

    rotation = glm::vec3(
            glm::cos(pitch) * glm::cos(yaw),
            glm::sin(pitch),
            glm::cos(pitch) * glm::cos(yaw)
    );
}


Transform::~Transform() = default;

//// Keep It Simple, Stupid - glm have ::translate() and ::rotate()
///*
//      Rx(P)=| 1      0       0 |
//            | 0  cos P  -sin P |
//            | 0  sin P   cos P |
// */
//glm::mat4 Rx = {
//        {1, 0, 0},
//        {0, cos(roll), -sin(roll)},
//        {0, sin(roll),  cos(roll)}
//};
///*
//    Ry(H)=|  cos H  0  sin H |
//          |      0  1      0 |
//          | -sin H  0  cos H |
//*/
//glm::mat3 Ry = {
//        {cos(yaw), 0, sin(yaw)},
//        {0, 1, 0},
//        {-sin(yaw), 0,  cos(yaw)}
//};
//
///*
//    Rz(B)=| cos B  -sin B  0 |
//          | sin B   cos B  0 |
//          |     0       0  1 |
//  */
//
//glm::mat3 Rz = {
//        {cos(pitch), -sin(pitch),0},
//        {sin(pitch), cos(pitch), 0},
//        {0, 0,  1}
//};
///*
//    R = Ry(H)*Rx(P)*Rz(B) =
//         | cos H*cos B+sin H*sin P*sin B   cos B*sin H*sin P-sin B*cos H   cos P*sin H |
//         |                   cos P*sin B                     cos B*cos P        -sin P |
//         | sin B*cos H*sin P-sin H*cos B   sin H*sin B+cos B*cos H*sin P   cos P*cos H |
//*/