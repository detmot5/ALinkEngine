#include "alinkpch.h"
#include "Buffer.h"

#ifdef ALINK_GL_OPENGL
#include "GraphicsAPI/OpenGL/OpenGLBuffer.h"
#endif  // ALINK_GL_OPENGL

#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"

namespace ALink {
std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* verticies, uint32_t size) {
#ifdef ALINK_GL_OPENGL
  return std::make_shared<OpenGLVertexBuffer>(verticies, size);
#else
#error "ALINK_GL not defined! Please define API what ALink should use eg. ALINK_GL_OPENGL"
#endif  // ALINK_GL_OPENGL
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indicies, uint32_t count) {
#ifdef ALINK_GL_OPENGL
  return std::make_shared<OpenGLIndexBuffer>(indicies, count);
#else
#error "ALINK_GL not defined! Please define graphics API what ALink should use. eg. ALINK_GL_OPENGL"
#endif  // ALINK_GL_OPENGL
}
}  // namespace ALink
