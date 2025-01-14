#include "../gl/ShaderProgram.hpp"
#include "../Camera.hpp"
#include "../../window/Window.hpp"
#include "../../world/Chunk.hpp"

class ChunkRenderer {
public:
    ChunkRenderer();
    ~ChunkRenderer();

    void draw(const Window &window, const Camera &camera) const;

private:
    ShaderProgram mShader;
    std::vector<Chunk> mChunks;
};
