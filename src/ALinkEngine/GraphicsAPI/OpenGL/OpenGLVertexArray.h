#ifndef ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLVERTEXARRAY_H_
#define ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLVERTEXARRAY_H_
#include "Renderer/VertexArray.h"
namespace ALinkEngine {

class OpenGLVertexArray : public VertexArray {
 public:
  OpenGLVertexArray();
  ~OpenGLVertexArray();
  void Bind() const override;
  void Unbind() const override;

  void AddVertexBuffer(
      const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
  inline std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const {
    return this->vertexBuffers;
  }
  inline std::shared_ptr<IndexBuffer> GetIndexBuffer() const {
    return this->indexBuffer;
  }

 private:
  std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
  std::shared_ptr<IndexBuffer> indexBuffer;
  uint32_t rendererID;
};
}  // namespace ALinkEngine

#endif  // ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLVERTEXARRAY_H_
