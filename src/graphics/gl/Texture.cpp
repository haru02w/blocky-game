#include <functional>
#include <glad/glad.h>
#include "Texture.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
/////////////////////
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
/////////////////////

Texture::Texture(fs::path texturePath, bool rgba, bool mipmap,
    std::function<void(Texture *tex)> setParamsFn)
{
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    // set the texture wrapping/filtering options (on the currently bound
    // texture object)
    setParamsFn(this);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height,
        &nrChannels, rgba ? STBI_rgb_alpha : STBI_rgb);
    if (data != nullptr) [[likely]] {
        glTexImage2D(GL_TEXTURE_2D, 0, rgba ? GL_RGBA : GL_RGB, width, height,
            0, rgba ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        if (mipmap)
            glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        spdlog::error("Failed to load texture");
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(Texture &&tex) noexcept
    : mId(std::exchange(tex.mId, 0))
{
}
Texture &Texture::operator=(Texture &&tex)
{
    Texture tmp(std::move(tex));
    std::swap(mId, tmp.mId);
    return *this;
}
