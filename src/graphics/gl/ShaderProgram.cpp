#include <alloca.h>
#include <filesystem>
#include <glad/glad.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include "../../utils/utils.hpp"
#include "ShaderProgram.hpp"
namespace fs = std::filesystem;
ShaderProgram::ShaderProgram(
    const std::string &vertexSrc, const std::string &fragmentSrc)
    : mUniforms()
{
    GLuint vertexId = createVertexId(vertexSrc);
    GLuint fragmentId = createFragmentId(fragmentSrc);
    // Shader Program
    mId = glCreateProgram();

    glAttachShader(mId, vertexId);
    glAttachShader(mId, fragmentId);

    glLinkProgram(mId);
    checkCompileErrors(mId, "PROGRAM");

    populateUniforms();

    glDetachShader(mId, vertexId);
    glDetachShader(mId, fragmentId);
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

ShaderProgram::ShaderProgram(
    const fs::path &vertexSrcPath, const fs::path &fragmentSrcPath)
    : ShaderProgram(utils::getStrFromFile(vertexSrcPath),
          utils::getStrFromFile(fragmentSrcPath))
{
    spdlog::debug("vertexSrcPath: {}, fragmentSrcPath: {}",
        vertexSrcPath.c_str(), fragmentSrcPath.c_str());
}

GLuint ShaderProgram::createVertexId(const std::string &vertexSrc) const
{
    // Vertex Shader
    GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexSrcPtr = vertexSrc.c_str();

    glShaderSource(vertexId, 1, &vertexSrcPtr, nullptr);
    glCompileShader(vertexId);
    checkCompileErrors(vertexId, "Vertex");
    return vertexId;
}

GLuint ShaderProgram::createFragmentId(const std::string &fragmentSrc) const
{
    // Fragment Shader
    GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentSrcPtr = fragmentSrc.c_str();

    glShaderSource(fragmentId, 1, &fragmentSrcPtr, nullptr);
    glCompileShader(fragmentId);
    checkCompileErrors(fragmentId, "Fragment");
    return fragmentId;
}

void ShaderProgram::populateUniforms()
{
    int uniformCount;
    glGetProgramiv(mId, GL_ACTIVE_UNIFORMS, &uniformCount);

    int uniformMaxLength;
    glGetProgramiv(mId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength);

    if (uniformCount <= 0 || uniformMaxLength <= 0)
        return;

    char *uniformName = (char *)alloca(sizeof(char) * uniformMaxLength);
    for (int i = 0; i < uniformCount; i++) {
        int length, size;
        GLenum dataType;
        glGetActiveUniform(
            mId, i, uniformMaxLength, &length, &size, &dataType, uniformName);
        GLint uniformLocation = glGetUniformLocation(mId, uniformName);

        mUniforms[uniformName] = uniformLocation;
    }
}

void ShaderProgram::checkCompileErrors(
    GLuint shaderId, const std::string &type) const
{
    int success;
    std::string infoLog(512, '\0');

    if (type == "PROGRAM") {
        glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
        if (success)
            return;
        glGetProgramInfoLog(shaderId, infoLog.size(), NULL, infoLog.data());
    } else {
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (success)
            return;
        glGetShaderInfoLog(shaderId, infoLog.size(), NULL, infoLog.data());
    }

    spdlog::error("{} Shader compilation error: \n{}", type, infoLog);
}
