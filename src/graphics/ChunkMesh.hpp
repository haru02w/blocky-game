#pragma once

#include "gl/IndexBuffer.hpp"
#include "gl/ShaderProgram.hpp"
#include "gl/Texture.hpp"
#include "gl/VertexArray.hpp"
#include "gl/VertexBuffer.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "../world/Block.hpp"
#include "glm/fwd.hpp"
class Chunk;

// TODO: compact it all into one integer
struct Vertex {
    glm::vec3 pos;
    glm::vec2 texCoords;
};

class ChunkMesh {
public:
    ChunkMesh();
    ChunkMesh(ChunkMesh &&other)
        : mVertices(std::move(other.mVertices))
        , mIndices(std::move(other.mIndices))
        , mTexture(std::move(other.mTexture))
        , mVertexArray(std::move(other.mVertexArray))
        , mVertexBuffer(std::move(other.mVertexBuffer))
        , mIndexBuffer(std::move(other.mIndexBuffer))
        , mIndicesCount(other.mIndicesCount)
        , mFacesCount(other.mFacesCount)
    {
    }
    ChunkMesh &addFace(const Block &block, glm::ivec3 worldPos,
        glm::ivec3 localPos, Block::Face face);

    void commit();
    void draw(const ShaderProgram &shader) const;
    ~ChunkMesh();

private:
    // TODO: change to Vertex Struct
    std::vector<GLfloat> mVertices;
    std::vector<GLuint> mIndices;
    // TODO: TextureAtlas textureAtlas;

    Texture mTexture; // TODO: remove it
    VertexArray mVertexArray;
    VertexBuffer mVertexBuffer;
    IndexBuffer mIndexBuffer;

    GLuint mIndicesCount = 0;
    GLuint mFacesCount = 0;
};
