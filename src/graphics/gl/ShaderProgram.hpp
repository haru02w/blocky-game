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

    // dtor
    inline ~ShaderProgram() { glDeleteProgram(mId); }

    // fns
    inline void bind() const { glUseProgram(mId); }
    inline void unbind() const { glUseProgram(0); }
    inline const GLuint getUniformId(const std::string &name) const
    {
        return mUniforms.at(name.data());
    }

    inline GLuint getId() const { return mId; }

private:
    GLuint createVertexId(const std::string &vertexSrc) const;
    GLuint createFragmentId(const std::string &fragmentSrc) const;

    void checkCompileErrors(GLuint shaderId, const std::string &type) const;
    void populateUniforms();

    GLuint mId;
    std::unordered_map<std::string, GLuint> mUniforms;
};
