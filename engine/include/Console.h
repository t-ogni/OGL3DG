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
#include "Errors.h"

namespace Console {
    static void error(const char *text, int errorCode = ERROR::UNKNOWN_ERROR, ...) {
        //Put to error stream and output stream
        va_list ptr = nullptr;
        va_start(ptr, errorCode);
        std::stringstream coutOut;
        std::cout << '\a';
        coutOut << "[" << errorCode << "] Fatal error: ";
        while (*text) {
            if (*text == '%') {
                switch (*(text + 1)) {
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
                    case 'x': {
                        coutOut << "0x" << std::hex << va_arg(ptr, int) << std::dec;
                        break;
                    }
                    case 'o': {
                        coutOut << "0x" << std::oct << va_arg(ptr, int) << std::dec;
                        break;
                    }
                    case '%': {
                        coutOut << '%';
                        break;
                    }
                    default:
                        error("unknown console output type ([%%i, %%d, %%c, %%s] only)");
                }
                text += 2;
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
        while (*text) {
            if (*text == '%') {
                switch (*(text + 1)) {
                    case 'i':
                        std::cout << va_arg(ptr, int);
                        break;
                    case 'd':
                        std::cout << va_arg(ptr, double);
                        break;
                    case 'c':
                        std::cout << (char) va_arg(ptr, int);
                        break;
                    case 's':
                        std::cout << va_arg(ptr, char*);
                        break;
                    case 'x':
                        std::cout << "0x" << std::hex << va_arg(ptr, int) << std::dec;
                        break;
                    case 'o':
                        std::cout << "0x" << std::oct << va_arg(ptr, int) << std::dec;
                        break;
                    case '%':
                        std::cout << '%';
                        break;

                    default:
                        error("unknown console output type ([%%i, %%d, %%c, %%s] only)");
                }
                text += 2;
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
        while (*text) {
            if (*text == '%') {
                switch (*(text + 1)) {
                    case 'i':
                        std::cout << va_arg(ptr, int);
                        break;
                    case 'd':
                        std::cout << va_arg(ptr, double);
                        break;
                    case 'c':
                        std::cout << (char) va_arg(ptr, int);
                        break;
                    case 's':
                        std::cout << va_arg(ptr, char*);
                        break;
                    case 'x':
                        std::cout << "0x" << std::hex << va_arg(ptr, int) << std::dec;
                        break;
                    case 'o':
                        std::cout << "0x" << std::oct << va_arg(ptr, int) << std::dec;
                        break;
                    case '%':
                        std::cout << '%';
                        break;

                    default:
                        error("unknown console output type ([%%i, %%d, %%c, %%s] only)");
                }
                text += 2;
            } else {
                std::cout << *text;
                text++;
            }
        }
        std::cout << std::endl;
        va_end(ptr);
    }

    static void glfwError(int id, const char *description) {
        std::cout << "[" << id << "] GLFW error: " << description << std::endl;
    }

    template<class T>
    static void showMas(T *start, T *end, const char *splitter = " - ") {
        if (start > end) {
            warning("showMas got invalid argument (%x > %x)", start, end);
            return;
        }
        for (auto begin = start; begin != end; ++begin) {
            std::cout << *start << splitter;
            start++;
        }
    }

    template<class T>
    static void print(T &out, const char *end = "\n") {
        std::cout << out << end;
    }
}


#endif //OGL3DG_CONSOLE_H
