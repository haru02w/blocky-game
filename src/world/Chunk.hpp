#pragma once
#include <array>
#include "Block.hpp"
#include "../graphics/ChunkMesh.hpp"
#include "glm/fwd.hpp"

struct AdjacentBlocks {
    const Block &up;
    const Block &down;
    const Block &left;
    const Block &right;
    const Block &front;
    const Block &back;
};

class Chunk {
public:
    static constexpr int SIZE = 32;
    Chunk(glm::ivec3 worldPos);

    void update(); // TODO
    inline void draw(const ShaderProgram &shader) const { mMesh.draw(shader); }

    std::array<std::array<std::array<Block, SIZE>, SIZE>, SIZE> blocks;

private:
    void addBlock(glm::ivec3 localPos);

    void generateChunkBlocks();
    inline bool isAir(glm::ivec3 localPos)
    {
        return blocks[localPos.x][localPos.y][localPos.z].id
            == Block::Type::AIR;
    }

    glm::ivec3 mWorldPos;
    ChunkMesh mMesh;
};
