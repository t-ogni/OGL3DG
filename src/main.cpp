#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>

int main(){
    if(!glfwInit()){
        return 0x0001;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

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

    static const GLfloat g_vertex_buffer_data[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f,
    };
    GLuint vertexbuffer;

// Сначала генерируем OpenGL буфер и сохраняем указатель на него в vertexbuffer
    glGenBuffers(1, &vertexbuffer);
// Биндим буфер
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

// Предоставляем наши вершины в OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    char *vertexShaderSource = "#version 330 core\n"
                               "layout (location = 0) in vec3 aPos;\n"
                               "out vec4 vertexColor;\n"
                               "void main()\n"
                               "{\n"
                               "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                               "   vertexColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
                               "}\0";

    char *fragmentShaderSource = "#version 330 core\n"
                                 "out vec4 FragColor;\n"
                                 "in vec4 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   FragColor = vertexColor;\n"
                                 "}\n\0";

    GLint success;
    GLchar infoLog[512];

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "err: " << infoLog << std::endl;
        glfwTerminate();
        return 0x0004;
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "err: " << infoLog << std::endl;
        glfwTerminate();
        return 0x0005;
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "err: " << infoLog << std::endl;
        glfwTerminate();
        return 0x0006;
    }


    glUseProgram(shaderProgram);
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы)
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Обратите внимание, что данное действие разрешено, вызов glVertexAttribPointer() зарегистрировал VBO как привязанный вершинный буферный объект для вершинного атрибута, так что после этого мы можем спокойно выполнить отвязку
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Вы можете отменить привязку VАО после этого, чтобы другие вызовы VАО случайно не изменили этот VAO (но подобное довольно редко случается)
    // Модификация других VAO требует вызов glBindVertexArray(), поэтому мы обычно не снимаем привязку VAO (или VBO), когда это не требуется напрямую
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // Переходим к рендерингу треугольников
        glBindBuffer(VBO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
