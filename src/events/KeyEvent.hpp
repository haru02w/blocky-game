#pragma once
#include "EventBase.hpp"
#include "GLFW/glfw3.h"

struct KeyEvent : public EventBase {
    inline KeyEvent(int action, int mods)
        : action(action)
        , mods(mods)
    {
    }
    virtual ~KeyEvent() = default;

    enum {
        PRESSED = GLFW_PRESS,
        RELEASED = GLFW_RELEASE,
    };

    int action;
    int mods;
};
