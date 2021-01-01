//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.12.20 at 5:19.

#ifndef OGL3DG_TRANSFORM_H
#define OGL3DG_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// that class contains all matrices as needed
// like position, rotation, scale
// (not done but must be)
// todo: matrices

class Transform {
private:
    glm::vec3 position;
    glm::vec3 directionSide;
    glm::vec3 rightSide;
    glm::vec3 upSide;
    glm::mat4 model = glm::mat4(1.0f);

    // x - right, y - up, z - forward;

    // radians
    float roll = 0.0f; // angle between y and z axis ( x )
    float yaw = 0.0f;  // angle between x and z axis ( y )
    float pitch = 0.0f; // angle between x and y axis ( z )

public:
    Transform();
    Transform(glm::vec3 position, glm::vec3 EulerAxis = glm::vec3(0.0f));

    glm::vec3 getPosition() const;

    float getRoll() const;
    float getYaw() const;
    float getPitch() const;

    void setYaw(float yaw);
    void setPitch(float pitch);
    void setRoll(float roll);

    void setPosition(glm::vec3 position);


    glm::vec3 getDirection();
    glm::mat4 getModel();

    void updateMat();




    ~Transform();
};


#endif //OGL3DG_TRANSFORM_H
