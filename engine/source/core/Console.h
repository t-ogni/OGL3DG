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



static class Log {
public:
    enum EnumLoggingLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        NOTHING
    } loggingLevel = DEBUG;
    bool showTime = true;
    void debug(const char *text, ...) const;
    void info(const char *text, ...) const;
    void warning(const char *text, ...) const;
    void error(const char *text, int errorCode = ERR::UNKNOWN_ERROR, ...) const;

    static void glfwError(int id, const char *description);

} Log;

#endif //OGL3DG_CONSOLE_H
