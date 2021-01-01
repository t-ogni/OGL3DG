#include "engine/source/components/states/Transform.h"
#include "engine/source/core/Engine.h"
#include <iostream>

int main(){
    glfwInit();
    double time = 0.2;
    while(time < 1000000){
        time = glfwGetTime(); // secs.millis
        std::cout << time << '\n';
    }
    Transform trans {{10, 0, 0}};
    glm::vec3 vecr(0);
    for (int i = 0; i < 181; ++i) {
        trans.setPitch(glm::radians(float(i)));
        trans.updateMat();
        glm::vec3 vec = trans.getModel() * glm::vec4(vecr, 1);
        std::cout << i << "deg: \t" << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
    }

    return 0;
}