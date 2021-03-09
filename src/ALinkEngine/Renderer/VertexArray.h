#ifndef ALINKENGINE_RENDERER_VERTEXARRAY_H_
#define ALINKENGINE_RENDERER_VERTEXARRAY_H_
#include "Renderer/Buffer.h"

namespace ALink {

class VertexArray {
 public:
  virtual void Bind() const = 0;
  virtual void Unbind() const = 0;

  virtual void AddVertexBuffer(
      const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
  virtual void SetIndexBuffer(
      const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

  virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const = 0;
  virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;


  static std::shared_ptr<VertexArray> Create();
};
}  // namespace ALink

#endif  // ALINKENGINE_RENDERER_VERTEXARRAY_H_
