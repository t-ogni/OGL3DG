#version 330 core
layout (location = 0) in vec3 position; // Устанавливаем позиция переменной с координатами в 0

uniform mat4 MVP;
uniform vec3 color;

out vec3 ourColor; // translate to fragment shader


void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
    if(color.x == color.y || color.y == color.z){
        ourColor = vec3(1-gl_Position.x/2, 1-gl_Position.y, 1-gl_Position.z);
    } else {
        ourColor = color;
    }
}