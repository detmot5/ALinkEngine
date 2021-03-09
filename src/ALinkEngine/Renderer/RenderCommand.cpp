#include "alinkpch.h"
#include "RenderCommand.h"
#ifdef ALINK_GL_OPENGL
#include "GraphicsAPI/OpenGL/OpenGLRendererAPI.h"
#endif  // ALINK_GL_OPENGL

namespace ALink {
#ifdef ALINK_GL_OPENGL
std::unique_ptr<RendererAPI> RenderCommand::rendererAPI =
                                            std::make_unique<OpenGLRendererAPI>();
#endif  // ALINK_GL_OPENGL

}  // namespace ALink

