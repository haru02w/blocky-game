#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <spdlog/spdlog.h>

constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;

class Window {
public:
    // typedefs
    struct Size {
        int width;
        int height;
    };
    // static vars
    static std::unordered_map<int, std::string> keyNames;
    // ctors
    Window(const std::string &title = "", int width = DEFAULT_WIDTH,
        int height = DEFAULT_HEIGHT);
    // dtor
    ~Window();

    // fns
    inline const Window &swapBuffers() const
    {
        glfwSwapBuffers(mWindow);
        return *this;
    }
    inline const Window &setContextCurrent()
    {
        glfwMakeContextCurrent(mWindow);
        return *this;
    }
    inline const Window &pollEvents() const
    {
        glfwPollEvents();
        return *this;
    }
    inline const Window &setResizeCallback(GLFWframebuffersizefun callback)
    {
        glfwSetFramebufferSizeCallback(mWindow, callback);
        return *this;
    }
    inline const Window &setKeyCallback(GLFWkeyfun callback)
    {
        glfwSetKeyCallback(mWindow, callback);
        return *this;
    }
    inline const Window &setCursorCallback(GLFWcursorposfun callback)
    {
        glfwSetCursorPosCallback(mWindow, callback);
        return *this;
    }
    inline const Window &setTitle(const std::string &title)
    {
        glfwSetWindowTitle(mWindow, title.c_str());
        return *this;
    }
    inline const Window &setSize(int width, int height)
    {
        glfwSetWindowSize(mWindow, width, height);
        return *this;
    };
    inline const Window &setVSync(bool on)
    {
        glfwSwapInterval(on);
        return *this;
    }
    inline const Size getSize() const
    {
        Size size;
        glfwGetWindowSize(mWindow, &size.width, &size.height);
        return size;
    }
    inline const Window &setMouseDisabled(bool on)
    {
        if (on)
            glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        else
            glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        return *this;
    }

    inline bool shoudClose() const { return glfwWindowShouldClose(mWindow); }
    inline GLFWwindow *getWindowPtr() const { return mWindow; };

    void setupInputEvents();

    // public members
    // ...
private:
    // members
    GLFWwindow *mWindow;
};
