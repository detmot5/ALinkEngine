#include "alinkpch.h"
#include "Application.h"
#include "Renderer/Renderer.h"
#include <glad/glad.h>

namespace ALink {

ALinkApplication::ALinkApplication() {
  Logger::Init();
  ALINK_ENGINE_ASSERT(ALinkApplication::instance == nullptr,
                      "There can be only one application!");
  ALinkApplication::instance = this;
}

ALinkApplication::~ALinkApplication() {}

void ALinkApplication::InternalInit(int argc, char* argv[]) {
  this->window = std::make_unique<Window>(WindowProps());
  this->isRunning = true;
  this->window->SetEventCallback(
      ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnEvent));
  Renderer::Init();
  this->imGuiLayer = new ImGuiLayer();
  this->AddOverlay(this->imGuiLayer);
}

void ALinkApplication::InternalEvents() {
  TimeStep ts = this->GetTimeStep();

  if (!this->isMinimized) {
    for (auto layer : this->layerStack) {
      layer->OnUpdate(ts);
    }

    this->imGuiLayer->Begin();
    for (auto layer : this->layerStack) {
      layer->OnImGuiRender();
    }
    this->imGuiLayer->End();

  }
  this->window->OnUpdate();
}

void ALinkApplication::AddLayer(Layer* layer) {
  this->layerStack.AddLayer(layer);
  layer->OnAttach();
}

void ALinkApplication::AddOverlay(Layer* overlay) {
  this->layerStack.AddOverlay(overlay);
  overlay->OnAttach();
}

TimeStep ALinkApplication::GetTimeStep() {
  static float lastFrameTime = 0;
  float currentTime = glfwGetTime();
  TimeStep timeStep = currentTime - lastFrameTime;
  lastFrameTime = currentTime;
  return timeStep;
}

void ALinkApplication::OnEvent(Event& event) {
  EventDispatcher dispacher(event);
  dispacher.Dispatch<WindowCloseEvent>(
    ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnWindowClose));
  dispacher.Dispatch<WindowResizeEvent>(
    ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnWindowResize));

  for (auto it = this->layerStack.rbegin(); it != this->layerStack.rend();
       it++) {
    if (!event.isHandled) (*it)->OnEvent(event);
  }
}

bool ALinkApplication::OnWindowClose(WindowCloseEvent& event) {
  this->isRunning = false;
  return true;
}

bool ALinkApplication::OnWindowResize(WindowResizeEvent& event) {
  if (event.GetWidth() == 0 || event.GetHeight() == 0) {
    this->isMinimized = true;
  } else {
    this->isMinimized = false;
  }
  Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
  return false;
}

}  // namespace ALink
