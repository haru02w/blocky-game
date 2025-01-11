#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Game;
class Input {
public:
    Input(Game &game);
    static void handleKeyInput(
        GLFWwindow *window, int key, int scancode, int action, int mods);
    static void handleCursorPosInput(
        GLFWwindow *window, double xpos, double ypos);
    ~Input();

private:
    Game &mGame;
};
