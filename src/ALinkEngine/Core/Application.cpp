#include "Application.h"

namespace ALinkEngine {

ALinkApplication::ALinkApplication() {
  ALINK_ENGINE_ASSERT(ALinkApplication::instance == nullptr,
                      "There can be only one application!");
  ALinkApplication::instance = this;
}

ALinkApplication::~ALinkApplication() {}

void ALinkApplication::InternalInit(int argc, char* argv[]) {
  Logger::Init();
  this->window = std::make_unique<Window>(WindowProps());
  this->isRunning = true;
  this->window->SetEventCallback(
      ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnEvent));
  this->imGuiLayer = new ImGuiLayer();
  this->AddOverlay(this->imGuiLayer);
}

void ALinkApplication::InternalEvents() {
  // temporaty as fuck !
  glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto layer : this->layerStack) {
    layer->OnUpdate();
  }

  this->imGuiLayer->Begin();
  for (auto layer : this->layerStack) {
    layer->OnImGuiRender();
  }
  this->imGuiLayer->End();

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

void ALinkApplication::OnEvent(Event& event) {
  EventDispatcher dispacher(event);
  dispacher.Dispatch<WindowCloseEvent>(
      ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnWindowCloseEvent));

  for (auto it = this->layerStack.rbegin();
       it != this->layerStack.rend(); it++) {
    if (!event.isHandled) (*it)->OnEvent(event);
  }
}

bool ALinkApplication::OnWindowCloseEvent(WindowCloseEvent& event) {
  this->isRunning = false;
  return true;
}

}  // namespace ALinkEngine
