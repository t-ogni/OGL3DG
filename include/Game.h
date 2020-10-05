//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 030 30.09.20 at 1:46.
// upper class
#ifndef OGL3DG_GAME_H
#define OGL3DG_GAME_H

class Engine;

enum GameState {
    GAME_ACTIVE,
    GAME_MENU
};

class Game {
protected:
    friend Engine;
    Engine *engine;


public:
    GameState State;
    Game();
    virtual void Init() { };
    void setEngine(Engine *eng);
    void keyPressCallback() { };


    virtual void ProcessInput(float deltatime);
    virtual void Update(float deltaTime) { }; // move
    virtual void Render() { };  //draw

    bool keys[1024];
    virtual void keyPressed(int key) { };
    virtual void keyreleased(int key) { };

    virtual void cursorPosCallback(double x, double y) { };
    ~Game();
};


#endif //OGL3DG_GAME_H
