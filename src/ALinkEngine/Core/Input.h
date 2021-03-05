#ifndef ALINKENGINE_CORE_INPUT_H_
#define ALINKENGINE_CORE_INPUT_H_
#include "alinkpch.h"
#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"


namespace ALinkEngine {

class Input {
 public:
  static bool IsKeyPressed(KeyCode keyCode);
  static bool IsMouseButtonPressed(MouseCode mouseCode);
  static std::pair<float, float> GetMousePosition();
  static float GetMouseX();
  static float GetMouseY();

};

}  // namespace ALinkEngine


#endif  // ALINKENGINE_CORE_INPUT_H_
