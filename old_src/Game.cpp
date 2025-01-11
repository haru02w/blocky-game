// #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <filesystem>
#include "Game.hpp"
#include "Camera.hpp"
#include "Input.hpp"
#include "ShaderProgram.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>
/////////////////////
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
/////////////////////

namespace fs = std::filesystem;

fs::path SHADER_PATH = "res/shaders";
fs::path TEX_PATH = "res/texture";

// static vars
Game *Game::sInstance = nullptr;

// class methods
Game::Game()
    : mWindow(Window())
    , mCamera(Camera(glm::vec3(0.0f, 0.0f, 3.0f)))
    , mTime({ 0.0f, 0.0f })
    , mInput(Input(*this))
{
    if (sInstance != nullptr)
        throw std::runtime_error("There should be only ONE class \"Game\"");
    sInstance = this;
}
Game::Game(const std::string &title)
    : mWindow(Window(title))
    , mCamera(Camera(glm::vec3(0.0f, 0.0f, 3.0f)))
    , mTime({ 0.0f, 0.0f })
    , mInput(Input(*this))
{
    if (sInstance != nullptr)
        throw std::runtime_error("There should be only ONE class \"Game\"");
    sInstance = this;
}

Game::~Game() { }

void Game::run()
{
    mWindow.makeContextCurrent();

    // void processInput(GLFWwindow * window)

    ShaderProgram shader(
        SHADER_PATH / "vertex.glsl", SHADER_PATH / "fragment.glsl");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first Triangle
        1, 2, 3 // second Triangle
    };

    // Setup OpenGL rendering
    Texture tex(TEX_PATH / "texture.jpg", true, [](Texture *tex) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    });
    VertexBuffer vertexBuffer;
    VertexArray vertexArray;
    IndexBuffer indexBuffer;

    vertexArray.bind();

    vertexBuffer.bind();
    vertexBuffer.push(vertices, sizeof(vertices));

    indexBuffer.bind();
    indexBuffer.push(indices, sizeof(indices));

    vertexArray.push(0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    vertexArray.push(1, 3, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
    vertexArray.push(2, 2, GL_FLOAT, 8 * sizeof(float), 6 * sizeof(float));

    vertexBuffer.unbind();
    vertexArray.unbind();
    indexBuffer.unbind();

    // enable z-buffer
    glEnable(GL_DEPTH_TEST);
    // Enable wireframe for debug purposes
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!mWindow.shoudClose()) {
        // Timing
        float currentFrame = static_cast<float>(glfwGetTime());
        mTime.delta = currentFrame - mTime.last;
        mTime.last = currentFrame;

        shader.bind();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tex.bind();

        // create transformations
        auto [scrWidth, scrHeight] = mWindow.getSize();

        // NOTE: Projection
        //
        // pass projection matrix to shader (note that in this case it could
        // change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(mCamera.mZoom),
            (float)scrWidth / (float)scrHeight, 0.1f, 100.0f);
        glUniformMatrix4fv(shader.getUniformId("projection"), 1, GL_FALSE,
            glm::value_ptr(projection));

        // NOTE: View
        glm::mat4 view = mCamera.getViewMatrix();
        glUniformMatrix4fv(
            shader.getUniformId("view"), 1, GL_FALSE, glm::value_ptr(view));

        // NOTE: Model

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix
                                           // to identity matrix first
        float angle = 0.0f;
        model = glm::rotate(
            model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        glUniformMatrix4fv(
            shader.getUniformId("model"), 1, GL_FALSE, glm::value_ptr(model));

        // render objects
        vertexArray.bind();

        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        mWindow.swapBuffers();
        Window::pollEvents();
    }
}

Window &Game::getWindow() { return mWindow; }
Camera &Game::getCamera() { return mCamera; }
Game::Timing &Game::getTime() { return mTime; }

