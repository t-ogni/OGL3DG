#include "Game.h"
#include "Engine.h"

class Striker : public Game
{
private:
    Object cube;
    Shader shader;

public:
    explicit Striker() : Game() {
        Console::message("Striker game inited");
    };
    void Init() override
    {
        shader = {"shaders/vertex/basic.vert", "shaders/fragment/basic.frag"};
        cube = { "common/cube.obj" };
    }

    void ProcessInput(float dt) override
    {
        if(keys[GLFW_KEY_W])
            this-> engine-> camera->forward(dt);
        if(keys[GLFW_KEY_S]) this-> engine-> camera->backward(dt);
        if(keys[GLFW_KEY_A]) this-> engine-> camera->left(dt);
        if(keys[GLFW_KEY_D]) this-> engine-> camera->right(dt);
        if(keys[GLFW_KEY_Q]) this-> engine-> camera->changeDirection(-10, 0);
        if(keys[GLFW_KEY_E]) this-> engine-> camera->changeDirection(+10, 0);
        if(keys[GLFW_KEY_CAPS_LOCK]) engine-> camera-> consPos();
    }

    void Render() override
    {

        cube.draw(shader, engine-> camera-> getMVP());

    }

    void keyPressed(int key, int mods) override
    {

    }

};


auto main() -> int
{
    Striker MainGame;
    Engine MainEng(&MainGame);
    return MainEng.run();
}