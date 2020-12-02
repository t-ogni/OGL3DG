//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 030 30.09.20 at 1:46.

//#include "Engine.h"
// included from "InputHandler.h"

#include "Game.h"

Game::Game() {
    title = "new Game";
}

void Game::setEngine(Engine *eng) {
    Log::message("Engine located at 0x%x (mem)", eng);
    this->engine = eng;
}

void Game::ProcessInput(float deltatime) {

}

void Game::Update(float deltaTime) {

}

void Game::Render() {

}

void Game::Destroy() {

}

Game::~Game() {
    Destroy();
}