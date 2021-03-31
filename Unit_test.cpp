#include "engine/source/components/object/Object.h"
#include "engine/source/core/Engine.h"
#include <iostream>

using namespace std;
class tst : public Game {
    void Init() override {
        auto obj = new Object("k");
        obj-> loadObjFromFile("res/square.obj");
    }
};

int main(){
    (new Engine(new tst()))->run();
    return 0;
}