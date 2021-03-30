//
// Created by moonlin on 28.03.2021.
//

#ifndef OGL3DG_POINTLIGHT_H
#define OGL3DG_POINTLIGHT_H

#include "BaseLight.h"

class PointLight : public BaseLight {
public:
    explicit PointLight(const char *label) : BaseLight(label) { };
};


#endif //OGL3DG_POINTLIGHT_H
