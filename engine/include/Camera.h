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
    float horizontalAngle = 0.0f;
    float verticalAngle = 0.0f;

    float FOV = 45.0f;
    float aspect = 4.0f / 3.0f;
    float ddNear = 0.1f; // dd - drawing distance
    float ddFar = 100.0f;


protected:

public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    float speed = 2.0f;

    Camera();

    auto getMVP() -> glm::mat4;

    void changeFOV(float x);

    void changeDirection(float x, float y, float dt);

    void setPosition(glm::vec3 pos);

    glm::vec2 getDirection(); // horizontal and vertical angles
    glm::vec3 getPosition();

    void forward(float dt);

    void backward(float dt);

    void left(float dt);

    void right(float dt);

    void up(float dt);

    void down(float dt);


    ~Camera();
};


#endif //OGL3DG_CAMERA_H
