//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 017 17.09.20 at 0:18.

#ifndef OGL3DG_CONSOLE_H
#define OGL3DG_CONSOLE_H

#include <iostream>
#include <cstdarg>
#include <sstream>
#include "Errors.h"

namespace Console {
    static void error(const char *text, int errorCode = ERROR::UNKNOWN_ERROR, ...)
    {
        //Put to error stream and output stream
        va_list ptr = nullptr;
        va_start(ptr, errorCode);
        std::stringstream coutOut;
        coutOut << "[" << errorCode << "] Fatal error: " << '\a';
        while (*text){
            if(*text == '%'){
                switch(*(text+1)){
                    case 'i': {
                        coutOut << va_arg(ptr, int);
                        break;
                    }
                    case 'd': {
                        coutOut << va_arg(ptr, double);
                        break;
                    }
                    case 'c': {
                        coutOut << va_arg(ptr, int);
                        break;
                    }
                    case 's': {
                        coutOut << va_arg(ptr, char *);
                        break;
                    }
                    case '%': {
                        coutOut << '%';
                        break;
                    }
                    default:
                        error("unknown console output type ([%%i, %%d, %%c, %%s] only)");
                }
                text+=2;
            } else {
                coutOut << *text;
                text++;
            }
        }
        std::cout << coutOut.str() << std::endl;
        std::cerr << "(cerr stream) " << coutOut.str() << std::endl;
        va_end(ptr);
        exit(errorCode);
    }

    static void warning(const char *text, ...) {
        va_list ptr = nullptr;
        va_start(ptr, text);
        std::cout << "Warning: " << '\a';
        while (*text){
            if(*text == '%'){
                switch(*(text+1)){
                    case 'i':
                        std::cout << va_arg(ptr, int);
                        break;
                    case 'd':
                        std::cout << va_arg(ptr, double);
                        break;
                    case 'c':
                        std::cout << (char)va_arg(ptr, int);
                        break;
                    case 's':
                        std::cout << va_arg(ptr, char*);
                        break;
                    case '%':
                        std::cout << '%';
                        break;

                    default:
                        error("unknown console output type ([%%i, %%d, %%c, %%s] only)");
                }
                text+=2;
            } else {
                std::cout << *text;
                text++;
            }
        }
        std::cout << std::endl;
        va_end(ptr);
    }


    static void message(const char *text, ...) {
        va_list ptr = nullptr;
        va_start(ptr, text);
        std::cout << "Info: ";
        while (*text){
            if(*text == '%'){
                switch(*(text+1)){
                    case 'i':
                        std::cout << va_arg(ptr, int);
                        break;
                    case 'd':
                        std::cout << va_arg(ptr, double);
                        break;
                    case 'c':
                        std::cout << (char)va_arg(ptr, int);
                        break;
                    case 's':
                        std::cout << va_arg(ptr, char*);
                        break;
                    case '%':
                        std::cout << '%';
                        break;

                    default:
                        error("unknown console output type ([%%i, %%d, %%c, %%s] only)");
                }
                text+=2;
            } else {
                std::cout << *text;
                text++;
            }
        }
        std::cout << std::endl;
        va_end(ptr);
    }

    static void glfwError(int id, const char* description)
    {
        std::cout << "[" << id << "] GLFW error: " << description << std::endl;
    }

}


#endif //OGL3DG_CONSOLE_H
