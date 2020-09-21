//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 017 17.09.20 at 0:18.

#ifndef OGL3DG_CONSOLE_H
#define OGL3DG_CONSOLE_H

#pragma once

#include <iostream>
#include <string>
#include "Errors.h"

namespace Console {
    template<class Terr>
    inline void error(Terr text, int error = ERROR::UNKNOWN_ERROR)
    {
        //Put to error stream and output stream
        std::cerr << "(" << error << ") Fatal error: " << text << std::endl;
        std::cout << "(" << error << ") Fatal error: " << text << '\a' << std::endl;
        exit(error);
    }

    template<class Twarn>
    inline void warning(Twarn text) {
        std::cout << "Warning: " << text << '\a' << std::endl;
    }

    template<class Tmess>
    inline void message(Tmess text) {
        std::cout << "Info: " << text << std::endl;
    }


}


#endif //OGL3DG_CONSOLE_H
