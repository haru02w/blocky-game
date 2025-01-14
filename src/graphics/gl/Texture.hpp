#pragma once
#include <functional>
#include <glad/glad.h>
#include <filesystem>
namespace fs = std::filesystem;

class Texture {
public:
    Texture(fs::path texturePath, bool rgba, bool mipmap,
        std::function<void(Texture *tex)> setParamsFn);
    Texture(const Texture &) = delete;
    Texture &operator=(const Texture &) = delete;
    Texture(Texture &&tex) noexcept;
    Texture &operator=(Texture &&tex);

    inline ~Texture() { glDeleteTextures(1, &mId); }

    inline void bind() const { glBindTexture(GL_TEXTURE_2D, mId); }
    inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

private:
    GLuint mId;
};
