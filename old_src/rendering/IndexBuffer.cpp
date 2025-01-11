#include "IndexBuffer.hpp"
// ctor
IndexBuffer::IndexBuffer() { glGenBuffers(1, &mId); }
// dtor
IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &mId); }

// Push data to the IndexBuffer
void IndexBuffer::push(const GLvoid *data, GLsizeiptr bytes, GLenum usage)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, data, usage);
}

// Bind the IndexBuffer
void IndexBuffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId); }

// Unbind the IndexBuffer
void IndexBuffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
