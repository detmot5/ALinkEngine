#ifndef ALINKENGINE_RENDERER_RENDERER2D_H_
#define ALINKENGINE_RENDERER_RENDERER2D_H_
#include <glm/glm.hpp>
#include "Renderer/OrthographicCamera.h"

namespace ALink {
class Renderer2D {
 public:
  static void Init();
  static void ShutDown();

  static void BeginScene(const OrthographicCamera& camera);
  static void EndScene();
  // Primitives

  static void DrawQuad(const glm::vec2& positions, const glm::vec2& size, const glm::vec4& color);
  static void DrawQuad(const glm::vec3& positions, const glm::vec2& size, const glm::vec4& color);


  static void DrawBezierCube();

};
}  // namespace ALink



#endif  // ALINKENGINE_RENDERER_RENDERER2D_H_
