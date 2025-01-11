#include "TickTime.hpp"
#include <GLFW/glfw3.h>

TickTime::TickTime()
    : mDelta(0.0f)
    , mLast(glfwGetTime())
    , mLag(0.0f)
{
}
TickTime &TickTime::update(float tickRate)
{
    double now_ms = glfwGetTime();
    mDelta = (now_ms - mLast);
    mLast = now_ms;
    mLag += mDelta / (1.0f / tickRate);
    return *this;
}

bool TickTime::shoudUpdateGame()
{
    bool should = mLag >= 1.0f;
    if (should)
        mLag--;
    return should;
}
