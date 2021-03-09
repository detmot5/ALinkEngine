#ifndef ALINKENGINE_RENDERER_GRAPHICSCONTEXT_H_
#define ALINKENGINE_RENDERER_GRAPHICSCONTEXT_H_


namespace ALink {

class GraphicsContext {
 public:
  virtual void Init() = 0;
  virtual void SwapBuffers() = 0;
};
} // namespace ALink


#endif  // ALINKENGINE_RENDERER_GRAPHICSCONTEXT_H_
