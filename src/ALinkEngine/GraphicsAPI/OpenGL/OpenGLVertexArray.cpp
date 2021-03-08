#include "alinkpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace ALinkEngine {

static GLenum ShaderDataTypeToOpenGLDataType(ShaderDataType type) {
  switch (type) {
    case ShaderDataType::Float:   return GL_FLOAT;
    case ShaderDataType::Float2:  return GL_FLOAT;
    case ShaderDataType::Float3:  return GL_FLOAT;
    case ShaderDataType::Float4:  return GL_FLOAT;
    case ShaderDataType::Mat3:    return GL_FLOAT;
    case ShaderDataType::Mat4:    return GL_FLOAT;
    case ShaderDataType::Int:     return GL_INT;
    case ShaderDataType::Int2:    return GL_INT;
    case ShaderDataType::Int3:    return GL_INT;
    case ShaderDataType::Int4:    return GL_INT;
    case ShaderDataType::Bool:    return GL_BOOL;
  }
  ALINK_ENGINE_ASSERT(false, "Unknown ShaderDataType!");
  return 0;
}


OpenGLVertexArray::OpenGLVertexArray() {
  glGenVertexArrays(1, &this->rendererID);
  glBindVertexArray(this->rendererID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
  glDeleteVertexArrays(1, &this->rendererID);
}

void OpenGLVertexArray::Bind() const {
  glBindVertexArray(this->rendererID);
}

void OpenGLVertexArray::Unbind() const {
  glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(
    const std::shared_ptr<VertexBuffer>& vertexBuffer) {
  ALINK_ENGINE_ASSERT(vertexBuffer->GetLayout().GetElements().size() != 0,
                      "VertexBuffer should be added after setting its layout");
  this->Bind();
  vertexBuffer->Bind();
  uint32_t index = 0;
  const auto& layout = vertexBuffer->GetLayout();
  for (const auto& element : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(
      index,
      BufferElement::GetElementsCount(element.type),
      ShaderDataTypeToOpenGLDataType(element.type),
      element.isNormalized,
      layout.GetStride(),
      reinterpret_cast<const void*>(element.offset));
    index++;
  }
  this->vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::SetIndexBuffer(
    const std::shared_ptr<IndexBuffer>& indexBuffer) {
  this->Bind();
  indexBuffer->Bind();
  this->indexBuffer = indexBuffer;
}
}  // namespace ALinkEngine
