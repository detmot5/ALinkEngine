#ifndef ALINKENGINE_RENDERER_RENDERER_H_
#define ALINKENGINE_RENDERER_RENDERER_H_
#include <glm/glm.hpp>
#include "Renderer/VertexArray.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/OrthographicCamera.h"
#include "Renderer/Shader.h"
namespace ALink {

struct SceneData {
  glm::mat4 viewProjectionMatrix;
};

class Renderer {
 public:
  static void BeginScene(const OrthographicCamera& camera);
  static void EndScene();
  static void Submit(const std::shared_ptr<Shader>& shader,
                      const std::shared_ptr<VertexArray>& vertexArray);
 private:
  static inline std::unique_ptr<SceneData> sceneData =
                                             std::make_unique<SceneData>();
};
}  // namespace ALink

#endif  // ALINKENGINE_RENDERER_RENDERER_H_
