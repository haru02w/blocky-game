#include "EventBase.hpp"
struct MouseEvent : EventBase {

    inline MouseEvent(float posX, float posY, float scrWidth, float scrHeight)
        : posX(posX)
        , posY(posY)
        , scrWidth(scrWidth)
        , scrHeight(scrHeight) {};
    float posX, posY;
    float scrWidth, scrHeight;
};
