#ifndef ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLRENDERERAPI_H_
#define ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLRENDERERAPI_H_
#include "Renderer/RendererAPI.h"
namespace ALink {
class OpenGLRendererAPI : public RendererAPI {
 public:
  void Init() override;
  void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
  void Clear() override;
  void SetClearColor(const glm::vec4& color) override;
  void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

};
}  // namespace ALink


#endif  // ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLRENDERERAPI_H_

