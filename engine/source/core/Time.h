//
// Created by moonlin on 21.02.2021.
//

#ifndef OGL3DG_TIME_H
#define OGL3DG_TIME_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// singleton Time
class Time {
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
    static Time* instance();
    void update();    //Called at the start of the main loop

    float getCurrentFrame() const { return current_frame; }
    int getFramesPassed() const { return frames_passed; }
    float getLastFrame() const { return last_frame; }
    float getSeconds() const { return seconds; }
    float getDelta() const { return delta; }
    float getTime() const { return time; }
    float getFps() const { return fps; }
};

#define TIME Time::instance()

#endif //OGL3DG_TIME_H
