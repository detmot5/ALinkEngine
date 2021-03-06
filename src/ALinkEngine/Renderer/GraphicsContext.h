#ifndef ALINKENGINE_RENDERER_GRAPHICSCONTEXT_H_
#define ALINKENGINE_RENDERER_GRAPHICSCONTEXT_H_


namespace ALinkEngine {

class GraphicsContext {
 public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};
} // namespace ALinkEngine


#endif  // ALINKENGINE_RENDERER_GRAPHICSCONTEXT_H_
