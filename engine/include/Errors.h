//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 014 14.09.20 at 21:44.

#ifndef OGL3DG_ERRORS_H
#define OGL3DG_ERRORS_H

namespace ERROR {
    enum ERRORS {
        UNKNOWN_ERROR = -1,
        INIT_GLFW = 1,
        INIT_GL,
        INIT_GLAD,
        INIT_WINDOW,

        OPEN_FILE,
        COMPILE_SHADER,
        LINK_PROGRAM_SHADER,

    };
}


#endif //OGL3DG_ERRORS_H
