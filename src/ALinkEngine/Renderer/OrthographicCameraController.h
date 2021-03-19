#ifndef ALINKENGINE_RENDERER_ORTHOGRAPHICCAMERACONTROLLER_H_
#define ALINKENGINE_RENDERER_ORTHOGRAPHICCAMERACONTROLLER_H_
#include <glm/glm.hpp>
#include "Renderer/OrthographicCamera.h"
#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"
#include "Core/TimeStep.h"
#include "Core/Input.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
namespace ALink {

class OrthographicCameraController {
 public:
  OrthographicCameraController(float aspectRatio,
                               bool isRotationEnabled = false);
  void OnUpdate(TimeStep ts);
  void OnEvent(Event& event);

  inline OrthographicCamera& GetCamera() { return this->camera; }
  inline const OrthographicCamera& GetCamera() const { return this->camera; }
 private:
  bool OnMouseScrolled(MouseScrolledEvent& event);
  bool OnWindowResized(WindowResizeEvent& event);

 private:
  float aspectRatio;
  float zoomLevel = 1.0f;
  float cameraTranslationSpeed = 5.0f;
  float cameraRotationSpeed = 180.0f;
  glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };
  bool isRotationEnabled;
  OrthographicCamera camera;
};
}  // namespace ALink



#endif  // ALINKENGINE_RENDERER_ORTHOGRAPHICCAMERACONTROLLER_H_
