#pragma once
#include <glad/glad.h>

class VertexBuffer {
public:
    // ctor
    inline VertexBuffer() { glGenBuffers(1, &mId); }
    // dtor
    inline ~VertexBuffer() { glDeleteBuffers(1, &mId); }
    // Push data to the VertexBuffer
    inline void push(
        const GLvoid *data, GLsizeiptr bytes, GLenum usage = GL_STATIC_DRAW)
    {
        glBufferData(GL_ARRAY_BUFFER, bytes, data, usage);
    }
    // Bind the VertexBuffer
    inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, mId); }
    // Unbind the VertexBuffer
    inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

private:
    GLuint mId;
};
