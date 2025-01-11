#pragma once
#include <functional>
#include <glad/glad.h>
#include <filesystem>

namespace fs = std::filesystem;

class Texture {
public:
    Texture(fs::path texturePath, bool mipmap,
        std::function<void(Texture *tex)> setParamsFn);
    inline Texture() { glDeleteTextures(1, &mId); }

    inline void bind() const { glBindTexture(GL_TEXTURE_2D, mId); }
    inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

private:
    GLuint mId;
};
