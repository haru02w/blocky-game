#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <spdlog/spdlog.h>

class Window {
private:
    struct Size {
        int width;
        int height;
    };

public:
    Window();
    Window(const std::string &title);
    Window(const std::string &title, int width, int height);
    Window(Window &&) = delete;
    Window(const Window &) = delete;
    Window &operator=(Window &&) = delete;
    Window &operator=(const Window &) = delete;
    ~Window();

    void makeContextCurrent() const;
    bool shoudClose() const;
    void swapBuffers() const;
    void close() const;

    // setters
    void setResizeCallback(GLFWframebuffersizefun callback) const;
    void setKeyboardCallback(GLFWkeyfun callback) const;
    void setCursorCallback(GLFWcursorposfun callback);
    void setUserPointer(void *data) const;
    void setTitle(const char *title) const;
    void setSize(int width, int height) const;
    void setVSync(bool on) const;

    // getters
    Size getSize() const;
    static void pollEvents();
    GLFWwindow *getWindowPtr() const;

private:
    GLFWwindow *mWindow;
};
