#include <functional>
#include <glad/glad.h>
#include "Texture.hpp"
#include "spdlog/spdlog.h"
#include <stb_image.h>
#include <filesystem>

namespace fs = std::filesystem;

Texture::Texture(fs::path texturePath, bool mipmap,
    std::function<void(Texture *tex)> setParamsFn)
{
    glGenTextures(1, &mId);
    glBindTexture(GL_TEXTURE_2D, mId);
    // set the texture wrapping/filtering options (on the currently bound
    // texture object)
    setParamsFn(this);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data
        = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data != nullptr) [[likely]] {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data);
        if (mipmap)
            glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        spdlog::error("Failed to load texture");
    }
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() { glDeleteTextures(1, &mId); }

void Texture::bind() const { glBindTexture(GL_TEXTURE_2D, mId); }
void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
