#include "Game.h"
#include "Engine.h"

class Striker : public Game
{
private:
    Object cube{ "common/cube.obj" };
public:
    explicit Striker(int a) : Game() {
        Console::message("MainGame inited %i", a);
    };
    void Init() override
    {

    }

    void ProcessInput(float dt) override{
        if(keys[GLFW_KEY_W]) this-> engine-> camera->forward(dt);
        if(keys[GLFW_KEY_S]) this-> engine-> camera->backward(dt);
        if(keys[GLFW_KEY_A]) this-> engine-> camera->left(dt);
        if(keys[GLFW_KEY_D]) this-> engine-> camera->right(dt);
        if(keys[GLFW_KEY_Q]) this-> engine-> camera->changeDirection(-1, 0);
        if(keys[GLFW_KEY_E]) this-> engine-> camera->changeDirection(+1, 0);
    }

    void Render() override
    {

    }

    void keyPressed(int key, int mods) override
    {

    }

};


auto main() -> int
{
    Striker MainGame(1);
    Engine MainEng(&MainGame);
    return MainEng.run();
}