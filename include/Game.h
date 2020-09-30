//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 030 30.09.20 at 1:46.
// upper class
#ifndef OGL3DG_GAME_H
#define OGL3DG_GAME_H

#include "Engine.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
protected:
    GLFWwindow *Window;
public:
    GameState State;
    Game();

    void Run();

    void Update(float deltaTime);

    void Render();

    virtual void keyPressed(int key) = 0;
    virtual void cursorPosCallback(double x, double y) = 0;
    virtual void keyreleased(int key) = 0;
    ~Game();
};


#endif //OGL3DG_GAME_H
