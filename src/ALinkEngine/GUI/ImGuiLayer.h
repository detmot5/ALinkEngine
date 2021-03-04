#ifndef ALINKENGINE_GUI_IMGUILAYER_H_
#define ALINKENGINE_GUI_IMGUILAYER_H_

#include "Core/Core.h"
#include "Core/Layer.h"


#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent.h"

namespace ALinkEngine {

class ImGuiLayer : public Layer {
 public:
  ImGuiLayer();
  ~ImGuiLayer();

  void OnAttach() override;
  void OnDetach() override;
  void OnUpdate();
  void OnEvent(Event& event);

 private:
  bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
  bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
  bool OnMouseMovedEvent(MouseMovedEvent& event);
  bool OnMouseScrolledEvent(MouseScrolledEvent& event);
  bool OnKeyPressedEvent(KeyPressedEvent& event);
  bool OnKeyReleasedEvent(KeyReleasedEvent& event);
  bool OnKeyTypedEvent(KeyTypedEvent& event);
  bool OnWindowResizeEvent(WindowResizeEvent& event);
 private:
  float time = 0.0f;
};

}  // namespace ALinkEngine

#endif  // ALINKENGINE_GUI_IMGUILAYER_H_
