#pragma once
#include <glad/glad.h>
#include <filesystem>
#include <unordered_map>
namespace fs = std::filesystem;

class ShaderProgram {
public:
    // ctors
    ShaderProgram(
        const fs::path &vertexSrcPath, const fs::path &fragmentSrcPath);
    ShaderProgram(const std::string &vertexSrc, const std::string &fragmentSrc);
    ShaderProgram(ShaderProgram &&) = delete;
    ShaderProgram(const ShaderProgram &) = delete;
    ShaderProgram &operator=(ShaderProgram &&) = delete;
    ShaderProgram &operator=(const ShaderProgram &) = delete;
    // dtor
    ~ShaderProgram();

    // fns
    void bind() const;
    void unbind() const;
    const GLuint getUniformId(const std::string &name) const;

    // variables
    GLuint id;

private:
    void checkCompileErrors(GLuint shaderId, const std::string &type) const;
    void populateUniforms();
    std::unordered_map<std::string, GLuint> mUniforms;
};
