#include <alloca.h>
#include <filesystem>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "utils.hpp"
#include "ShaderProgram.hpp"
namespace fs = std::filesystem;

ShaderProgram::ShaderProgram(
    const fs::path &vertexSrcPath, const fs::path &fragmentSrcPath)
    : mUniforms()
{
    // Vertex Shader
    GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexSrc = utils::getStrFromFile(vertexSrcPath);
    const char *vertexSrcPtr = vertexSrc.c_str();

    glShaderSource(vertexId, 1, &vertexSrcPtr, nullptr);
    glCompileShader(vertexId);
    checkCompileErrors(vertexId, "Vertex");

    // Fragment Shader
    GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentSrc = utils::getStrFromFile(fragmentSrcPath);
    const char *fragmentSrcPtr = fragmentSrc.c_str();

    glShaderSource(fragmentId, 1, &fragmentSrcPtr, nullptr);
    glCompileShader(fragmentId);
    checkCompileErrors(vertexId, "Fragment");

    // Shader Program
    id = glCreateProgram();

    glAttachShader(id, vertexId);
    glAttachShader(id, fragmentId);

    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");

    populateUniforms();

    glDetachShader(id, vertexId);
    glDetachShader(id, fragmentId);
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

void ShaderProgram::populateUniforms()
{
    int uniformCount;
    glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &uniformCount);

    int uniformMaxLength;
    glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformMaxLength);

    if (uniformCount <= 0 || uniformMaxLength <= 0)
        return;

    char *uniformName = (char *)alloca(sizeof(char) * uniformMaxLength);
    for (int i = 0; i < uniformCount; i++) {
        int length, size;
        GLenum dataType;
        glGetActiveUniform(
            id, i, uniformMaxLength, &length, &size, &dataType, uniformName);
        GLint uniformLocation = glGetUniformLocation(id, uniformName);

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

ShaderProgram::~ShaderProgram() { glDeleteProgram(id); }

void ShaderProgram::bind() const { glUseProgram(id); }
void ShaderProgram::unbind() const { glUseProgram(0); }

const GLuint ShaderProgram::getUniformId(const std::string &name) const
{
    return mUniforms.at(name.data());
}
