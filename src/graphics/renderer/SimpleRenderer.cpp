#include "SimpleRenderer.hpp"
#include "../gl/ShaderProgram.hpp"
#include "../gl/Texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Globals.hpp"

SimpleRenderer::SimpleRenderer()
    : mShader(SHADER_PATH / "simple_vertex.glsl",
          SHADER_PATH / "simple_fragment.glsl")
    , mVertices({
          // positions          // texture coords
          // Back
          1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 1
          0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 2
          0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 3
          1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 4
          // Front
          0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 1
          1.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 2
          1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 3
          0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 4
          // Right
          1.0f, 0.0f, 1.0f, 0.0f, 1.0f, // 1
          1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 2
          1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 3
          1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 4
          // Left
          0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 1
          0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 2
          0.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 3
          0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 4
          // Top
          0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 1
          1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 2
          1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 3
          0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 4
          // Bottom
          0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // 1
          1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 2
          1.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 3
          0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 4
      })
    , mIndices({
          // Back
          0, 1, 2, // 1
          2, 3, 0, // 2
          // Front
          4, 5, 6, //
          6, 7, 4, //
          // Right
          8, 9, 10, //
          10, 11, 8, //
          // Left
          12, 13, 14, //
          14, 15, 12, //
          // Top
          16, 17, 18, //
          18, 19, 16, //
          // Bottom
          20, 21, 22, //
          22, 23, 20, //
      })
    , mTexture(TEX_PATH / "texture.jpg", false, true,
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
    // glEnable(GL_CULL_FACE); // NOTE: test
    // glCullFace(GL_BACK);
    // Enable wireframe for debug purposes
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

SimpleRenderer::~SimpleRenderer() { }

void SimpleRenderer::draw(const Window &window, const Camera &camera) const
{
    auto [scrWidth, scrHeight] = window.getSize();
    mShader.bind();
    glClearColor(
        0.2666666667f, 0.5568627451f, 0.8941176471, 1.0f); // dark sky-blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mTexture.bind();

    glm::mat4 projection = camera.getProjectionMatrix(scrWidth, scrHeight);
    glUniformMatrix4fv(mShader.getUniformId("projection"), 1, GL_FALSE,
        glm::value_ptr(projection));

    glm::mat4 view = camera.getViewMatrix();
    glUniformMatrix4fv(
        mShader.getUniformId("view"), 1, GL_FALSE, glm::value_ptr(view));

    // TODO: get model from the object class and transform if you want
    glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix

    glUniformMatrix4fv(
        mShader.getUniformId("model"), 1, GL_FALSE, glm::value_ptr(model));

    mVertexArray.bind();

    // glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
