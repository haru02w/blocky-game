#include "VertexArray.hpp"
#include <cstddef>
#include <glad/glad.h>

VertexArray::VertexArray() { glGenVertexArrays(1, &mId); }
VertexArray::~VertexArray() { glDeleteVertexArrays(1, &mId); }

// fns
void VertexArray::push(GLuint index, GLint components, GLenum type,
    GLsizei stride, std::size_t offset, GLboolean normalized) const
{
    glVertexAttribPointer(index, components, type, normalized, stride,
        reinterpret_cast<const void *>(offset));
    glEnableVertexAttribArray(index);
}
void VertexArray::bind() const { glBindVertexArray(mId); }
void VertexArray::unbind() const { glBindVertexArray(0); }
