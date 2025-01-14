#include "Game.hpp"
#include "TickTime.hpp"
#include "Globals.hpp"
#include "events/KeyEvent.hpp"

Game::Game(const std::string &title)
    : mWindow(Window(title))
    , mTime()
    , mCamera()
    , mRenderer()
{
    globals.eventManager.subscribe<KeyEvent>(
        "KEY_ESCAPE", [this](KeyEvent &&keyEvent) {
            if (keyEvent.action == KeyEvent::PRESSED)
                this->togglePause();
        });
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
    mRenderer.chunkRenderer.draw(mWindow, mCamera);
    mWindow.swapBuffers();
}
void Game::togglePause()
{
    static bool paused = false;
    paused = !paused;
    mWindow.setMouseDisabled(!paused);
    globals.state.paused = paused;
}
