#ifndef ALINKENGINE_RENDERER_RENDERCOMMAND_H_
#define ALINKENGINE_RENDERER_RENDERCOMMAND_H_
#include "Renderer/RendererAPI.h"

namespace ALink {

class RenderCommand {
 public:
  static inline void Init() {rendererAPI->Init();}
  static inline void SetViewPort(uint32_t width, uint32_t height) {
    rendererAPI->SetViewPort(0, 0, width, height);
  }
  static inline void SetClearColor(const glm::vec4& color) { rendererAPI->SetClearColor(color); }
  static inline void Clear() { rendererAPI->Clear(); }
  static inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
    rendererAPI->DrawIndexed(vertexArray);
  }
 private:
  static std::unique_ptr<RendererAPI> rendererAPI;
};

  
}  // namespace ALink


#endif  // ALINKENGINE_RENDERER_RENDERCOMMAND_H_


