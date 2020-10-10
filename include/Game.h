//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 030 30.09.20 at 1:46.
#ifndef OGL3DG_GAME_H
#define OGL3DG_GAME_H

#include "Object.h"

class Engine;

enum GameState {
    GAME_ACTIVE,
    GAME_MENU
};

class Game {
protected:
    friend Engine;
    Engine *engine{};
    Object ThisPlayer;

public:
    GameState State = GAME_MENU;
    Game();
    virtual void Init() { };
    void setEngine(Engine *eng);
    void keyPressCallback() { };


    virtual void ProcessInput(float deltatime) { };
    virtual void Update(float deltaTime) { }; // move
    virtual void Render() { };  //draw

    bool keys[1024];
    virtual void keyPressed(int key, int mods) { };
    virtual void keyReleased(int key, int mods) { };

    virtual void cursorPosCallback(double x, double y) { };
    ~Game();
};


#endif //OGL3DG_GAME_H
