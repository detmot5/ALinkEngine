#include "alinkpch.h"
#include "Shader.h"
#include "GraphicsAPI/OpenGL/OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
namespace ALink {

std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
#ifdef ALINK_GL_OPENGL
  return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
#else
#error "ALINK_GL not defined! Please define API what ALink should use eg. ALINK_GL_OPENGL"
#endif  // ALINK_GL_OPENGL
}


}  // namespace ALink