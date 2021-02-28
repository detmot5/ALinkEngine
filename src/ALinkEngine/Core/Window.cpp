#include "Window.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace ALinkEngine {

static bool isGLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description) {
  ALINK_LOG_ERROR("GLFW Error: (%d): %s", error, description);
}


Window::Window(const WindowProps& props) {
  this->windowProps.Title = props.Title;
  this->windowProps.Width = props.Width;
  this->windowProps.Height = props.Height;
  ALINK_LOG_INFO("Creating window %s with size: %ux%u",
                 this->windowProps.Title.c_str(), this->windowProps.Width,
                 this->windowProps.Height);
  
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
  this->SetWindowEvents();
}

Window::~Window() { this->ShutDown(); }

void Window::ShutDown() { glfwDestroyWindow(this->windowHandle); }

void Window::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(this->windowHandle);
}

void Window::SetEventCallback(const EventCallbackFn& callback) {
  this->windowProps.eventCallback = callback;
}

void Window::SetVSync(bool isEnabled) {
  glfwSwapInterval(isEnabled ? 1 : 0);
  this->windowProps.isVsync = isEnabled;
}

bool Window::IsVSync() const { return windowProps.isVsync; }

void Window::SetWindowEvents() {
    glfwSetWindowSizeCallback(
      this->windowHandle, [](GLFWwindow* window, int width, int height) {
        WindowProps* props =
            reinterpret_cast<WindowProps*>(glfwGetWindowUserPointer(window));
        props->Width = width;
        props->Height = height;
        WindowResizeEvent event(width, height);
        props->eventCallback(event);
      });

  glfwSetWindowCloseCallback(this->windowHandle, [](GLFWwindow* window) {
    WindowProps* props =
        reinterpret_cast<WindowProps*>(glfwGetWindowUserPointer(window));
    WindowCloseEvent event;
    props->eventCallback(event);
  });

  glfwSetKeyCallback(
      this->windowHandle,
      [](GLFWwindow* window, int key, int scanCode, int action, int mods) {
        WindowProps* props =
            reinterpret_cast<WindowProps*>(glfwGetWindowUserPointer(window));
        switch (action) {
          case GLFW_PRESS: {
            KeyPressedEvent event(key, 0);
            props->eventCallback(event);
            break;
          }
          case GLFW_RELEASE: {
            KeyReleasedEvent event(key);
            props->eventCallback(event);
            break;
          }
          case GLFW_REPEAT: {
            KeyPressedEvent event(key, 1);
            props->eventCallback(event);
            break;
          }
        }
      });
  glfwSetMouseButtonCallback(
      this->windowHandle,
      [](GLFWwindow* window, int button, int action, int mods) {
        WindowProps* props =
            reinterpret_cast<WindowProps*>(glfwGetWindowUserPointer(window));
        switch (action) {
          case GLFW_PRESS: {
            MouseButtonPressedEvent event(button);
            props->eventCallback(event);
            break;
          }
          case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(button);
            props->eventCallback(event);
            break;
          }
        }
      });
  
  glfwSetScrollCallback(this->windowHandle, [] (GLFWwindow* window, double xOffset, double yOffset) {
    WindowProps* props =
      reinterpret_cast<WindowProps*>(glfwGetWindowUserPointer(window));
    MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
    props->eventCallback(event);
  });

  glfwSetCursorPosCallback(this->windowHandle, [] (GLFWwindow* window, double xPos, double yPos) {
    WindowProps* props =
      reinterpret_cast<WindowProps*>(glfwGetWindowUserPointer(window)); 
    MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
    props->eventCallback(event);
  });
}

}  // namespace ALinkEngine
