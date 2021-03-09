#ifndef ALINKENGINE_RENDERER_ORTHOGRAPHICCAMERA_H_
#define ALINKENGINE_RENDERER_ORTHOGRAPHICCAMERA_H_
#include <glm/glm.hpp>

namespace ALink {

class OrthographicCamera {
 public:
  OrthographicCamera(float left, float right, float bottom, float top);

  void SetPosition(const glm::vec3& position);
  void SetRotation(float rotation);

  inline const glm::vec3& GetPosition() const { return this->position; }
  inline float GetRotation() const { return this->rotation; }
  inline const glm::mat4& GetProjectionMatrix() const { return this->projectionMatrix; }
  inline const glm::mat4& GetViewMatrix() const { return this->viewMatrix; }
  inline const glm::mat4& GetViewProjectionMatrix() const { return this->viewProjectionMatrix; }
  

 private:
  void RecalculateViewMatrix();

 private:

  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;
  glm::mat4 viewProjectionMatrix;
  glm::vec3 position = {0.0f, 0.0f, 0.0f};
  float rotation = 0.0f;
};


} // namespace ALink



#endif  // ALINKENGINE_RENDERER_ORTHOGRAPHICCAMERA_H_
