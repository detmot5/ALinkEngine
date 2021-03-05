#include "Input.h"
#include <GLFW/glfw3.h>
#include "Core/Application.h"

namespace ALinkEngine {

bool Input::IsKeyPressed(KeyCode keyCode) {
  auto window = ALinkApplication::GetInstance().GetWindow().GetWindowHandle();
  auto keyState = glfwGetKey(window, keyCode);
  return (keyState == GLFW_PRESS || keyState == GLFW_REPEAT);
}

bool Input::IsMouseButtonPressed(MouseCode mouseCode) {
  auto window = ALinkApplication::GetInstance().GetWindow().GetWindowHandle();
  auto buttonState = glfwGetMouseButton(window, mouseCode);
  return (buttonState == GLFW_PRESS);
}

std::pair<float, float> Input::GetMousePosition() {
  auto window = ALinkApplication::GetInstance().GetWindow().GetWindowHandle();
  double xPos, yPos;
  glfwGetCursorPos(window, &xPos, &yPos);
  return {static_cast<float>(xPos), static_cast<float>(yPos)};
}

float Input::GetMouseX() {
  auto[xPos, yPos] = GetMousePosition();
  return xPos;
}

float Input::GetMouseY() {
  auto[xPos, yPos] = GetMousePosition();
  return yPos;
}
  
}  // namespace ALinkEngine
