#include "Chunk.hpp"
#include "Block.hpp"
#include "glm/fwd.hpp"
#include "spdlog/spdlog.h"
#include <cstdlib>

Chunk::Chunk(glm::ivec3 worldPos)
    : mWorldPos(worldPos)
{
    generateChunkBlocks();
    for (unsigned x = 0; x < blocks.size(); x++) {
        for (unsigned y = 0; y < blocks[x].size(); y++) {
            for (unsigned z = 0; z < blocks[x][y].size(); z++) {
                addBlock(glm::ivec3(x, y, z));
            }
        }
    };
    mMesh.commit();
}

void Chunk::generateChunkBlocks()
{
    srand(1);
    for (unsigned x = 0; x < blocks.size(); x++)
        for (unsigned y = 0; y < blocks[x].size(); y++)
            for (unsigned z = 0; z < blocks[x][y].size(); z++)
                if (y == rand() % Chunk::SIZE)
                    blocks[x][y][z].id = Block::Type::STONE;
}

void Chunk::addBlock(glm::ivec3 localPos)
{
    const Block &block = blocks[localPos.x][localPos.y][localPos.z];
    if (block.id == Block::Type::AIR)
        return;

    glm::ivec3 left(localPos.x - 1, localPos.y, localPos.z);
    glm::ivec3 right(localPos.x + 1, localPos.y, localPos.z);
    glm::ivec3 up(localPos.x, localPos.y + 1, localPos.z);
    glm::ivec3 down(localPos.x, localPos.y - 1, localPos.z);
    glm::ivec3 front(localPos.x, localPos.y, localPos.z + 1);
    glm::ivec3 back(localPos.x, localPos.y, localPos.z - 1);

    if (left.x < 0 || isAir(left))
        mMesh.addFace(block, mWorldPos, localPos, Block::Face::LEFT);

    if (right.x >= Chunk::SIZE || isAir(right))
        mMesh.addFace(block, mWorldPos, localPos, Block::Face::RIGHT);

    if (down.y < 0 || isAir(down))
        mMesh.addFace(block, mWorldPos, localPos, Block::Face::BOTTOM);
    if (up.y >= Chunk::SIZE || isAir(up))
        mMesh.addFace(block, mWorldPos, localPos, Block::Face::TOP);

    if (back.z < 0 || isAir(back))
        mMesh.addFace(block, mWorldPos, localPos, Block::Face::BACK);

    if (front.z >= Chunk::SIZE || isAir(front))
        mMesh.addFace(block, mWorldPos, localPos, Block::Face::FRONT);
}
