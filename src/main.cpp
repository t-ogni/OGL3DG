#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

int main(){
    if(!glfwInit()){
        return 0x0001;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(500, 400, "test", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if(window == nullptr){
        glfwTerminate();
        return 0x0002;
    }
    std::cout << "init window" << std::endl;

    int gladInitRes = gladLoadGL();
    if (!gladInitRes) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0x0003;
    }


    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    // Массив из 3 векторов которые будут представлять 3 вершины
    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };
    GLuint vertexbuffer;

// Сначала генерируем OpenGL буфер и сохраняем указатель на него в vertexbuffer
    glGenBuffers(1, &vertexbuffer);
// Биндим буфер
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

// Предоставляем наши вершины в OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,                  // Атрибут 0. Сакрального смысла в нуле нет, но число должно совпадать с числом в шейдере
                3,                  // количество
                GL_FLOAT,           // тип
                GL_FALSE,           // нормализировано ли?
                0,                  // шаг
                (void*)nullptr      // смещение в буфере
        );

// Рисуем треугольник !
        glDrawArrays(GL_TRIANGLES, 0, 3); //Начиная с вершины 0 и рисуем 3 штуки. Всего => 1 треугольник
        glDisableVertexAttribArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
