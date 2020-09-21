#version 330 core
layout (location = 0) in vec3 position; // Устанавливаем позиция переменной с координатами в 0
layout (location = 1) in vec3 color;    // А позицию переменной с цветом в 1

out vec3 ourColor; // Передаем цвет во фрагментный шейдер

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(position, 1.0);
    ourColor = color;
}