#ifndef ALINKENGINE_RENDERER_RENDERER_H_
#define ALINKENGINE_RENDERER_RENDERER_H_
namespace ALinkEngine {

enum class RendererAPI {
  None = 0,
  OpenGL = 1,
};

class Renderer {
 public:
  static inline RendererAPI GetAPI() { return currentAPI; }
 private:
  static inline RendererAPI currentAPI = RendererAPI::OpenGL;  // for now
};
}  // namespace ALinkEngine

#endif  // ALINKENGINE_RENDERER_RENDERER_H_
