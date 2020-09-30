#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Engine.h"

int main(){
    Engine engine;
    Shader shad("shaders\\vertex\\basic.vert", "shaders\\fragment\\basic.frag");
    Object cube("common\\cube.obj");
    engine.run();
}
