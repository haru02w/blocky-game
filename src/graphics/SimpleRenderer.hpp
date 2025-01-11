#include <vector>
#include "gl/ShaderProgram.hpp"
#include "gl/Texture.hpp"
#include "gl/VertexArray.hpp"
#include "gl/VertexBuffer.hpp"
#include "gl/IndexBuffer.hpp"
#include "Camera.hpp"

class SimpleRenderer {
public:
    SimpleRenderer(Camera &camera);
    ~SimpleRenderer();

    void draw(int srcWidth, int srcHeight) const;

private:
    ShaderProgram mShader;
    std::vector<float> mVertices;
    std::vector<unsigned> mIndices;
    Texture mTexture;
    VertexArray mVertexArray;
    VertexBuffer mVertexBuffer;
    IndexBuffer mIndexBuffer;
    Camera &mCamera;
};
