#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <string>

constexpr int DEFAULT_WIDTH = 800;
constexpr int DEFAULT_HEIGHT = 600;

static unsigned windowsOpen = 0;

Window::Window()
    : Window("", DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
}

Window::Window(const std::string &title)
    : Window(title, DEFAULT_WIDTH, DEFAULT_HEIGHT)
{
}

Window::Window(const std::string &title, int width, int height)
{
    // spdlog: Set log level
    spdlog::set_level(spdlog::level::debug);

    spdlog::info("NAME: {}", title);
    // TODO:
    // spdlog::info(
    //     "VERSION: {}.{}.{}", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

    // glfw: initialize and configure OpenGL context if not already configured
    if (windowsOpen == 0) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    // glfw: window creation
    mWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (mWindow == nullptr) {
        // Clean-up before throw exception
        glfwTerminate();
        const std::string &error = "Failed to create GLFW window";
        spdlog::critical(error);
        throw std::runtime_error(error);
    }

    // bind OpenGL context
    makeContextCurrent();

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // Clean-up before throw exception
        glfwDestroyWindow(mWindow);
        glfwTerminate();
        const std::string &error = "Failed to initialize GLAD";
        spdlog::critical(error);
        throw std::runtime_error(error);
    }

    glViewport(0, 0, width, height);
    setResizeCallback([](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    });
}

Window::~Window()
{
    glfwDestroyWindow(mWindow);
    if (windowsOpen == 1)
        glfwTerminate();
}

void Window::makeContextCurrent() const { glfwMakeContextCurrent(mWindow); }

bool Window::shoudClose() const { return glfwWindowShouldClose(mWindow); }

void Window::swapBuffers() const { glfwSwapBuffers(mWindow); }

void Window::pollEvents() { glfwPollEvents(); }

void Window::setResizeCallback(GLFWframebuffersizefun callback) const
{
    glfwSetFramebufferSizeCallback(mWindow, callback);
}

void Window::setKeyboardCallback(GLFWkeyfun callback) const
{
    glfwSetKeyCallback(mWindow, callback);
}
void Window::setCursorCallback(GLFWcursorposfun callback)
{

    glfwSetCursorPosCallback(mWindow, callback);
}

void Window::close() const
{
    glfwSetWindowShouldClose((GLFWwindow *)mWindow, GLFW_TRUE);
}

void Window::setTitle(const char *title) const
{
    glfwSetWindowTitle((GLFWwindow *)mWindow, title);
}

void Window::setSize(int width, int height) const
{
    glfwSetWindowSize((GLFWwindow *)mWindow, width, height);
}

void Window::setVSync(bool on) const { glfwSwapInterval(on); }

void Window::setUserPointer(void *data) const
{
    glfwSetWindowUserPointer(mWindow, data);
}

Window::Size Window::getSize() const
{
    Size size;
    glfwGetWindowSize(mWindow, &size.width, &size.height);
    return size;
}

GLFWwindow *Window::getWindowPtr() const { return mWindow; }
