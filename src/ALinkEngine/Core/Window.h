#ifndef ALINKENGINE_CORE_WINDOW_H_
#define ALINKENGINE_CORE_WINDOW_H_
// Based on Hazel but without abstraciotn - ALink will always use GLFW

#include <GLFW/glfw3.h>

#include "Core/Core.h"
#include "Events/Event.h"
#include "alinkpch.h"

namespace ALinkEngine {
using EventCallbackFn = std::function<void(Event&)>;
struct WindowProps {
  WindowProps(const std::string& title = "ALink", uint32_t width = 1600,
              uint32_t height = 900)
      : Title(title), Width(width), Height(height) {}

  std::string Title;
  uint32_t Width;
  uint32_t Height;
  bool isVsync;
  EventCallbackFn eventCallback;
};

// Interface representing a desktop system based Window
class Window {
 public:
  explicit Window(const WindowProps& props);
  ~Window();
  void ShutDown();
  void OnUpdate();

  inline uint32_t GetWidth() const { return windowProps.Width; }
  inline uint32_t GetHeight() const { return windowProps.Height; }

  // Window attributes
  void SetEventCallback(const EventCallbackFn& callback);
  void SetVSync(bool isEnabled);
  bool IsVSync() const;

 private:
  void SetWindowEvents();
 private:
  WindowProps windowProps;
  GLFWwindow* windowHandle;
};
}  // namespace ALinkEngine

#endif  // ALINKENGINE_CORE_WINDOW_H_
