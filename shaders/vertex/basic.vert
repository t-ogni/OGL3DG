#version 330 core
layout (location = 0) in vec3 position; // Устанавливаем позиция переменной с координатами в 0

uniform mat4 MVP;
uniform vec3 color;

out vec3 ourColor; // translate to fragment shader


void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
    if(color.x == color.y || color.y == color.z){
        ourColor = vec3(position.x+position.y, position.y+position.z, position.z+position.x);
    } else {
        ourColor = color;
    }
    if(ourColor.x + ourColor.y + ourColor.z < 0.01f){
        ourColor = vec3(1.0f, 1.0f, 1.0f);
    }
}