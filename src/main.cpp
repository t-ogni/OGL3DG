#include <iostream>
#include <foo.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

int main(){
    std::cout << "init" << std::endl;
    foo::bar();
    return 0;
}