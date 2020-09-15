#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Errors.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main(){
    if(!glfwInit())
        return ERROR::INIT_GLFW;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(500, 400, "test", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(window == nullptr){
        glfwTerminate();
        return ERROR::INIT_GL;
    }
    std::cout << "init window" << std::endl;

    int gladInitRes = gladLoadGL();
    if (!gladInitRes) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return ERROR::INIT_GLAD;
    }


    Shader shad("shaders\\vertex\\basic.vert", "shaders\\fragment\\basic.frag");
    float vertices[] = {
            // координаты         // цвета
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // нижняя правая вершина
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // нижняя левая вершина
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 0.7f    // верхняя вершина
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    // Координатный атрибут
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    // Цветовой атрибут
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // Обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer() зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после этого мы можем спокойно выполнить отвязку
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Вы можете отменить привязку VАО после этого, чтобы другие вызовы VАО случайно не изменили этот VAO (но подобное довольно редко случается)
    // Модификация других VAO требует вызов glBindVertexArray(), поэтому мы обычно не снимаем привязку VAO (или VBO), когда это не требуется напрямую
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)){
        processInput(window);
        shad.useProgram();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.4f, 0.6f, 0.6f, 1.0f);


        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        // Переходим к рендерингу треугольников
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}