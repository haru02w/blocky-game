#pragma once
#include "SimpleRenderer.hpp"
#include "ChunkRenderer.hpp"
class MasterRenderer {
public:
    MasterRenderer() = default;
    ~MasterRenderer() = default;

    // SimpleRenderer simpleRenderer;
    ChunkRenderer chunkRenderer;

private:
};
