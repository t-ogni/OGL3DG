#include "Game.h"

class Striker : public Game
{

};

int main(){
    Engine engine;
    Shader shad("shaders\\vertex\\basic.vert", "shaders\\fragment\\basic.frag");
    Object cube("common\\cube.obj");
    engine.run();
    return 0;
}
