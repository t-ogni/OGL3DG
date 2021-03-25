//______  _______ _______ _______ _______ _______
//|     \ |______    |    |______ |_____| |  |  |
//|_____/.______| .  |    |______ |     | |  |  |
// Copyright (c) 2020 Dark Shield Team. All rights reserved.
// Created by moonlin on 013 13.12.20 at 17:16.

#include "Console.h"

std::string getTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer [40];                                // строка, в которой будет храниться текущее время
    time ( &rawtime );                               // текущая дата в секундах
    timeinfo = localtime ( &rawtime );
    strftime (buffer,80,"[%X]", timeinfo); // форматируем строку времени
    return buffer;
}

void Logger::error(const char *text, int errorCode, ...) const {
    if(loggingLevel > ERROR) return;

    va_list ptr;
    va_start(ptr, errorCode);
    std::string coutOut = generateOut(text, ptr);
    va_end(ptr);

    if(showTime)
        std::cout << getTime();
    std::cout << "Fatal  (" << errorCode << "): "
                   << coutOut << '\a' << std::endl;
    std::cerr << "(cerr stream) " << coutOut << std::endl;
    exit(errorCode);
}

void Logger::warning(const char *text, ...) const {
    if(loggingLevel > WARNING) return;

    va_list ptr;
    va_start(ptr, text);
    std::string coutOut = generateOut(text, ptr);
    va_end(ptr);

    if(showTime)
        std::cout << getTime();
    std::cout << "Warning: " << coutOut << '\a' << std::endl;
}

void Logger::info(const char *text, ...) const {
    if(loggingLevel > INFO) return;

    va_list ptr;
    va_start(ptr, text);
    std::string coutOut = generateOut(text, ptr);
    va_end(ptr);

    if(showTime)
        std::cout << getTime();
    std::cout << "Info   : " << coutOut << std::endl;
}

void Logger::debug(const char *text, ...) const {
    if(loggingLevel > DEBUG) return;

    va_list ptr;
    va_start(ptr, text);
    std::string coutOut = generateOut(text, ptr);
    va_end(ptr);

    if(showTime)
        std::cout << getTime();
    std::cout << "Debug  : " << coutOut << std::endl;
}



void Logger::glfwError(int id, const char *description) {
    std::cout << "[" << id << "] GLFW error: " << description << std::endl;
}

Logger *Logger::instance() {
    static Logger instance_ptr;
    return &instance_ptr;
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
                case 'f':
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
        coutOut << "\n unknown console output type ([%i, %fd, %c, %s, %xo, %%] only)";

    return coutOut.str();

}
