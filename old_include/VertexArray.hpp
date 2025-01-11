#pragma once
#include <cstddef>
#include <glad/glad.h>
class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    // fns
    void push(GLuint index, GLint components, GLenum type, GLsizei stride,
        std::size_t offset, GLboolean normalized = GL_FALSE) const;

    void bind() const;
    void unbind() const;
    // vars
    GLuint mId;
};
