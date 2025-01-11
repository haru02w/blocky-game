#pragma once

class TickTime {
public:
    TickTime();
    TickTime &update(float tickRate = 60.0f);
    bool shoudUpdateGame();

private:
    double mDelta;
    double mLast;
    double mLag;
};
