#ifndef ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLTEXTURE_H_
#define ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLTEXTURE_H_
#include "Renderer/Texture.h"

namespace ALink {
  
class OpenGLTexture2D : public Texture2D {
 public:
  explicit OpenGLTexture2D(const std::string& path);
  ~OpenGLTexture2D();
  void Bind(uint32_t slot = 0) const override;
  inline uint32_t GetWidth() const override { return this->width; }
  inline uint32_t GetHeight() const override { return this->height; }
 private:
  std::string path;
  uint32_t width;
  uint32_t height;
  uint32_t rendererID;
};

}  // namespace ALink


#endif  // ALINKENGINE_GRAPHICSAPI_OPENGL_OPENGLTEXTURE_H_

