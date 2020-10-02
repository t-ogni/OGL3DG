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
    friend Engine;
    GLFWwindow *Window;
    Engine *engine;
public:
    GameState State;
    Game();
    virtual void Init() { };

    virtual void Run() { };
    virtual void Update(float deltaTime) { };
    virtual void Render() { };

    virtual void keyPressed(int key) { };
    virtual void keyreleased(int key) { };
    virtual void cursorPosCallback(double x, double y) { };
    ~Game();
};


#endif //OGL3DG_GAME_H
