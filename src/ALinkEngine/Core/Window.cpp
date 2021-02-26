#include "Window.h"

namespace ALinkEngine {

static bool isGLFWInitialized = false;

Window::Window(const WindowProps& props) {
  this->windowProps.Title = props.Title;
  this->windowProps.Width = props.Width;
  this->windowProps.Height = props.Height;
  ALINK_LOG_INFO("Creating window %s with size: %ux%u", this->windowProps.Title.c_str(),
                 this->windowProps.Width, this->windowProps.Height);

  if (!isGLFWInitialized) {
    int isSuccess = glfwInit();
    ALINK_ENGINE_ASSERT(isSuccess, "Could not initialize GLFW");
    isGLFWInitialized = true;
  }
  this->windowHandle =
      glfwCreateWindow(static_cast<int>(this->windowProps.Width),
                       static_cast<int>(this->windowProps.Height),
                       this->windowProps.Title.c_str(), nullptr, nullptr);

  glfwMakeContextCurrent(this->windowHandle);
  glfwSetWindowUserPointer(this->windowHandle, &this->windowProps);
  this->SetVSync(true);
}

Window::~Window() { this->ShutDown(); }

void Window::ShutDown() { glfwDestroyWindow(this->windowHandle); }

void Window::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(this->windowHandle);
}

void Window::SetEventCallback(const EventCallbackFn& callback) {}

void Window::SetVSync(bool isEnabled) {
  glfwSwapInterval(isEnabled ? 1 : 0);
  this->windowProps.isVsync = isEnabled;
}

bool Window::IsVSync() const { return windowProps.isVsync; }

}  // namespace ALinkEngine