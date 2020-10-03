#include "Game.h"
#include "Object.h"
class Striker : public Game
{
private:
    Object cube;
public:
    void Init() override
    {
        cube("")
    }

};


int main()
{
    Striker striker;
    striker.Init();
    return 0;
}