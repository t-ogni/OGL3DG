//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 006 06.09.20 at 20:46.

#include "Engine.h"


Engine::Engine() : settings(new Settings()) {
    glfwSetErrorCallback(&Console::glfwError);

    if(!glfwInit())
        Console::error("GLFW cannot be started", ERROR::INIT_GLFW);
    else
        Console::message("GLFW started");


    window = glfwCreateWindow(this-> settings-> screenWidth,
                              this-> settings-> screenHeight,
                              this-> settings-> windowName,
                              nullptr,
                              nullptr);



    if(window == nullptr) {
        glfwTerminate();
        Console::error("Window cannot be initialised", ERROR::INIT_WINDOW);
    } else {
        Console::message("Window initialised");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resizeCallback);


    int gladInitRes = gladLoadGL();
    if (!gladInitRes) {
        glfwDestroyWindow(window);
        glfwTerminate();
        Console::error("GLAD cannot be initialised", ERROR::INIT_GLAD);
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this-> settings-> glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this-> settings-> glMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}

int Engine::run(){
    Shader shad("shaders\\vertex\\basic.vert", "shaders\\fragment\\basic.frag");
    Object cube("common\\cube.obj");
    Camera cam;
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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    while(!glfwWindowShouldClose(window)){



        GLuint MatrixID = glGetUniformLocation(shad.Program, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE,  &cam.getMVP()[0][0]);

        shad.useProgram();
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
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
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
    }
    glfwTerminate();
    return 0;
}

void Engine::resizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    //settings-> screenHeight = height;
    //settings-> screenWidth = width;

}

void Engine::InputHandler(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        //cam.forward();
    }
    if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        //cam.backward();
    }
    if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
        //cam.right();
    }
    if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        //cam.left();
    }
}

void Engine::drawPicture() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

Engine::~Engine() = default;


//cos(Xdeg) = Y
//acos(Y) = Xdeg