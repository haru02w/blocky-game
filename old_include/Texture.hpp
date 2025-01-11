#pragma once
#include <functional>
#include <glad/glad.h>
#include <filesystem>

namespace fs = std::filesystem;

class Texture {
public:
    Texture(fs::path texturePath, bool mipmap,
        std::function<void(Texture *tex)> setParamsFn);
    Texture(Texture &&) = default;
    Texture(const Texture &) = default;
    Texture &operator=(Texture &&) = default;
    Texture &operator=(const Texture &) = default;
    ~Texture();

    void bind() const;
    void unbind() const;

private:
    GLuint mId;
};
