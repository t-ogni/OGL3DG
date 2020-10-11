//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 030 30.09.20 at 1:46.

#include "Game.h"
#include "Engine.h"

Game::Game() : ThisPlayer(), keys {} {
    for (auto &item : this-> keys)
        item = false;
}

void Game::setEngine(Engine *eng) {
    Console::message("Engine setted at %i (mem)", eng);
    this-> engine = eng;
}

Game::~Game() = default;