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

    void keyPressed(int key) override
    {

    }

};


int main()
{
    Striker MainGame(1);
    Engine MainEng(&MainGame);
    return MainEng.run();
}