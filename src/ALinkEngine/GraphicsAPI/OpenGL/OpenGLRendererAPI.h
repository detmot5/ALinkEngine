#ifndef ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLRENDERERAPI_H_
#define ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLRENDERERAPI_H_
#include "Renderer/RendererAPI.h"
namespace ALink {
class OpenGLRendererAPI : public RendererAPI {
 public:
  void Clear() override;
  void SetClearColor(const glm::vec4& color) override;
  void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

};
}  // namespace ALink


#endif  // ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLRENDERERAPI_H_

