//
// Created by moonlin on 21.02.2021.
//

#ifndef OGL3DG_TIME_H
#define OGL3DG_TIME_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

static class Time {
private:
    //Values to return
    int frames_passed = 0;
    float seconds = 0.0f;
    float delta = 0.0f;
    float time = 0.0f;
    float fps = 0.0f;

    //Calculating delta time
    float last_frame = 0.0f;
    float current_frame = 0.0f;

public:
    //Called at the start of the main loop
    void update()
    {
        //Find delta time
        current_frame = (float)glfwGetTime();
        delta = current_frame - last_frame;

        //Update time
        time = (float)glfwGetTime();

        //Find FPS
        fps = 1 / delta;

        //Done
        frames_passed++;
        seconds += delta;
        last_frame = current_frame;
    }

    //Since all values should be read only they need getters
    float getCurrentFrame() { return current_frame; }
    int getFramesPassed() { return frames_passed; }
    float getLastFrame() { return last_frame; }
    float getSeconds() { return seconds; }
    float getDelta() { return delta; }
    float getTime() { return time; }
    float getFps() { return fps; }

} Time;

#endif //OGL3DG_TIME_H
