//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 019 19.09.20 at 5:07.

#ifndef OGL3DG_SETTINGS_H
#define OGL3DG_SETTINGS_H


class Settings {
public:
    short Mouse_sensitivity;
    bool fullscreen; // todo
    bool dev_log;

    Settings(); // todo read from file

    ~Settings();
};


#endif //OGL3DG_SETTINGS_H
