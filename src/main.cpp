#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Engine.h"

int main(){
    Engine engine;
    float vertices[] = {
            // координаты         // цвета
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // нижняя правая вершина
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // нижняя левая вершина
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 0.7f    // верхняя вершина
    };

    engine.run();
}
