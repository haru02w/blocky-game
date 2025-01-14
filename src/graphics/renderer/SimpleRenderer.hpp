#include <vector>
#include "../gl/ShaderProgram.hpp"
#include "../gl/Texture.hpp"
#include "../gl/VertexArray.hpp"
#include "../gl/VertexBuffer.hpp"
#include "../gl/IndexBuffer.hpp"
#include "../Camera.hpp"
#include "../../window/Window.hpp"

class SimpleRenderer {
public:
    SimpleRenderer();
    ~SimpleRenderer();

    void draw(const Window &window, const Camera &camera) const;

private:
    ShaderProgram mShader;
    std::vector<float> mVertices;
    std::vector<unsigned> mIndices;
    Texture mTexture;
    VertexArray mVertexArray;
    VertexBuffer mVertexBuffer;
    IndexBuffer mIndexBuffer;
};
