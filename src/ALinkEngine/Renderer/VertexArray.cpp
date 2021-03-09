#include "alinkpch.h"
#include "VertexArray.h"

#ifdef ALINK_GL_OPENGL
#include "GraphicsAPI/OpenGL/OpenGLVertexArray.h"
#endif  // ALINK_GL_OPENGL

#include "Renderer/Renderer.h"
#include "Renderer/RendererAPI.h"
namespace ALink {
std::shared_ptr<VertexArray> VertexArray::Create() {
#ifdef ALINK_GL_OPENGL
  return std::make_shared<OpenGLVertexArray>();
#else
#error "ALINK_GL not defined! Please define API what ALink should use eg. ALINK_GL_OPENGL"
#endif  // ALINK_GL_OPENGL
}
}  // namespace ALink
