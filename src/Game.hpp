#pragma once
#include "window/Window.hpp"
#include "State.hpp"
#include "TickTime.hpp"
#include "graphics/Camera.hpp"
#include "graphics/renderer/MasterRenderer.hpp"

class Game {
public:
    Game(const std::string &title);
    ~Game();

    bool isRunning() const;
    void update();
    void render() const;

    Window &getWindow();
    TickTime &getTickTime();

private:
    void togglePause();
    // TODO: chainning setting functions
    Window mWindow;
    TickTime mTime;
    Camera mCamera;
    State mState;
    // TODO: chainning setting functions
    MasterRenderer mRenderer;
};
