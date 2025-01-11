#pragma once
#include <glad/glad.h>

class IndexBuffer {
public:
    IndexBuffer();
    ~IndexBuffer();

    // fns
    void push(
        const GLvoid *data, GLsizeiptr bytes, GLenum usage = GL_STATIC_DRAW);
    void bind() const;
    void unbind() const;
    // vars
    GLuint mId;
};
