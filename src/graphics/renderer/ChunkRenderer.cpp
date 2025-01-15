#include "ChunkRenderer.hpp"
#include "../gl/ShaderProgram.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Globals.hpp"
ChunkRenderer::ChunkRenderer()
    : mShader(SHADER_PATH / "chunk_vertex.glsl",
          SHADER_PATH / "chunk_fragment.glsl")
{
    for (float y = 0; y < 16; y++) {

        for (float z = 0; z < 16; z++) {
            mChunks.emplace_back(glm::ivec3(0.0f, y, z));
        }
    }
    // enable z-buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // NOTE: test
    glCullFace(GL_BACK);
    // Enable wireframe for debug purposes
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

ChunkRenderer::~ChunkRenderer() { }

void ChunkRenderer::draw(const Window &window, const Camera &camera) const
{
    auto [scrWidth, scrHeight] = window.getSize();
    mShader.bind();
    glClearColor(
        0.2666666667f, 0.5568627451f, 0.8941176471, 1.0f); // dark sky-blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projectionView = camera.getProjectionMatrix(scrWidth, scrHeight)
        * camera.getViewMatrix();
    glUniformMatrix4fv(mShader.getUniformId("ProjectionView"), 1, GL_FALSE,
        glm::value_ptr(projectionView));

    for (auto &chunk : mChunks)
        chunk.draw(mShader);
}
