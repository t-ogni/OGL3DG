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

class Transform {
private:
    glm::vec3 position {0.0f};
    glm::vec3 rotation{0.0f};    // x - right, y - up, z - forward;
    glm::vec3 scale {1.0f};
    glm::mat4 model = glm::mat4(1.0f);

    // grads
    float roll = 0.0f; // angle between y and z axis ( x )
    float yaw = 0.0f;  // angle between x and z axis ( y )
    float pitch = 0.0f; // angle between x and y axis ( z )

public:
    Transform();
    explicit Transform(glm::vec3 position, glm::vec3 EulerAxis = glm::vec3(0.0f));

    glm::vec3 getPosition() const;
    glm::vec3 getDirection();
    glm::vec3 getScale();
    glm::mat4 getModel();

    float getRoll() const;
    float getYaw() const;
    float getPitch() const;
    glm::vec3 getEulerAngles() const;


    void setYaw(float yaw);
    void setPitch(float pitch);
    void setRoll(float roll);
    void setScale(float scalar);
    void setScale(glm::vec3 xyz);
    void setEulerAngles(glm::vec3 axes); // { x, y, z } as { roll, yaw, pitch }
    void setPosition(glm::vec3 position);

    void updateMat();

    ~Transform();

};


#endif //OGL3DG_TRANSFORM_H
