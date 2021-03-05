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
  void OnImGuiRender() override;
  void OnEvent(Event& event) override;

  void Begin();
  void End();
 private:
  
};

}  // namespace ALinkEngine

#endif  // ALINKENGINE_GUI_IMGUILAYER_H_
