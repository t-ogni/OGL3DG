//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 017 17.09.20 at 0:18.
// todo: must be factored in future for output in hand-made in-app console
// todo: create logging level (debug, info, warning, error)

#ifndef OGL3DG_CONSOLE_H
#define OGL3DG_CONSOLE_H

#include <iostream>
#include <cstdarg>
#include <sstream>
#include <ctime>
#include "Errors.h"

std::string generateOut(const char *text, va_list ptr);

namespace Log {
    enum EnumLoggingLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        GLFWERROR,
        NOTHING
    };
    extern EnumLoggingLevel loggingLevel;
    extern bool showTime;
    void debug(const char *text, ...);
    void info(const char *text, ...);
    void warning(const char *text, ...);
    void error(const char *text, int errorCode = ERROR::UNKNOWN_ERROR, ...);

    void glfwError(int id, const char *description);
}

#endif //OGL3DG_CONSOLE_H
