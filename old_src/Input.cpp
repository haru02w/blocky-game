#include "Game.hpp"
#include "Input.hpp"
Input::Input(Game &game)
    : mGame(game)
{
    GLFWwindow *window = game.getWindow().getWindowPtr();

    glfwSetKeyCallback(window, Input::handleKeyInput);
    glfwSetCursorPosCallback(window, handleCursorPosInput);
}

Input::~Input() { }

void Input::handleKeyInput(
    GLFWwindow *window, int key, int scancode, int action, int mods)
{

    const float cameraSpeed = 0.5f; // adjust accordingly
    
    Game &game = *Game::sInstance;
    Camera &camera = game.getCamera();
    const Game::Timing &time = game.getTime();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(Camera::FORWARD, time.delta);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(Camera::BACKWARD, time.delta);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.processKeyboard(Camera::UP, time.delta);

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.processKeyboard(Camera::DOWN, time.delta);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(Camera::LEFT, time.delta);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(Camera::RIGHT, time.delta);
}
