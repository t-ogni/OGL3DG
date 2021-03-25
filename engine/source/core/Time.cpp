//
// Created by moonlin on 25.03.2021.
//

#include "Time.h"

Time *Time::instance()  {
    static Time instance_ptr;
    return &instance_ptr;
}

void Time::update()
{
    current_frame = (float)glfwGetTime();
    delta = current_frame - last_frame;
    fps = 1 / delta;

    time = (float)glfwGetTime();

    frames_passed++;
    seconds += delta;
    last_frame = current_frame;
}

