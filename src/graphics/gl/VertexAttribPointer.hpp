#pragma once
#include <cstddef>
#include <glad/glad.h>

struct VertexAttribPointer {
    GLint components;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    std::size_t offset;
};
