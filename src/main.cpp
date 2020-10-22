#include "Game.h"
#include "Engine.h"

class Striker : public Game
{
private:
    Object cube, car;
    Shader shader;
    bool mouseChanged = false;
    double mouseChangedX = 0, mouseChangedY = 0;

public:
    explicit Striker() : Game() {
        Console::message("Striker game inited");
    };
    void Init() override
    {
        shader("shaders/vertex/basic.vert", "shaders/fragment/basic.frag");
        cube("common/cube.obj");
        car("common/Deer.obj");
    }

    void ProcessInput(float dt) override
    {
        if(keys[GLFW_KEY_W]) this-> engine-> camera->forward(dt);
        if(keys[GLFW_KEY_S]) this-> engine-> camera->backward(dt);
        if(keys[GLFW_KEY_A]) this-> engine-> camera->left(dt);
        if(keys[GLFW_KEY_D]) this-> engine-> camera->right(dt);
        if(keys[GLFW_KEY_SPACE]) this-> engine-> camera-> up(dt);
        if(keys[GLFW_KEY_LEFT_SHIFT]) this-> engine-> camera-> down(dt);

        if(mouseChanged) {
            engine-> camera-> changeDirection(mouseChangedX, mouseChangedY, dt);
            mouseChanged = false;
        }
    }

    void mouseMoved(double x, double y) override
    {
        mouseChanged = true;
        mouseChangedX = (mouseX - x);
        mouseChangedY = (mouseY - y);
    }

    void Render() override
    {
        //cube.draw(shader, engine-> camera-> getMVP());
        car.draw(shader, engine-> camera-> getMVP());
    }

};


auto main() -> int
{
    Striker MainGame;
    Engine MainEng(&MainGame);
    return MainEng.run();
}