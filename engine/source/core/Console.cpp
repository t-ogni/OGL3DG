//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 013 13.12.20 at 17:16.

#include "Console.h"

std::string __getTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [40];                                // строка, в которой будет храниться текущее время
    time ( &rawtime );                               // текущая дата в секундах
    timeinfo = localtime ( &rawtime );
    strftime (buffer,80,"[%X]", timeinfo); // форматируем строку времени
    return buffer;
}

namespace Log {
    EnumLoggingLevel loggingLevel = INFO;
    bool showTime = true;
    void error(const char *text, int errorCode, ...) {
        if(loggingLevel > ERROR) return;

        va_list ptr = nullptr;
        va_start(ptr, errorCode);
        std::string coutOut = generateOut(text, ptr);
        va_end(ptr);

        if(showTime)
            std::cout << __getTime();
        std::cout << "Fatal  "<< errorCode << "): "
                        << '\a' << coutOut << std::endl;
        std::cerr << "(cerr stream) " << coutOut << std::endl;
        exit(errorCode);
    }

    void warning(const char *text, ...) {
        if(loggingLevel > WARNING) return;

        va_list ptr = nullptr;
        va_start(ptr, text);
        std::string coutOut = generateOut(text, ptr);
        va_end(ptr);

        if(showTime)
            std::cout << __getTime();
        std::cout << "Warning: " << '\a'
                  << coutOut << std::endl;
    }

    void info(const char *text, ...) {
        if(loggingLevel > INFO) return;

        va_list ptr = nullptr;
        va_start(ptr, text);
        std::string coutOut = generateOut(text, ptr);
        va_end(ptr);

        if(showTime)
            std::cout << __getTime();
        std::cout << "Info   : " << coutOut << std::endl;
    }

    void debug(const char *text, ...) {
        if(loggingLevel > DEBUG) return;

        va_list ptr = nullptr;
        va_start(ptr, text);
        std::string coutOut = generateOut(text, ptr);
        va_end(ptr);

        if(showTime)
            std::cout << __getTime();
        std::cout << "Debug  : " << coutOut << std::endl;
    }
    void glfwError(int id, const char *description) {
        if(loggingLevel > GLFWERROR) return;
        std::cout << "[" << id << "] GLFW error: " << description << std::endl;
    }
}

std::string generateOut(const char *text, va_list ptr){
    std::stringstream coutOut;
    bool ErrTip = false;
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
                    coutOut << char(va_arg(ptr, int));
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
                    coutOut << "0o" << std::oct << va_arg(ptr, int) << std::dec;
                    break;
                }
                case '%': {
                    coutOut << '%';
                    break;
                }
                default:
                    coutOut << '%' << *(text + 1);
                    ErrTip = true;
            }
            text += 2;
        } else {
            coutOut << *text;
            text++;
        }
    }
    if(ErrTip)
        coutOut << "\n unknown console output type ([%i, %d, %c, %s] only)";

    return coutOut.str();

};

