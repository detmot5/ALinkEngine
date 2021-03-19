#include "alinkpch.h"
#include "OrthographicCameraController.h"

namespace ALink {
OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool isRotationEnabled)
  : aspectRatio(aspectRatio), isRotationEnabled(isRotationEnabled),
    camera(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel) {
  
}

void OrthographicCameraController::OnUpdate(TimeStep ts) {
  // ALINK_LOG_INFO("Current framerate: {0}", 1 / ts.GetSeconds());
  float spd = this->cameraTranslationSpeed * ts;
  if (Input::IsKeyPressed(Key::W)) {
    auto pos = camera.GetPosition();
    pos.y += spd;
    camera.SetPosition(pos);
  } else if (Input::IsKeyPressed(Key::S)) {
    auto pos = camera.GetPosition();
    pos.y -= spd;
    camera.SetPosition(pos);
  } else if (Input::IsKeyPressed(Key::A)) {
    auto pos = camera.GetPosition();
    pos.x -= spd;
    camera.SetPosition(pos);
  } else if (Input::IsKeyPressed(Key::D)) {
    auto pos = camera.GetPosition();
    pos.x += spd;
    camera.SetPosition(pos);
  }
  if (this->isRotationEnabled) {
    if (Input::IsKeyPressed(Key::Q)) {
      auto rotation = camera.GetRotation();
      camera.SetRotation(rotation += this->cameraRotationSpeed * ts);
    } else if (Input::IsKeyPressed(Key::E)) {
      auto rotation = camera.GetRotation();
      camera.SetRotation(rotation -= this->cameraRotationSpeed * ts);
    }
  }

  this->cameraTranslationSpeed = this->zoomLevel * 2;


}

void OrthographicCameraController::OnEvent(Event& event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<WindowResizeEvent>(
    ALINK_BIND_EVENT_CALLBACK(OrthographicCameraController::OnWindowResized));
  dispatcher.Dispatch<MouseScrolledEvent>(
    ALINK_BIND_EVENT_CALLBACK(OrthographicCameraController::OnMouseScrolled));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event) {
  if (Input::IsKeyPressed(Key::LeftControl)) {
    this->zoomLevel -= event.GetYOffset() * 0.25;
    this->zoomLevel = std::max(this->zoomLevel, 0.25f);
    ALINK_LOG_INFO(zoomLevel);
    this->camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
  }
  return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event) {
  this->aspectRatio = static_cast<float>(event.GetWidth()) / static_cast<float>(event.GetHeight());
  this->camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
  return false;
}


}  // namespace ALink
