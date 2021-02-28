#ifndef ALINKENGINE_CORE_APPLICATION_H_
#define ALINKENGINE_CORE_APPLICATION_H_
#include "Core/Core.h"
#include "Core/Window.h"
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

  virtual void Init() {}
  virtual void ShutDown() {}
  virtual void Run() {}
 private:
  void OnEvent(Event& event);
  bool OnWindowCloseEvent(WindowCloseEvent& event);
 private:
  Scope<Window> window;
  bool isRunning;
};

ALinkApplication* CreateApplication();
}  // namespace ALinkEngine

#endif  // ALINKENGINE_CORE_APPLICATION_H_
