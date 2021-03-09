#include "alinkpch.h"
#include "OpenGLContext.h"
#include "Core/Core.h"
#include <glad/glad.h>

namespace ALink {
OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
  : windowHandle(windowHandle) {
  ALINK_ENGINE_ASSERT(windowHandle, "OpenGL Context - window is nullptr");
}

void OpenGLContext::Init() {
  glfwMakeContextCurrent(this->windowHandle);
  int status =
      gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
  ALINK_ENGINE_ASSERT(status, "Could not load GLAD");
  ALINK_ENGINE_LOG_INFO("Detected GPU: {0} {1} ", glGetString(GL_VENDOR), glGetString(GL_RENDERER));
  ALINK_ENGINE_LOG_INFO("Detected Graphics Driver: {0}", glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers() {
  glfwSwapBuffers(this->windowHandle);
}


}  // namespace ALink
