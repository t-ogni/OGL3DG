#include "Game.h"
#include "Object.h"

#include "Engine.h"

class Striker : public Game
{
private:
    Object cube;
public:
    explicit Striker(int a) : Game() {
        Console::message("MainGame inited %i", a);
    };
    void Init() override
    {
        cube.loadObj("common/cube.obj");
    }

    void Render() override
    {

    }

    void keyPressed(int key, int mods, float dt = 1) override
    {
        switch (key) {
            case GLFW_KEY_W: this-> engine-> camera->forward(dt);
            case GLFW_KEY_S: this-> engine-> camera->backward(dt);
            case GLFW_KEY_A: this-> engine-> camera->left(dt);
            case GLFW_KEY_D: this-> engine-> camera->right(dt);
            case GLFW_KEY_Q: this-> engine-> camera->changeDirection(-1, 0);
            case GLFW_KEY_E: this-> engine-> camera->changeDirection(+1, 0);
            default: break;
        }
    }

};


auto main() -> int
{
    Striker MainGame(1);
    Engine MainEng(&MainGame);
    return MainEng.run();
}