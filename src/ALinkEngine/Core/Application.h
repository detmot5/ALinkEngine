#ifndef ALINKENGINE_CORE_APPLICATION_H_
#define ALINKENGINE_CORE_APPLICATION_H_
#include <glad/glad.h>
#include "Core/Core.h"
#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Events/ApplicationEvent.h"
#include "alinkpch.h"

namespace ALinkEngine {

class ALinkApplication {
 public:
  ALinkApplication();
  virtual ~ALinkApplication();
  void InternalInit(int argc, char* argv[]);
  void InternalEvents();
  inline bool IsRunning() { return isRunning; }
  inline void AddLayer(Layer* layer) { layerStack.AddLayer(layer); }
  inline void AddOverlay(Layer* overlay) { layerStack.AddOverlay(overlay); }


  virtual void Init() {}
  virtual void ShutDown() {}
  virtual void Run() {}
 private:
  void OnEvent(Event& event);
  bool OnWindowCloseEvent(WindowCloseEvent& event);
 private:
  Scope<Window> window;
  LayerStack layerStack;
  bool isRunning;
};

ALinkApplication* CreateApplication();
}  // namespace ALinkEngine

#endif  // ALINKENGINE_CORE_APPLICATION_H_
