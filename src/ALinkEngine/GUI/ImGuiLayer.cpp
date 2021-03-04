#include "ImGuiLayer.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>

#include "Core/Application.h"
#include "Core/Core.h"
#include "alinkpch.h"

namespace ALinkEngine {
ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplOpenGL3_Init("#version 330");
}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnUpdate() {
  ImGuiIO& io = ImGui::GetIO();
  auto& window = ALinkApplication::GetInstance().GetWindow();

  float deltaTime = static_cast<float>(glfwGetTime());
  io.DeltaTime = this->time > 0.0f ? (deltaTime - this->time) : (1.0f / 60.0f);
  io.DisplaySize = ImVec2(1600, 900);
  this->time = deltaTime;
  static bool show = true;
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();
  ImGui::ShowDemoWindow(&show);
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Event handling

void ImGuiLayer::OnEvent(Event& event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<MouseButtonPressedEvent>(
      ALINK_BIND_EVENT_CALLBACK(ImGuiLayer::OnMouseButtonPressedEvent));
  dispatcher.Dispatch<MouseButtonReleasedEvent>(
      ALINK_BIND_EVENT_CALLBACK(ImGuiLayer::OnMouseButtonReleasedEvent));
  dispatcher.Dispatch<MouseMovedEvent>(
      ALINK_BIND_EVENT_CALLBACK(ImGuiLayer::OnMouseMovedEvent));
  dispatcher.Dispatch<MouseScrolledEvent>(
      ALINK_BIND_EVENT_CALLBACK(ImGuiLayer::OnMouseScrolledEvent));
  dispatcher.Dispatch<KeyPressedEvent>(
      ALINK_BIND_EVENT_CALLBACK(ImGuiLayer::OnKeyPressedEvent));
  dispatcher.Dispatch<KeyReleasedEvent>(
      ALINK_BIND_EVENT_CALLBACK(ImGuiLayer::OnKeyReleasedEvent));
  dispatcher.Dispatch<KeyTypedEvent>(
      ALINK_BIND_EVENT_CALLBACK(ImGuiLayer::OnKeyTypedEvent));
  dispatcher.Dispatch<WindowResizeEvent>(
      ALINK_BIND_EVENT_CALLBACK(ImGuiLayer::OnWindowResizeEvent));
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.MouseDown[event.GetMouseButton()] = true;
  return false;
}
bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.MouseDown[event.GetMouseButton()] = false;
  return false;
}
bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.MousePos = ImVec2(event.GetX(), event.GetY());
  return false;
}
bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.MouseWheelH += event.GetXOffset();
  io.MouseWheel += event.GetYOffset();
  return false;
}
bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.KeysDown[event.GetKeyCode()] = true;
  io.KeyCtrl =
      (io.KeysDown[Key::LeftControl] || io.KeysDown[Key::RightControl]);
  io.KeyAlt = (io.KeysDown[Key::LeftAlt] || io.KeysDown[Key::RightAlt]);
  io.KeyShift = (io.KeysDown[Key::LeftShift] || io.KeysDown[Key::RightShift]);

  return false;
}
bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.KeysDown[event.GetKeyCode()] = false;
  io.KeyCtrl =
      (io.KeysDown[Key::LeftControl] || io.KeysDown[Key::RightControl]);
  io.KeyAlt = (io.KeysDown[Key::LeftAlt] || io.KeysDown[Key::RightAlt]);
  io.KeyShift = (io.KeysDown[Key::LeftShift] || io.KeysDown[Key::RightShift]);
  return false;
}
bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& event) {
  return false;
}  // not implemented yet
bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event) {
  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
  io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
  glViewport(0, 0, event.GetWidth(), event.GetHeight());
  return false;
}

}  // namespace ALinkEngine
