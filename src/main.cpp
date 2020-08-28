#include <iostream>
#include <foo.h>

int main(){
    std::cout << "init" << std::endl;
    foo::bar();
    return 0;
}