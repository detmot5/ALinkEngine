#ifndef ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLBUFFER_H_
#define ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLBUFFER_H_
#include "Renderer/Buffer.h"
namespace ALink {
class OpenGLVertexBuffer : public VertexBuffer {
 public:
  OpenGLVertexBuffer(float* verticies, uint32_t size);
  ~OpenGLVertexBuffer();
  void Bind() const override;
  void Unbind() const override;

  inline void SetLayout(const BufferLayout& layout) override { this->layout = layout; }
  inline const BufferLayout& GetLayout() const override { return this->layout; }

 private:
  uint32_t rendererID;
  BufferLayout layout;
};

class OpenGLIndexBuffer : public IndexBuffer {
 public:
  OpenGLIndexBuffer(uint32_t* indicies, uint32_t count);
  void Bind() const override;
  void Unbind() const override;
  inline uint32_t GetCount() const override { return this->count; }
 private:
  uint32_t rendererID;
  uint32_t count;
};
}  // namespace ALink



#endif  // ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLBUFFER_H_
