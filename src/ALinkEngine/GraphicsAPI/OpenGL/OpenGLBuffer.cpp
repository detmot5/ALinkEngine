#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace ALinkEngine {
// VertexBuffer
OpenGLVertexBuffer::OpenGLVertexBuffer(float* verticies, uint32_t size) {
  glGenBuffers(1, &this->rendererID);
  glBindBuffer(GL_ARRAY_BUFFER, this->rendererID);
  glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  glDeleteBuffers(1, &this->rendererID);
}

void OpenGLVertexBuffer::Bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, this->rendererID);
}

void OpenGLVertexBuffer::Unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// IndexBuffer

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indicies, uint32_t count)
  : count(count) {
  glGenBuffers(1, &this->rendererID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indicies, GL_STATIC_DRAW);
}

void OpenGLIndexBuffer::Bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererID);
}

void OpenGLIndexBuffer::Unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->rendererID);
}
}  // namespace ALinkEngine
