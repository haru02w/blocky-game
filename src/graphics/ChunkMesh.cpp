#include "ChunkMesh.hpp"
#include "../world/Chunk.hpp"
#include "../Globals.hpp"
#include "gl/ShaderProgram.hpp"
#include "glm/fwd.hpp"
#include <array>

static constexpr int BLOCK_SIZE = 1.0f;

static constexpr GLfloat FaceVertex[][20] = {
    /* FRONT */ {
        0, 0, BLOCK_SIZE, 0, 0, //
        BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE, 0, //
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, //
        0, BLOCK_SIZE, BLOCK_SIZE, 0, BLOCK_SIZE, //
    },
    /* BACK */
    {
        BLOCK_SIZE, 0, 0, 0, 0, //
        0, 0, 0, BLOCK_SIZE, 0, //
        0, BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE, //
        BLOCK_SIZE, BLOCK_SIZE, 0, 0, BLOCK_SIZE, //
    },
    /* LEFT */
    {
        0, 0, 0, 0, 0, //
        0, 0, BLOCK_SIZE, BLOCK_SIZE, 0, //
        0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, //
        0, BLOCK_SIZE, 0, 0, BLOCK_SIZE, //
    },

    /* RIGHT */
    {
        BLOCK_SIZE, 0, BLOCK_SIZE, 0, 0, //
        BLOCK_SIZE, 0, 0, BLOCK_SIZE, 0, //
        BLOCK_SIZE, BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE, //
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, BLOCK_SIZE, //
    },
    /* TOP */
    {
        0, BLOCK_SIZE, BLOCK_SIZE, 0, 0, //
        BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, 0, //
        BLOCK_SIZE, BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE, //
        0, BLOCK_SIZE, 0, 0, BLOCK_SIZE, //
    },
    /* BOTTOM */
    {
        0, 0, 0, 0, 0, //
        BLOCK_SIZE, 0, 0, BLOCK_SIZE, 0, //
        BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, //
        0, 0, BLOCK_SIZE, 0, BLOCK_SIZE, //
    }
};

ChunkMesh::ChunkMesh()
    // TODO: SWAP IT FOR A TEXTURE ATLAS
    : mTexture(TEX_PATH / "stone.jpg", false, true, [](Texture *tex) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    })
{
}

ChunkMesh::~ChunkMesh() { }

bool isAir(const Chunk &chunk, glm::ivec3 pos)
{
    const Block &block = chunk.blocks[pos.x][pos.y][pos.z];
    return block.id == Block::Type::AIR;
}

ChunkMesh &ChunkMesh::addFace(const Block &block, glm::ivec3 worldPos,
    glm::ivec3 localPos, Block::Face face)
{
    mFacesCount++;
    for (int i = 0, index = 0; i < 4; i++) {
        mVertices.push_back(FaceVertex[(int)face][index++]
            + worldPos.x * Chunk::SIZE + localPos.x);
        mVertices.push_back(FaceVertex[(int)face][index++]
            + worldPos.y * Chunk::SIZE + localPos.y);
        mVertices.push_back(FaceVertex[(int)face][index++]
            + worldPos.z * Chunk::SIZE + localPos.z);
        mVertices.push_back(FaceVertex[(int)face][index++]);
        mVertices.push_back(FaceVertex[(int)face][index++]);
    }

    mIndices.insert(mIndices.end(),
        {
            mIndicesCount + 0,
            mIndicesCount + 1,
            mIndicesCount + 2,
            mIndicesCount + 2,
            mIndicesCount + 3,
            mIndicesCount + 0,
        });
    mIndicesCount += 4;
    return *this;
}

void ChunkMesh::commit()
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
}

void ChunkMesh::draw(const ShaderProgram &shader) const
{
    shader.bind();
    mVertexArray.bind();
    mTexture.bind();
    glDrawElements(GL_TRIANGLES, mFacesCount * 6, GL_UNSIGNED_INT, 0);
}
