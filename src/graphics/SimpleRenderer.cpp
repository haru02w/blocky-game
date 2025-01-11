#include "SimpleRenderer.hpp"
#include "Camera.hpp"
#include "gl/ShaderProgram.hpp"
#include "gl/Texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fs = std::filesystem;

fs::path SHADER_PATH = "res/shaders";
fs::path TEX_PATH = "res/texture";

SimpleRenderer::SimpleRenderer(Camera &camera)
    : mShader(SHADER_PATH / "vertex.glsl", SHADER_PATH / "fragment.glsl")
    , mVertices({
          // positions          // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
      })
    , mIndices({
          // // note that we start from 0!
          // 0, 1, 3, // first triangle
          // 1, 2, 3 // second triangle
      })
    , mTexture(TEX_PATH / "texture.jpg", true,
          [](Texture *tex) {
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          })
    , mVertexArray()
    , mVertexBuffer()
    , mIndexBuffer()
    , mCamera(camera)
{

    mVertexArray.bind();

    mVertexBuffer.bind();
    mVertexBuffer.push(
        mVertices.data(), mVertices.size() * sizeof(mVertices[0]));

    mIndexBuffer.bind();
    mIndexBuffer.push(mIndices.data(), mIndices.size() * sizeof(mIndices[0]));

    mVertexArray.push(0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    mVertexArray.push(1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

    mVertexBuffer.unbind();
    mVertexArray.unbind();
    mIndexBuffer.unbind();

    // enable z-buffer
    glEnable(GL_DEPTH_TEST);
    // Enable wireframe for debug purposes
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

SimpleRenderer::~SimpleRenderer() { }
void SimpleRenderer::draw(int scrWidth, int scrHeight) const
{
    mShader.bind();
    glClearColor(
        0.2666666667f, 0.5568627451f, 0.8941176471, 1.0f); // dark sky-blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mTexture.bind();

    glm::mat4 projection = mCamera.getProjectionMatrix(scrWidth, scrHeight);
    glUniformMatrix4fv(mShader.getUniformId("projection"), 1, GL_FALSE,
        glm::value_ptr(projection));

    glm::mat4 view = mCamera.getViewMatrix();
    glUniformMatrix4fv(
        mShader.getUniformId("view"), 1, GL_FALSE, glm::value_ptr(view));

    // TODO: get model from the object class and transform if you want
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix

    glUniformMatrix4fv(
        mShader.getUniformId("model"), 1, GL_FALSE, glm::value_ptr(model));

    mVertexArray.bind();

    glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
