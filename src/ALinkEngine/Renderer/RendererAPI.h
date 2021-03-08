#ifndef ALINKENGINE_RENDERER_RENDERERAPI_H_
#define ALINKENGINE_RENDERER_RENDERERAPI_H_
#include <glm/glm.hpp>
#include "Renderer/VertexArray.h"

namespace ALinkEngine {
class RendererAPI {
 public:
  virtual void Clear() = 0;
  virtual void SetClearColor(const glm::vec4& color) = 0;

  virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
 private:
};

}  // namespace ALinkEngine

#endif  // ALINKENGINE_RENDERER_RENDERERAPI_H_

