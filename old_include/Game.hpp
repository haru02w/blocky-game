#pragma once

#include "Window.hpp"
#include "Camera.hpp"
#include "Input.hpp"

class Game {
public:
    struct Timing {
        float delta;
        float last;
    };

    Game();
    Game(const std::string &title);
    ~Game();

    void run();

    Window &getWindow();
    Camera &getCamera();
    Timing &getTime();

    static Game *sInstance;

private:
    void setup();

    // Input
    void handleKeyCallback();
    void handleCursorPosCallback();

    Window mWindow;
    Camera mCamera;
    Input mInput;
    Timing mTime;
};
