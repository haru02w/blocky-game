#pragma once
#include <cstddef>
#include <glad/glad.h>
#include <utility>
class VertexArray {
public:
    inline VertexArray() { glGenVertexArrays(1, &mId); }
    inline VertexArray(VertexArray &&other)
        : mId(std::exchange(other.mId, 0))
    {
    }
    inline ~VertexArray() { glDeleteVertexArrays(1, &mId); }

    // fns
    inline void push(GLuint index, GLint components, GLenum type,
        GLsizei stride, std::size_t offset,
        GLboolean normalized = GL_FALSE) const
    {
        glVertexAttribPointer(index, components, type, normalized, stride,
            reinterpret_cast<const void *>(offset));
        glEnableVertexAttribArray(index);
    }
    inline void bind() const { glBindVertexArray(mId); }
    inline void unbind() const { glBindVertexArray(0); }
    inline GLuint getId() const { return mId; }

private:
    GLuint mId;
};
