#include "Application.h"
namespace ALinkEngine {

ALinkApplication::ALinkApplication() {}

ALinkApplication::~ALinkApplication() {}

void ALinkApplication::InternalInit(int argc, char* argv[]) {
  loguru::init(argc, argv);
  this->window = CreateScope<Window>(WindowProps());
  this->isRunning = true;
  this->window->SetEventCallback(
      ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnEvent));
}

void ALinkApplication::InternalEvents() {
  this->window->OnUpdate();
  for (auto layer : this->layerStack) {
    layer->OnUpdate();
  }
}

void ALinkApplication::OnEvent(Event& event) {
  EventDispatcher dispacher(event);
  dispacher.Dispatch<WindowCloseEvent>(
      ALINK_BIND_EVENT_CALLBACK(ALinkApplication::OnWindowCloseEvent));

  for (auto it = this->layerStack.reverseBegin();
       it != this->layerStack.reverseEnd(); it++) {
    if (!event.isHandled)
      (*it)->OnEvent(event);
  }

  ALINK_LOG_INFO(event.ToString().c_str());
}

bool ALinkApplication::OnWindowCloseEvent(WindowCloseEvent& event) {
  this->isRunning = false;
  return true;
}

}  // namespace ALinkEngine
