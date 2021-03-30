//
// Created by moonlin on 11.03.2021.
//

#ifndef OGL3DG_BASELIGHT_H
#define OGL3DG_BASELIGHT_H

#include "components/object/Object.h"

class BaseLight : public Object {
    enum LightType {
        DirectLight,
        PointLight,
        SpotLight
    } type = PointLight;

public:
    explicit BaseLight(const char *label) : Object(label) { };
};


#endif //OGL3DG_BASELIGHT_H
