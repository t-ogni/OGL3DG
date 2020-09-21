//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#include "Engine.h"
#include "Object.h"
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

Engine::Engine() : globals(new EngineGlobals()) {

    if(!glfwInit())
        Console::error("GLFW cannot be started", ERROR::INIT_GLFW);
    else
        Console::message("GLFW started");


    window = glfwCreateWindow(this-> globals-> screenWidth,
                              this-> globals-> screenHeight,
                              this-> globals-> windowName,
                              nullptr,
                              nullptr);


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resizeCallback);

    if(window == nullptr) {
        glfwTerminate();
        Console::error("Window cannot be initialised", ERROR::INIT_WINDOW);
    } else {
            Console::message("Window initialised");
    }


    int gladInitRes = gladLoadGL();
    if (!gladInitRes) {
        glfwDestroyWindow(window);
        glfwTerminate();
        Console::error("GLAD cannot be initialised", ERROR::INIT_GLAD);
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this-> globals-> glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this-> globals-> glMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}

int Engine::run(){
    Shader shad("shaders\\vertex\\basic.vert", "shaders\\fragment\\basic.frag");
    Object cube("common\\cube.obj");

    glm::vec3 CubeColors[cube.vertices.size()];
    for (unsigned int i = 0; i < cube.vertices.size(); ++i) {
        CubeColors[i] = glm::vec3(rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f);
        std::cout << i << " is " << CubeColors[i].x << " " << CubeColors[i].y << " " << CubeColors[i].z << "\n";
    }
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(glm::vec3), &cube.vertices[0], GL_STATIC_DRAW);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeColors), &CubeColors[0], GL_STATIC_DRAW);

    glm::vec3 position = glm::vec3( 0, 0, 5 );

    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    float initialFoV = 45.0f;

    float speed = 3.0f; // 3 units per second
    float mouseSpeed = 0.005f;
    float deltaTime = 0.2f;
    while(!glfwWindowShouldClose(window)){
        double lastTime = glfwGetTime();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        glfwSetCursorPos(window, globals-> screenWidth/2,  globals-> screenHeight/2);
// Вычисляем углы
        horizontalAngle += mouseSpeed * deltaTime * float(globals-> screenWidth/2 - xpos );
        verticalAngle   += mouseSpeed * deltaTime * float(globals-> screenHeight/2 - ypos );
        glm::vec3 direction(
                cos(verticalAngle) * sin(horizontalAngle),
                sin(verticalAngle),
                cos(verticalAngle) * cos(horizontalAngle)
        );
        glm::vec3 right = glm::vec3(
                sin(horizontalAngle - 3.14f/2.0f),
                0,
                cos(horizontalAngle - 3.14f/2.0f)
        );
        // Вектор, указывающий направление вверх относительно камеры
        glm::vec3 up = glm::cross( right, direction );

// Движение вперед
        if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
            position += direction * deltaTime * speed;
        }
// Движение назад
        if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
            position -= direction * deltaTime * speed;
        }
// Стрэйф вправо
        if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
            position += right * deltaTime * speed;
        }
// Стрэйф влево
        if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
            position -= right * deltaTime * speed;
        }
        int mwheel = 0;
        if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS){
            mwheel += 1;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS){
            mwheel -= 1;
        }
        initialFoV = initialFoV - 5 * mwheel;

        glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 100.0f);
// Матрица камеры
        glm::mat4 ViewMatrix       = glm::lookAt(
                position,           // Позиция камеры
                position+direction, // Направление камеры
                up                  // Вектор "Вверх" камеры
        );
        glm::mat4 Model = glm::mat4(1.0f);  // Индивидуально для каждой модели

// Итоговая матрица ModelViewProjection, которая является результатом перемножения наших трех матриц
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * Model; // Помните, что умножение матрицы производиться в обратном порядке

        GLuint MatrixID = glGetUniformLocation(shad.Program, "MVP");

// Передать наши трансформации в текущий шейдер
// Это делается в основном цикле, поскольку каждая модель будет иметь другую MVP-матрицу (как минимум часть M)
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        shad.useProgram();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.2f, 0.15f, 1.0f);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
                3,                  // Размер
                GL_FLOAT,           // Тип
                GL_FALSE,           // Указывает, что значения не нормализованы
                0,                  // Шаг
                (void*)0            // Смещение массива в буфере
        );
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
                1,                                // Атрибут. Здесь необязательно указывать 1, но главное, чтобы это значение совпадало с layout в шейдере..
                3,                                // Размер
                GL_FLOAT,                         // Тип
                GL_FALSE,                         // Нормализован?
                0,                                // Шаг
                (void*)0                          // Смещение
        );
        glDrawArrays(GL_TRIANGLES, 0, cube.vertices.size() * 3); // Начиная с вершины 0, всего 3 вершины -> один треугольник

        glDisableVertexAttribArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        InputHandler(window);
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);
    }
    glfwTerminate();
    return 0;
}

void Engine::resizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void Engine::InputHandler(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

void Engine::drawPicture() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

Engine::~Engine() = default;
