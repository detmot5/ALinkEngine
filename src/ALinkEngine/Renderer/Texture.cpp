#include "alinkpch.h"
#include "Texture.h"

#include "Renderer/Renderer.h"
#ifdef ALINK_GL_OPENGL
#include "GraphicsAPI/OpenGL/OpenGLTexture.h"
#endif  // ALINK_GL_OPENGL

namespace ALink {
std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path) {
#ifdef ALINK_GL_OPENGL
  return std::make_shared<OpenGLTexture2D>(path);
#else
#error "ALINK_GL not defined! Please define API what ALink should use eg. ALINK_GL_OPENGL"
#endif  // ALINK_GL_OPENGL
}
}  // namespace ALink
