#include "VertexBuffer.hpp"
// ctor
VertexBuffer::VertexBuffer() { glGenBuffers(1, &mId); }
// dtor
VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &mId); }

// Push data to the VertexBuffer
void VertexBuffer::push(const GLvoid *data, GLsizeiptr bytes, GLenum usage)
{
    glBufferData(GL_ARRAY_BUFFER, bytes, data, usage);
}

// Bind the VertexBuffer
void VertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, mId); }

// Unbind the VertexBuffer
void VertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
