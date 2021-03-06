#ifndef ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLCONTEXT_H_
#define ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLCONTEXT_H_

#include <GLFW/glfw3.h>
#include "Renderer/GraphicsContext.h"

namespace ALinkEngine {

class OpenGLContext : public GraphicsContext {
 public:
  explicit OpenGLContext(GLFWwindow* windowHandle);

  void Init() override;
  void SwapBuffers() override;
 private:
  GLFWwindow* windowHandle;
};

}

#endif  // ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLCONTEXT_H_
