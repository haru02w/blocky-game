#pragma once
#include "TickTime.hpp"
#include "graphics/Camera.hpp"
#include "window/Window.hpp"
#include "graphics/SimpleRenderer.hpp"

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
    // TODO: chainning setting functions
    Window mWindow;
    TickTime mTime;
    Camera mCamera;
    // TODO: chainning setting functions
    SimpleRenderer mRenderer;
};
