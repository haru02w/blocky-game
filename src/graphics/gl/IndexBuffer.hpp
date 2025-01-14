#pragma once
#include <glad/glad.h>
#include <utility>

class IndexBuffer {
public:
    // ctor
    inline IndexBuffer() { glGenBuffers(1, &mId); }
    inline IndexBuffer(IndexBuffer &&other)
        : mId(std::exchange(other.mId, 0))
    {
    }
    // dtor
    inline ~IndexBuffer() { glDeleteBuffers(1, &mId); }

    // Push data to the IndexBuffer
    inline void push(
        const GLvoid *data, GLsizeiptr bytes, GLenum usage = GL_STATIC_DRAW)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, data, usage);
    }

    // Bind the IndexBuffer
    inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId); }

    // Unbind the IndexBuffer
    inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    inline GLuint getId() const { return mId; }

private:
    GLuint mId;
};
