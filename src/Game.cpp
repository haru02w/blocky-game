#include "Game.hpp"
#include "TickTime.hpp"
#include "Globals.hpp"

Game::Game(const std::string &title)
    : mWindow(Window(title))
    , mTime()
    , mCamera()
    , mRenderer(mCamera)
{
}

Game::~Game() { }

// getters
Window &Game::getWindow() { return mWindow; }
TickTime &Game::getTickTime() { return mTime; }

void Game::update()
{
    mWindow.pollEvents();

    mCamera.update();
}

bool Game::isRunning() const { return !mWindow.shoudClose(); }
void Game::render() const
{
    auto [scrWidth, scrHeight] = mWindow.getSize();
    mRenderer.draw(scrWidth, scrHeight);
    mWindow.swapBuffers();
}
