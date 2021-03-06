
#include "Buffer.h"

#include "GraphicsAPI/OpenGL/OpenGLBuffer.h"
#include "Renderer/Renderer.h"

// TODO(me):  to refactor - we don't need runtime switching API's
namespace ALinkEngine {
VertexBuffer* VertexBuffer::Create(float* verticies, uint32_t size) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::None:
      ALINK_ENGINE_ASSERT(
          false, "Current API is set to None - now it's not supported!");
    case RendererAPI::OpenGL:
      return new OpenGLVertexBuffer(verticies, size);
  }
  ALINK_ENGINE_ASSERT(false, "Graphics API not found");
  return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indicies, uint32_t count) {
  switch (Renderer::GetAPI()) {
    case RendererAPI::None:
      ALINK_ENGINE_ASSERT(
          false, "Current API is set to None - now it's not supported!");
    case RendererAPI::OpenGL:
      return new OpenGLIndexBuffer(indicies, count);
  }
  ALINK_ENGINE_ASSERT(false, "Graphics API not found");
  return nullptr;
}
}  // namespace ALinkEngine
