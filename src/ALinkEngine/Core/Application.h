#ifndef ALINKENGINE_CORE_APPLICATION_H_
#define ALINKENGINE_CORE_APPLICATION_H_
#include "Core/LayerStack.h"
#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Core/TimeStep.h"
#include "GUI/ImGuiLayer.h"

namespace ALink {

// ALinkApplication is a singleton but with public constructor
// When user is trying to create second instance application should crash

class ALinkApplication {
 public:
  ALinkApplication();
  virtual ~ALinkApplication();
  void InternalInit(int argc, char* argv[]);
  void InternalEvents();
  inline bool IsRunning() { return isRunning; }
  inline Window& GetWindow() { return *window; }

  void AddLayer(Layer* layer);
  void AddOverlay(Layer* overlay);

  virtual void Init() {}
  virtual void ShutDown() {}
  virtual void Run() {}

  static inline ALinkApplication& GetInstance() { return *instance; }

 private:
  TimeStep GetTimeStep();
  void OnEvent(Event& event);
  bool OnWindowCloseEvent(WindowCloseEvent& event);
  

 private:
  std::unique_ptr<Window> window;
  ImGuiLayer* imGuiLayer;
  LayerStack layerStack;
  bool isRunning;
  float lastFrameTime = 0.0f;
  static inline ALinkApplication* instance = nullptr;

};

ALinkApplication* CreateApplication();
}  // namespace ALink

#endif  // ALINKENGINE_CORE_APPLICATION_H_
