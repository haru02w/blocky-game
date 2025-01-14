#pragma once

#include <GLFW/glfw3.h>
class TickTime {
public:
    TickTime();
    TickTime &update(float tickRate = 60.0f);
    bool shoudUpdateGame();
    inline double now() { return glfwGetTime(); }

private:
    double mDelta;
    double mLast;
    double mLag;
};
